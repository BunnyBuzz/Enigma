#include <cfg/FunctionGraphLayout.h>

#include <algorithm>
#include <unordered_map>

namespace cfg {

namespace {

// Successor of a block: direct edge target (block index) or fallthrough.
struct Successor {
    int block = -1;
    int edge = -1; // index into edges_; -1 = synthetic fallthrough
    bool fallthrough = false;
    uint64_t sortKey = 0; // target address for deterministic order
};

} // namespace

GraphLayout layoutFunctionGraph(const std::vector<CfgBlock>& blocks,
                                const std::vector<CfaEdge>& edges,
                                uint64_t funcStart, uint64_t funcEnd,
                                const std::vector<GraphBlockInput>& inputs,
                                const GraphMetrics& metrics) {
    GraphLayout out;

    // ---- 1. Select blocks of this function, in address order ----
    std::vector<int> order;
    for (int i = 0; i < static_cast<int>(blocks.size()); ++i) {
        if (blocks[i].startAddr >= funcStart && blocks[i].startAddr <= funcEnd)
            order.push_back(i);
    }
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        if (blocks[a].startAddr != blocks[b].startAddr)
            return blocks[a].startAddr < blocks[b].startAddr;
        return a < b;
    });
    if (order.empty()) return out;

    std::unordered_map<int, int> rowOf; // block index -> row
    for (int r = 0; r < static_cast<int>(order.size()); ++r)
        rowOf[order[r]] = r;

    // Row -> block lookup for edge target resolution (blocks are disjoint in
    // rows; first match in address order wins).
    auto blockAtRow = [&](int row) -> int {
        for (int bi : order) {
            if (row >= blocks[bi].firstRow && row <= blocks[bi].lastRow)
                return bi;
        }
        return -1;
    };

    // ---- 2. Successors: direct edges + synthetic fallthrough ----
    // fallthrough exists iff the block has no Unconditional and no Return
    // among its out-edges (mirrors the Ghidra block model used by build()).
    std::unordered_map<int, std::vector<Successor>> succ;
    std::unordered_map<int, std::vector<int>> edgeOfBlock; // block -> edge idx
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        const CfaEdge& e = edges[i];
        const int from = blockAtRow(e.fromRow);
        if (from < 0 || rowOf.find(from) == rowOf.end()) continue;
        edgeOfBlock[from].push_back(i);
        if (e.toRow < 0 || e.isReturn() || e.isComputed() ||
            e.kind == EdgeKind::Call)
            continue; // exit stub, not a routed edge
        const int to = blockAtRow(e.toRow);
        if (to < 0 || rowOf.find(to) == rowOf.end()) continue;
        succ[from].push_back({to, i, false, e.toAddr});
    }
    for (int bi : order) {
        bool hasUncond = false, hasReturn = false;
        auto it = edgeOfBlock.find(bi);
        if (it != edgeOfBlock.end()) {
            for (int ei : it->second) {
                if (edges[ei].kind == EdgeKind::Unconditional) hasUncond = true;
                if (edges[ei].isReturn()) hasReturn = true;
            }
        }
        if (!hasUncond && !hasReturn) {
            // Fallthrough = next block in address order.
            const int r = rowOf[bi];
            if (r + 1 < static_cast<int>(order.size()))
                succ[bi].push_back({order[r + 1], -1, true,
                                    blocks[order[r + 1]].startAddr});
        }
        // Deterministic successor order: fallthrough first, then by address.
        std::sort(succ[bi].begin(), succ[bi].end(), [](const Successor& a,
                                                       const Successor& b) {
            if (a.fallthrough != b.fallthrough) return a.fallthrough;
            if (a.sortKey != b.sortKey) return a.sortKey < b.sortKey;
            return a.block < b.block;
        });
    }

    // ---- 3. Column assignment: DFS from entry ----
    std::unordered_map<int, int> colOf;
    int maxCol = 0;
    {
        std::vector<int> stack;
        stack.push_back(order[0]);
        colOf[order[0]] = 0;
        std::unordered_map<int, bool> entered;
        entered[order[0]] = true;
        while (!stack.empty()) {
            const int b = stack.back();
            stack.pop_back();
            auto it = succ.find(b);
            if (it == succ.end()) continue;
            // Push in reverse so the first successor is processed first.
            for (int k = static_cast<int>(it->second.size()) - 1; k >= 0; --k) {
                const Successor& s = it->second[k];
                if (entered[s.block]) continue;
                entered[s.block] = true;
                if (s.fallthrough) {
                    colOf[s.block] = colOf[b];
                } else {
                    colOf[s.block] = ++maxCol;
                }
                stack.push_back(s.block);
            }
        }
        // Unreachable blocks: append in address order, continuing the DFS.
        for (int bi : order) {
            if (entered[bi]) continue;
            entered[bi] = true;
            colOf[bi] = ++maxCol;
            stack.push_back(bi);
            while (!stack.empty()) {
                const int b = stack.back();
                stack.pop_back();
                auto it = succ.find(b);
                if (it == succ.end()) continue;
                for (int k = static_cast<int>(it->second.size()) - 1; k >= 0; --k) {
                    const Successor& s = it->second[k];
                    if (entered[s.block]) continue;
                    entered[s.block] = true;
                    colOf[s.block] = s.fallthrough ? colOf[b] : ++maxCol;
                    stack.push_back(s.block);
                }
            }
        }
    }

    // ---- 4. Node rects (uniform column width keeps routing simple) ----
    std::unordered_map<int, GraphBlockInput> inputByBlock;
    for (const GraphBlockInput& in : inputs) inputByBlock[in.blockIndex] = in;
    std::unordered_map<int, int> nodeW, nodeH;
    int colW = 0;
    for (int bi : order) {
        auto it = inputByBlock.find(bi);
        const int lines = (it != inputByBlock.end()) ? it->second.lineCount : 1;
        const int chars = (it != inputByBlock.end()) ? it->second.maxChars : 8;
        nodeW[bi] = chars * metrics.charWidth + 2 * metrics.padX;
        nodeH[bi] = lines * metrics.lineHeight + 2 * metrics.padY;
        colW = std::max(colW, nodeW[bi]);
    }
    std::vector<int> rowH(order.size(), 0);
    for (int r = 0; r < static_cast<int>(order.size()); ++r)
        rowH[r] = nodeH[order[r]];
    std::vector<int> rowY(order.size(), 0);
    for (size_t r = 1; r < order.size(); ++r)
        rowY[r] = rowY[r - 1] + rowH[r - 1] + metrics.rowGap;
    const int nCols = maxCol + 1;
    auto colX = [&](int c) { return c * (colW + metrics.colGap); };
    for (int r = 0; r < static_cast<int>(order.size()); ++r) {
        const int bi = order[r];
        GraphNode n;
        n.blockIndex = bi;
        n.col = colOf[bi];
        n.row = r;
        n.w = nodeW[bi];
        n.h = nodeH[bi];
        n.x = colX(n.col);
        n.y = rowY[r];
        out.nodes.push_back(n);
    }
    out.width = nCols * colW + (nCols - 1) * metrics.colGap;
    out.height = rowY.back() + rowH.back();

    std::unordered_map<int, const GraphNode*> nodeByBlock;
    for (const GraphNode& n : out.nodes) nodeByBlock[n.blockIndex] = &n;

    // ---- 5. Edges: route + shared lane assignment over row spans ----
    struct Routable {
        int from, to; // block indices; to == -1 => exit stub
        int edge;     // index into edges_; -1 = synthetic fallthrough
        EdgeKind kind;
        bool fallthrough;
    };
    std::vector<Routable> routables;
    for (int bi : order) {
        auto it = succ.find(bi);
        if (it != succ.end()) {
            for (const Successor& s : it->second)
                routables.push_back({bi, s.block, s.edge,
                                     s.edge >= 0 ? edges[s.edge].kind
                                                 : EdgeKind::Unconditional,
                                     s.fallthrough});
        }
        // Exit stubs for call/return/computed/unresolved edges.
        auto eit = edgeOfBlock.find(bi);
        if (eit != edgeOfBlock.end()) {
            // Deterministic stub order: by source row, then target address.
            std::vector<int> stubEdges = eit->second;
            std::sort(stubEdges.begin(), stubEdges.end(), [&](int a, int b) {
                if (edges[a].fromRow != edges[b].fromRow)
                    return edges[a].fromRow < edges[b].fromRow;
                return edges[a].toAddr < edges[b].toAddr;
            });
            for (int ei : stubEdges) {
                const CfaEdge& e = edges[ei];
                if (e.toRow >= 0 && !e.isReturn() && !e.isComputed() &&
                    e.kind != EdgeKind::Call)
                    continue; // already routed above
                routables.push_back({bi, -1, ei, e.kind, false});
            }
        }
    }

    // One shared lane assignment over row spans (same rule as the gutter).
    std::vector<const CfaEdge*> spanEdges;
    std::vector<CfaEdge> spanStorage;
    for (const Routable& r : routables) {
        if (r.to < 0) continue;
        CfaEdge se;
        se.fromRow = rowOf[r.from];
        se.toRow = rowOf[r.to];
        spanStorage.push_back(se);
    }
    for (const CfaEdge& se : spanStorage) spanEdges.push_back(&se);
    const std::vector<int> lanes = assignTracks(spanEdges);
    size_t laneIdx = 0;

    for (const Routable& r : routables) {
        GraphEdge ge;
        ge.fromBlock = r.from;
        ge.toBlock = r.to;
        ge.kind = r.kind;
        ge.isFallthrough = r.fallthrough;
        const GraphNode* src = nodeByBlock[r.from];
        if (r.to < 0) {
            // Exit stub: returns drop below, calls/computed jog right.
            ge.lane = 0;
            if (r.kind == EdgeKind::Return) {
                const int cx = src->x + src->w / 2;
                ge.points = {{cx, src->y + src->h},
                             {cx, src->y + src->h + metrics.rowGap / 2}};
            } else {
                const int my = src->y + src->h / 2;
                ge.points = {{src->x + src->w, my},
                             {src->x + src->w + metrics.colGap / 2, my}};
            }
            out.edges.push_back(ge);
            continue;
        }
        const GraphNode* dst = nodeByBlock[r.to];
        ge.lane = lanes[laneIdx++];
        ge.isBackEdge = (dst->row <= src->row);
        if (!ge.isBackEdge) {
            // Forward: down out of the source, jog in the gap below it,
            // straight down the target column into the target top.
            // Same column + adjacent rows: single straight spine.
            const int sx = src->x + src->w / 2;
            const int tx = dst->x + dst->w / 2;
            const int ySrcBot = src->y + src->h;
            const int yDstTop = dst->y;
            const int yJog = ySrcBot + 1 + ge.lane;
            if (sx == tx && dst->row == src->row + 1) {
                ge.points = {{sx, ySrcBot}, {sx, yDstTop}};
            } else {
                ge.points = {{sx, ySrcBot},
                             {sx, yJog},
                             {tx, yJog},
                             {tx, yDstTop}};
            }
        } else {
            // Back edge: out the right side, up the channel right of all
            // columns, back in the right side of the target.
            const int chX = out.width + 1 + ge.lane;
            const int ySrc = src->y + src->h / 2;
            const int yDst = dst->y + dst->h / 2;
            ge.points = {{src->x + src->w, ySrc},
                         {chX, ySrc},
                         {chX, yDst},
                         {dst->x + dst->w, yDst}};
        }
        out.edges.push_back(ge);
    }

    // Expand the canvas to contain every routed point (back-edge channels
    // extend right of the node area).
    for (const GraphEdge& ge : out.edges) {
        for (const GraphPoint& p : ge.points) {
            if (p.x + 1 > out.width) out.width = p.x + 1;
            if (p.y + 1 > out.height) out.height = p.y + 1;
        }
    }

    return out;
}

} // namespace cfg

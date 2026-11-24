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
                if (e.kind == EdgeKind::Call || e.kind == EdgeKind::ComputedCall)
                    continue; // intra-block calls stay inside the block box
                if (e.toRow >= 0 && !e.isReturn() && !e.isComputed())
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

    // Precompute distributed horizontal ports for forward edges so multiple
    // outgoing/incoming edges do not stack on the exact center pixel.
    std::vector<int> fwdLane(routables.size(), 0);
    std::vector<bool> fwdIsBack(routables.size(), false);
    std::unordered_map<int, std::vector<size_t>> outFwdByBlock;
    std::unordered_map<int, std::vector<size_t>> inFwdByBlock;
    {
        size_t li = 0;
        for (size_t i = 0; i < routables.size(); ++i) {
            const Routable& r = routables[i];
            if (r.to < 0) continue;
            fwdLane[i] = lanes[li++];
            const GraphNode* src = nodeByBlock[r.from];
            const GraphNode* dst = nodeByBlock[r.to];
            fwdIsBack[i] = (dst->row <= src->row);
            if (!fwdIsBack[i]) {
                outFwdByBlock[r.from].push_back(i);
                inFwdByBlock[r.to].push_back(i);
            }
        }
    }

    std::vector<int> srcPortX(routables.size(), 0);
    std::vector<int> dstPortX(routables.size(), 0);

    auto distributePorts = [&](int center, int boxWidth, size_t idx, size_t count) -> int {
        if (count <= 1) return center;
        const int maxSpan = std::max(2, boxWidth / 2);
        const int idealStep = std::max(2, metrics.charWidth * 3);
        const int span = std::min(maxSpan, static_cast<int>(count - 1) * idealStep);
        return center - span / 2 + static_cast<int>(idx * span / (count - 1));
    };

    for (auto& kv : outFwdByBlock) {
        auto& list = kv.second;
        const GraphNode* src = nodeByBlock[kv.first];
        std::sort(list.begin(), list.end(), [&](size_t a, size_t b) {
            const GraphNode* da = nodeByBlock[routables[a].to];
            const GraphNode* db = nodeByBlock[routables[b].to];
            if (da->col != db->col) return da->col < db->col;
            if (da->row != db->row) return da->row < db->row;
            return routables[a].to < routables[b].to;
        });
        const int cx = src->x + src->w / 2;
        for (size_t k = 0; k < list.size(); ++k)
            srcPortX[list[k]] = distributePorts(cx, src->w, k, list.size());
    }

    for (auto& kv : inFwdByBlock) {
        auto& list = kv.second;
        const GraphNode* dst = nodeByBlock[kv.first];
        std::sort(list.begin(), list.end(), [&](size_t a, size_t b) {
            const size_t ia = a;
            const size_t ib = b;
            if (srcPortX[ia] != srcPortX[ib]) return srcPortX[ia] < srcPortX[ib];
            const GraphNode* sa = nodeByBlock[routables[ia].from];
            const GraphNode* sb = nodeByBlock[routables[ib].from];
            if (sa->row != sb->row) return sa->row > sb->row;
            return routables[ia].from < routables[ib].from;
        });
        const int cx = dst->x + dst->w / 2;
        for (size_t k = 0; k < list.size(); ++k)
            dstPortX[list[k]] = distributePorts(cx, dst->w, k, list.size());
    }

    // Also offset multiple back-edge ports on the right side of nodes.
    std::unordered_map<int, std::vector<size_t>> backOutByBlock, backInByBlock;
    for (size_t i = 0; i < routables.size(); ++i) {
        if (routables[i].to >= 0 && fwdIsBack[i]) {
            backOutByBlock[routables[i].from].push_back(i);
            backInByBlock[routables[i].to].push_back(i);
        }
    }
    std::vector<int> backSrcY(routables.size(), 0);
    std::vector<int> backDstY(routables.size(), 0);
    for (auto& kv : backOutByBlock) {
        auto& list = kv.second;
        const GraphNode* src = nodeByBlock[kv.first];
        for (size_t k = 0; k < list.size(); ++k) {
            const int mid = src->y + src->h / 2;
            backSrcY[list[k]] = distributePorts(mid, src->h, k, list.size());
        }
    }
    for (auto& kv : backInByBlock) {
        auto& list = kv.second;
        const GraphNode* dst = nodeByBlock[kv.first];
        for (size_t k = 0; k < list.size(); ++k) {
            const int mid = dst->y + dst->h / 2;
            backDstY[list[k]] = distributePorts(mid, dst->h, k, list.size());
        }
    }

    const int baseWidth = out.width;
    const int rowMargin = std::max(1, metrics.rowGap / 4);
    const int laneBand = std::max(1, metrics.rowGap - 2 * rowMargin);
    const int laneStep = std::max(1, laneBand / std::max(1, kCFAMaxTracks));

    for (size_t i = 0; i < routables.size(); ++i) {
        const Routable& r = routables[i];
        GraphEdge ge;
        ge.fromBlock = r.from;
        ge.toBlock = r.to;
        ge.kind = r.kind;
        ge.isFallthrough = r.fallthrough;
        const GraphNode* src = nodeByBlock[r.from];
        if (r.to < 0) {
            // Exit stub: returns and unresolved computed jumps drop cleanly below.
            ge.lane = 0;
            const int cx = src->x + src->w / 2;
            const int drop = std::max(1, metrics.rowGap / 3);
            ge.points = {{cx, src->y + src->h},
                         {cx, src->y + src->h + drop}};
            out.edges.push_back(ge);
            continue;
        }
        const GraphNode* dst = nodeByBlock[r.to];
        ge.lane = fwdLane[i];
        ge.isBackEdge = fwdIsBack[i];
        if (!ge.isBackEdge) {
            const int sx = srcPortX[i];
            const int tx = dstPortX[i];
            const int ySrcBot = src->y + src->h;
            const int yDstTop = dst->y;
            const int maxJog = ySrcBot + metrics.rowGap - rowMargin;
            const int yJog = std::min(maxJog, ySrcBot + rowMargin + ge.lane * laneStep);

            if (sx == tx && dst->row == src->row + 1) {
                ge.points = {{sx, ySrcBot}, {sx, yDstTop}};
            } else {
                // Check if a straight vertical drop along tx crosses any intermediate node.
                bool blocked = false;
                int maxObsRight = 0;
                if (dst->row > src->row + 1) {
                    const int tol = std::max(1, metrics.charWidth);
                    for (const GraphNode& mid : out.nodes) {
                        if (mid.row > src->row && mid.row < dst->row) {
                            if (tx >= mid.x - tol && tx <= mid.x + mid.w + tol) {
                                blocked = true;
                                maxObsRight = std::max(maxObsRight, mid.x + mid.w);
                            }
                        }
                    }
                }
                if (!blocked) {
                    ge.points = {{sx, ySrcBot},
                                 {sx, yJog},
                                 {tx, yJog},
                                 {tx, yDstTop}};
                } else {
                    // Route through the vertical gutter adjacent to dst's column.
                    int gutterX = 0;
                    const int colMargin = std::max(1, metrics.colGap / 3);
                    const int colStep = std::max(1, metrics.colGap / 8);
                    if (dst->col > 0) {
                        const int leftBound = colX(dst->col) - metrics.colGap + colMargin;
                        const int rightBound = colX(dst->col) - colMargin;
                        gutterX = std::min(rightBound, leftBound + (ge.lane % 4) * colStep);
                    } else {
                        const int rightBound = colW + metrics.colGap - colMargin;
                        gutterX = std::min(rightBound, maxObsRight + colMargin + (ge.lane % 4) * colStep);
                    }
                    const int yEntryJog = std::max(yJog + 1, yDstTop - rowMargin);
                    ge.points = {{sx, ySrcBot},
                                 {sx, yJog},
                                 {gutterX, yJog},
                                 {gutterX, yEntryJog},
                                 {tx, yEntryJog},
                                 {tx, yDstTop}};
                }
            }
        } else {
            // Back edge: out the right side, up the channel right of all
            // columns, back in the right side of the target.
            const int chMargin = std::max(1, metrics.colGap / 3);
            const int chStep = std::max(1, metrics.colGap / 6);
            const int chX = baseWidth + chMargin + ge.lane * chStep;
            const int ySrc = backSrcY[i];
            const int yDst = backDstY[i];
            ge.points = {{src->x + src->w, ySrc},
                         {chX, ySrc},
                         {chX, yDst},
                         {dst->x + dst->w, yDst}};
        }
        out.edges.push_back(ge);
    }

    // Expand the canvas to contain every routed point plus clean outer padding.
    for (const GraphEdge& ge : out.edges) {
        for (const GraphPoint& p : ge.points) {
            if (p.x + 1 > out.width) out.width = p.x + 1;
            if (p.y + 1 > out.height) out.height = p.y + 1;
        }
    }
    out.width += std::max(1, metrics.padX);
    out.height += std::max(1, metrics.padY);

    return out;
}

} // namespace cfg

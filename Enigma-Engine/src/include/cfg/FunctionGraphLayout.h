#pragma once

#include <cfg/DisassemblyCFG.h>

#include <cstdint>
#include <vector>

// Layered layout for the Function Graph view.
//
// Pure engine type (no Qt dependency) so it can be unit-tested with a plain
// C++ test binary. The GUI maps the abstract-unit rects/routes to pixels.
//
// Input: the blocks/edges of one function from cfg::DisassemblyCFG plus
// per-block text metrics (line count, longest line). Output: a node rect per
// block and an orthogonal polyline route per edge.
//
// Conventions:
//   - Rows (y) follow block address order: forward edges always go down,
//     loop-back edges always go up and are flagged isBackEdge.
//   - Columns (x) come from a DFS out of the entry block: the fallthrough
//     successor keeps the column, branch targets open a new column right.
//     Merge targets keep their first-assigned column.
//   - Horizontal jog separation reuses cfg::assignTracks over row spans, so
//     only genuinely concurrent edges consume lanes (same rule as the
//     disassembly gutter). Overspill shares the outermost lane.
//   - Known limitation (Phase-1): forward verticals may cross intermediate
//     nodes in dense graphs. Crossing-free channel routing is a Phase-2
//     refinement for the widget.

namespace cfg {

struct GraphPoint {
    int x = 0;
    int y = 0;
    bool operator==(const GraphPoint& o) const { return x == o.x && y == o.y; }
    bool operator!=(const GraphPoint& o) const { return !(*this == o); }
};

// Text metrics for one block; supplied by the caller (GUI measures real text,
// tests use synthetic values).
struct GraphBlockInput {
    int blockIndex = -1; // index into DisassemblyCFG::blocks()
    int lineCount = 1;   // text lines rendered inside the node
    int maxChars = 8;    // longest line, in characters
};

struct GraphMetrics {
    int lineHeight = 1; // abstract units per text line
    int charWidth = 1;  // abstract units per character
    int padX = 1;       // horizontal node padding
    int padY = 1;       // vertical node padding
    int colGap = 4;     // horizontal gap between columns
    int rowGap = 8;     // vertical gap between rows (headroom for edge jogs)
};

struct GraphNode {
    int blockIndex = -1;
    int col = 0;
    int row = 0;
    int x = 0, y = 0, w = 0, h = 0; // rect in abstract units
};

struct GraphEdge {
    int fromBlock = -1;
    int toBlock = -1; // -1 = exit stub (return / call / computed / unresolved)
    EdgeKind kind = EdgeKind::Unconditional;
    bool isFallthrough = false;
    bool isBackEdge = false;
    int lane = 0;
    std::vector<GraphPoint> points; // orthogonal route, source -> target
};

struct GraphLayout {
    std::vector<GraphNode> nodes;
    std::vector<GraphEdge> edges;
    int width = 0;
    int height = 0;

    const GraphNode* nodeByBlock(int blockIndex) const {
        for (const GraphNode& n : nodes)
            if (n.blockIndex == blockIndex) return &n;
        return nullptr;
    }
};

// Lays out a single function. `blocks`/`edges` are the full
// DisassemblyCFG output; only blocks in [funcStart, funcEnd] and direct
// edges between them are placed (calls/returns/computed become exit stubs).
// `inputs` must carry one entry per placed block; missing entries fall back
// to lineCount=1/maxChars=8. Fully deterministic for identical input.
GraphLayout layoutFunctionGraph(const std::vector<CfgBlock>& blocks,
                                const std::vector<CfaEdge>& edges,
                                uint64_t funcStart, uint64_t funcEnd,
                                const std::vector<GraphBlockInput>& inputs,
                                const GraphMetrics& metrics);

} // namespace cfg

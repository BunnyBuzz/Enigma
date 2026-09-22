/**
 * Enigma Engine - Function Graph Layout Unit Test
 *
 * Verifies the Qt-free layered layout over cfg::DisassemblyCFG output:
 * diamond/loop/nested fixtures, back-edge detection, lane-cap overspill,
 * node non-overlap, route orthogonality + containment, determinism.
 */
#include <cfg/DisassemblyCFG.h>
#include <cfg/FunctionGraphLayout.h>

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

static int passed = 0, total = 0;
#define TEST(n, x) do { total++; if(x){std::cout<<"[PASS] "<<n<<"\n"<<std::flush;passed++;}else{std::cout<<"[FAIL] "<<n<<"\n"<<std::flush;} } while(0)

using cfg::CfaEdge;
using cfg::CfgBlock;
using cfg::CfgInsn;
using cfg::DisassemblyCFG;
using cfg::EdgeKind;
using cfg::GraphBlockInput;
using cfg::GraphLayout;
using cfg::GraphMetrics;
using cfg::layoutFunctionGraph;

namespace {

CfgInsn insn(uint64_t addr, int row, const char* mne, const char* ops = "") {
    CfgInsn i;
    i.address = addr;
    i.row = row;
    i.length = 1;
    i.mnemonic = mne;
    i.operands = ops;
    return i;
}

// Inputs derived the way the widget will: line count from the block row
// span, fixed char width.
std::vector<GraphBlockInput> inputsFor(const DisassemblyCFG& cfg) {
    std::vector<GraphBlockInput> in;
    for (int i = 0; i < static_cast<int>(cfg.blocks().size()); ++i) {
        const CfgBlock& b = cfg.blocks()[i];
        GraphBlockInput gi;
        gi.blockIndex = i;
        gi.lineCount = b.lastRow - b.firstRow + 1;
        gi.maxChars = 20;
        in.push_back(gi);
    }
    return in;
}

bool orthogonal(const std::vector<cfg::GraphPoint>& pts) {
    if (pts.size() < 2) return false;
    for (size_t i = 1; i < pts.size(); ++i) {
        if (pts[i].x != pts[i - 1].x && pts[i].y != pts[i - 1].y)
            return false;
    }
    return true;
}

bool noOverlap(const GraphLayout& l) {
    for (size_t a = 0; a < l.nodes.size(); ++a) {
        for (size_t b = a + 1; b < l.nodes.size(); ++b) {
            const auto& A = l.nodes[a];
            const auto& B = l.nodes[b];
            const bool xOver = A.x < B.x + B.w && B.x < A.x + A.w;
            const bool yOver = A.y < B.y + B.h && B.y < A.y + A.h;
            if (xOver && yOver) return false;
        }
    }
    return true;
}

bool contained(const GraphLayout& l) {
    for (const auto& e : l.edges) {
        for (const auto& p : e.points) {
            if (p.x < 0 || p.y < 0 || p.x > l.width || p.y > l.height)
                return false;
        }
    }
    return true;
}

bool sameLayout(const GraphLayout& a, const GraphLayout& b) {
    if (a.nodes.size() != b.nodes.size() || a.edges.size() != b.edges.size())
        return false;
    if (a.width != b.width || a.height != b.height) return false;
    for (size_t i = 0; i < a.nodes.size(); ++i) {
        const auto& A = a.nodes[i];
        const auto& B = b.nodes[i];
        if (A.blockIndex != B.blockIndex || A.col != B.col || A.row != B.row ||
            A.x != B.x || A.y != B.y || A.w != B.w || A.h != B.h)
            return false;
    }
    for (size_t i = 0; i < a.edges.size(); ++i) {
        const auto& A = a.edges[i];
        const auto& B = b.edges[i];
        if (A.fromBlock != B.fromBlock || A.toBlock != B.toBlock ||
            A.isBackEdge != B.isBackEdge ||
            A.isFallthrough != B.isFallthrough || A.lane != B.lane ||
            A.points.size() != B.points.size())
            return false;
        for (size_t k = 0; k < A.points.size(); ++k)
            if (A.points[k] != B.points[k]) return false;
    }
    return true;
}

const cfg::GraphNode* findNode(const GraphLayout& l, int block) {
    return l.nodeByBlock(block);
}

} // namespace

int main() {
    std::cout << "=== Enigma Engine - FunctionGraphLayout Test ===" << std::endl;
    GraphMetrics m; // abstract units: lineHeight=1, charWidth=1

    // ---- 1. Diamond: cmp/je/jmp/ret ----
    {
        DisassemblyCFG cfg;
        std::vector<CfgInsn> insns = {
            insn(0x1000, 0, "CMP", "rax, rbx"),
            insn(0x1001, 1, "JE", "0x1004"),
            insn(0x1002, 2, "MOV", "rax, 1"),
            insn(0x1003, 3, "JMP", "0x1005"),
            insn(0x1004, 4, "MOV", "rax, 2"),
            insn(0x1005, 5, "RET", ""),
        };
        cfg.build(insns, {0x1000});
        TEST("diamond: 4 blocks", cfg.blocks().size() == 4);
        GraphLayout l = layoutFunctionGraph(cfg.blocks(), cfg.edges(), 0x1000,
                                            0x1005, inputsFor(cfg), m);
        TEST("diamond: 4 nodes placed", l.nodes.size() == 4);
        TEST("diamond: entry at col 0 row 0",
             findNode(l, 0) && findNode(l, 0)->col == 0 &&
                 findNode(l, 0)->row == 0);
        TEST("diamond: fallthrough keeps column",
             findNode(l, 1) && findNode(l, 1)->col == 0);
        TEST("diamond: branch opens new column",
             findNode(l, 2) && findNode(l, 2)->col == 1);
        TEST("diamond: merge block placed", findNode(l, 3) != nullptr);
        TEST("diamond: 5 edges (4 routed + ret stub)", l.edges.size() == 5);
        TEST("diamond: no back edges", [&] {
            for (const auto& e : l.edges)
                if (e.isBackEdge) return false;
            return true;
        }());
        TEST("diamond: no node overlap", noOverlap(l));
        TEST("diamond: all routes orthogonal", [&] {
            for (const auto& e : l.edges)
                if (!orthogonal(e.points)) return false;
            return true;
        }());
        TEST("diamond: routes contained", contained(l));
        TEST("diamond: lanes within cap", [&] {
            for (const auto& e : l.edges)
                if (e.lane < 0 || e.lane >= cfg::kCFAMaxTracks) return false;
            return true;
        }());
        TEST("diamond: deterministic",
             sameLayout(l, layoutFunctionGraph(cfg.blocks(), cfg.edges(),
                                               0x1000, 0x1005, inputsFor(cfg),
                                               m)));
    }

    // ---- 2. Loop: back edge detected ----
    {
        DisassemblyCFG cfg;
        std::vector<CfgInsn> insns = {
            insn(0x1000, 0, "MOV", "rcx, 10"),
            insn(0x1001, 1, "CMP", "rcx, 0"),
            insn(0x1002, 2, "JGE", "0x1005"),
            insn(0x1003, 3, "ADD", "rax, rcx"),
            insn(0x1004, 4, "JMP", "0x1001"),
            insn(0x1005, 5, "RET", ""),
        };
        cfg.build(insns, {0x1000});
        GraphLayout l = layoutFunctionGraph(cfg.blocks(), cfg.edges(), 0x1000,
                                            0x1005, inputsFor(cfg), m);
        TEST("loop: 4 nodes placed", l.nodes.size() == 4);
        int backEdges = 0, fwdEdges = 0;
        for (const auto& e : l.edges) {
            if (e.toBlock < 0) continue;
            if (e.isBackEdge)
                ++backEdges;
            else
                ++fwdEdges;
        }
        TEST("loop: exactly one back edge", backEdges == 1);
        TEST("loop: forward edges present", fwdEdges >= 2);
        TEST("loop: back edge goes up", [&] {
            for (const auto& e : l.edges) {
                if (e.toBlock < 0 || !e.isBackEdge) continue;
                const auto* s = l.nodeByBlock(e.fromBlock);
                const auto* d = l.nodeByBlock(e.toBlock);
                if (!(d->row < s->row)) return false;
            }
            return true;
        }());
        TEST("loop: no node overlap", noOverlap(l));
        TEST("loop: all routes orthogonal", [&] {
            for (const auto& e : l.edges)
                if (!orthogonal(e.points)) return false;
            return true;
        }());
        TEST("loop: routes contained", contained(l));
        TEST("loop: deterministic",
             sameLayout(l, layoutFunctionGraph(cfg.blocks(), cfg.edges(),
                                               0x1000, 0x1005, inputsFor(cfg),
                                               m)));
    }

    // ---- 3. Nested branches widen columns ----
    {
        DisassemblyCFG cfg;
        std::vector<CfgInsn> insns = {
            insn(0x1000, 0, "CMP", "rax, rbx"),
            insn(0x1001, 1, "JE", "0x1006"),  // outer else
            insn(0x1002, 2, "CMP", "rcx, rdx"),
            insn(0x1003, 3, "JE", "0x1005"),  // inner else
            insn(0x1004, 4, "JMP", "0x1007"), // inner then -> end
            insn(0x1005, 5, "JMP", "0x1007"), // inner else -> end
            insn(0x1006, 6, "MOV", "rax, 0"), // outer else
            insn(0x1007, 7, "RET", ""),
        };
        cfg.build(insns, {0x1000});
        GraphLayout l = layoutFunctionGraph(cfg.blocks(), cfg.edges(), 0x1000,
                                            0x1007, inputsFor(cfg), m);
        int maxCol = 0;
        for (const auto& n : l.nodes) maxCol = std::max(maxCol, n.col);
        TEST("nested: columns widen (maxCol>=2)", maxCol >= 2);
        TEST("nested: no node overlap", noOverlap(l));
        TEST("nested: all routes orthogonal", [&] {
            for (const auto& e : l.edges)
                if (!orthogonal(e.points)) return false;
            return true;
        }());
        TEST("nested: routes contained", contained(l));
        TEST("nested: deterministic",
             sameLayout(l, layoutFunctionGraph(cfg.blocks(), cfg.edges(),
                                               0x1000, 0x1007, inputsFor(cfg),
                                               m)));
    }

    // ---- 4. Overspill: 7 overlapping long edges share the outer lane ----
    {
        DisassemblyCFG cfg;
        std::vector<CfgInsn> insns;
        for (int i = 0; i < 7; ++i) {
            char ops[16];
            snprintf(ops, sizeof(ops), "0x2000");
            insns.push_back(insn(0x1000 + i, i, "JMP", ops));
        }
        insns.push_back(insn(0x2000, 7, "RET", ""));
        cfg.build(insns, {0x1000});
        GraphLayout l = layoutFunctionGraph(cfg.blocks(), cfg.edges(), 0x1000,
                                            0x2000, inputsFor(cfg), m);
        int maxLane = 0, routed = 0;
        for (const auto& e : l.edges) {
            if (e.toBlock < 0) continue;
            ++routed;
            maxLane = std::max(maxLane, e.lane);
        }
        TEST("overspill: 7 routed edges", routed == 7);
        TEST("overspill: lanes capped",
             maxLane <= cfg::kCFAMaxTracks - 1);
        TEST("overspill: no node overlap", noOverlap(l));
        TEST("overspill: routes contained", contained(l));
    }

    // ---- 5. Edge cases ----
    {
        DisassemblyCFG cfg;
        GraphLayout l = layoutFunctionGraph(cfg.blocks(), cfg.edges(), 0x1000,
                                            0x1000, {}, m);
        TEST("empty: no nodes, no edges",
             l.nodes.empty() && l.edges.empty());
    }
    {
        DisassemblyCFG cfg;
        std::vector<CfgInsn> insns = {insn(0x1000, 0, "RET", "")};
        cfg.build(insns, {0x1000});
        GraphLayout l = layoutFunctionGraph(cfg.blocks(), cfg.edges(), 0x1000,
                                            0x1000, inputsFor(cfg), m);
        TEST("single ret block: 1 node", l.nodes.size() == 1);
        TEST("single ret block: only a stub edge",
             l.edges.size() == 1 && l.edges[0].toBlock < 0);
    }
    {
        // Out-of-range function window selects nothing.
        DisassemblyCFG cfg;
        std::vector<CfgInsn> insns = {insn(0x1000, 0, "RET", "")};
        cfg.build(insns, {0x1000});
        GraphLayout l = layoutFunctionGraph(cfg.blocks(), cfg.edges(), 0x9000,
                                            0x9FFF, inputsFor(cfg), m);
        TEST("window miss: empty layout",
             l.nodes.empty() && l.edges.empty());
    }

    std::cout << "=== FunctionGraphLayout: " << passed << "/" << total
              << " passed ===" << std::endl;
    return passed == total ? 0 : 1;
}

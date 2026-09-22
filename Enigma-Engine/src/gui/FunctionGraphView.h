#pragma once

#include <cfg/DisassemblyCFG.h>
#include <cfg/FunctionGraphLayout.h>

#include <QAbstractScrollArea>

#include <cstdint>
#include <functional>

// Function Graph view: basic-block flowchart of a single function.
//
// Custom-painted QAbstractScrollArea following the DisassemblyFieldView
// house style (no QGraphicsView dependency). The widget owns its
// cfg::GraphLayout plus per-node text lines; all text knowledge stays with
// the caller via BlockTextProvider so this file never touches ProgramDB.
//
// Phase 2: static painting + scroll + zoom. Selection/navigation sync is
// Phase 3; MainWindow dock wiring is Phase 4.
class FunctionGraphView : public QAbstractScrollArea {
    Q_OBJECT
public:
    // Returns every text line for a block (blockIndex into
    // cfg::DisassemblyCFG::blocks()). First line of the entry block is
    // rendered as the node title.
    using BlockTextProvider = std::function<QStringList(int blockIndex)>;

    explicit FunctionGraphView(QWidget* parent = nullptr);

    // Copies the model output and rebuilds the layout. Empty selection or
    // null provider clears the view.
    void setGraph(const cfg::DisassemblyCFG* cfg, uint64_t funcStart,
                  uint64_t funcEnd, BlockTextProvider text);
    void clear();

    void setZoom(double z);
    double zoom() const { return zoom_; }
    QSize contentSize() const { return QSize(layout_.width, layout_.height); }

    bool empty() const { return layout_.nodes.empty(); }
    // Entry address of the laid-out function (0 when empty). Test hook.
    uint64_t graphFunctionEntry() const { return hasGraph_ ? funcStart_ : 0; }
    // Block index containing addr, or -1. Test hook.
    int blockForAddress(uint64_t addr) const;

    // Highlights the node containing addr without rebuilding. No-op when
    // the address is outside the laid-out function.
    void setCurrentAddress(uint64_t addr);

public slots:
    void zoomIn();
    void zoomOut();
    void zoomReset();
    void zoomFit();

signals:
    void nodeSelected(int blockIndex);
    void navigateRequested(uint64_t addr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void rebuild();
    void updateScrollBars();
    // Scroll so the content center lands on the viewport center.
    void centerOnContent();
    QRect nodeRectPx(int i) const;
    int nodeAt(const QPoint& pos) const;
    // Centering offset (device px) applied when content is smaller than the
    // viewport; added to every content coordinate.
    void contentOrigin(double& ox, double& oy) const;

    const cfg::DisassemblyCFG* cfg_ = nullptr; // not owned; copied below
    cfg::DisassemblyCFG cfgCopy_;
    uint64_t funcStart_ = 0;
    uint64_t funcEnd_ = 0;
    BlockTextProvider text_;
    cfg::GraphLayout layout_;
    std::vector<QStringList> nodeLines_; // aligned with layout_.nodes
    cfg::GraphMetrics usedMetrics_; // metrics the live layout was built with
    bool hasGraph_ = false;
    double zoom_ = 1.0;
    int selectedBlock_ = -1; // block index, -1 = none
    int currentBlock_ = -1;  // block index containing the synced cursor
    bool panning_ = false;   // drag-pan in progress
    QPoint panLast_;         // last drag position (device px)
    QPoint pressPos_;        // left-press position (pan-vs-click decision)
    int pressBlock_ = -1;    // node under the left press, -1 = background
    bool pressMoved_ = false;
};

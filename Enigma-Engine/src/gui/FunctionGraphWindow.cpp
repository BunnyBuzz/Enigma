#include "FunctionGraphWindow.h"

#include "FunctionGraphView.h"

#include <QGuiApplication>
#include <QScreen>
#include <QToolBar>

namespace {

constexpr int kChromeW = 24;
constexpr int kChromeH = 96;

} // namespace

FunctionGraphWindow::FunctionGraphWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle(tr("Function Graph"));
    setObjectName(QStringLiteral("FUNCTION GRAPH WINDOW"));
    resize(1100, 800);

    graphView_ = new FunctionGraphView(this);
    setCentralWidget(graphView_);

    auto* toolbar = addToolBar(tr("graph"));
    toolbar->setObjectName(QStringLiteral("graph-toolbar"));
    toolbar->setMovable(false);
    toolbar->setFloatable(false);

    auto* zoomInAct = toolbar->addAction(tr("Zoom In (+)"));
    zoomInAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Plus));
    connect(zoomInAct, &QAction::triggered, graphView_,
            &FunctionGraphView::zoomIn);

    auto* zoomOutAct = toolbar->addAction(tr("Zoom Out (-)"));
    zoomOutAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));
    connect(zoomOutAct, &QAction::triggered, graphView_,
            &FunctionGraphView::zoomOut);

    auto* fitAct = toolbar->addAction(tr("Fit to Window (0)"));
    fitAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));
    connect(fitAct, &QAction::triggered, graphView_,
            &FunctionGraphView::zoomFit);

    auto* resetAct = toolbar->addAction(tr("100%"));
    connect(resetAct, &QAction::triggered, graphView_,
            &FunctionGraphView::zoomReset);

    connect(graphView_, &FunctionGraphView::navigateRequested, this,
            &FunctionGraphWindow::navigateRequested);
    connect(graphView_, &FunctionGraphView::nodeSelected, this,
            &FunctionGraphWindow::nodeSelected);
}

void FunctionGraphWindow::setGraph(const cfg::DisassemblyCFG* cfg,
                                   uint64_t funcStart, uint64_t funcEnd,
                                   BlockTextProvider text) {
    graphView_->setGraph(cfg, funcStart, funcEnd, std::move(text));
    if (graphView_->empty()) {
        setWindowTitle(tr("Function Graph"));
    } else {
        setWindowTitle(
            tr("Function Graph — 0x%1").arg(funcStart, 0, 16));
    }
}

void FunctionGraphWindow::clear() {
    graphView_->clear();
    setWindowTitle(tr("Function Graph"));
}

bool FunctionGraphWindow::empty() const {
    return !graphView_ || graphView_->empty();
}

uint64_t FunctionGraphWindow::graphFunctionEntry() const {
    return graphView_ ? graphView_->graphFunctionEntry() : 0;
}

void FunctionGraphWindow::setCurrentAddress(uint64_t addr) {
    if (graphView_) graphView_->setCurrentAddress(addr);
}

void FunctionGraphWindow::fitWindowToContent() {
    const QSize content =
        graphView_ ? graphView_->contentSize() : QSize();
    if (content.isEmpty()) return;
    const QRect available =
        screen() ? screen()->availableGeometry()
                 : QGuiApplication::primaryScreen()->availableGeometry();
    const int w = std::min(content.width() + kChromeW,
                           available.width() * 4 / 5);
    const int h = std::min(content.height() + kChromeH,
                           available.height() * 4 / 5);
    resize(std::max(w, 400), std::max(h, 300));
}

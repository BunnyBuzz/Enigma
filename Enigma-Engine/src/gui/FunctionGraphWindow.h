#pragma once

#include <cfg/DisassemblyCFG.h>
#include <cfg/FunctionGraphLayout.h>

#include "FunctionGraphView.h"

#include <QMainWindow>

#include <cstdint>
#include <functional>

// Top-level Function Graph window: a real window (min/max/close, resizable)
// hosting a FunctionGraphView plus a zoom toolbar. Owned by MainWindow, which
// feeds it the same graph data as the docked view.
class FunctionGraphWindow : public QMainWindow {
    Q_OBJECT
public:
    using BlockTextProvider = FunctionGraphView::BlockTextProvider;

    explicit FunctionGraphWindow(QWidget* parent = nullptr);

    void setGraph(const cfg::DisassemblyCFG* cfg, uint64_t funcStart,
                  uint64_t funcEnd, BlockTextProvider text);
    void clear();
    void setCurrentAddress(uint64_t addr);

    FunctionGraphView* graphView() const { return graphView_; }
    bool empty() const;
    uint64_t graphFunctionEntry() const;

    // Size the window to the content (bounded by the available screen).
    void fitWindowToContent();

signals:
    void navigateRequested(uint64_t addr);
    void nodeSelected(int blockIndex);

private:
    FunctionGraphView* graphView_;
};

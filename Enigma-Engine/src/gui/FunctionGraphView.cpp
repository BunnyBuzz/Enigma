#include "FunctionGraphView.h"

#include "EditorTheme.h"

#include <QApplication>
#include <QFontMetrics>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QScrollBar>
#include <QWheelEvent>

#include <algorithm>
#include <cmath>

namespace {

constexpr double kMinZoom = 0.25;
constexpr double kMaxZoom = 3.0;
constexpr int kHeadLen = 8;
constexpr int kHeadHalfW = 4;

} // namespace

FunctionGraphView::FunctionGraphView(QWidget* parent)
    : QAbstractScrollArea(parent) {
    setFrameShape(QFrame::NoFrame);
    viewport()->setBackgroundRole(QPalette::NoRole);
    setMouseTracking(true);
}

void FunctionGraphView::setGraph(const cfg::DisassemblyCFG* cfg,
                                 uint64_t funcStart, uint64_t funcEnd,
                                 BlockTextProvider text) {
    if (!cfg || !text || cfg->empty()) {
        clear();
        return;
    }
    cfgCopy_ = *cfg;
    cfg_ = &cfgCopy_;
    funcStart_ = funcStart;
    funcEnd_ = funcEnd;
    text_ = std::move(text);
    hasGraph_ = true;
    rebuild();
}

void FunctionGraphView::clear() {
    cfg_ = nullptr;
    text_ = nullptr;
    layout_ = cfg::GraphLayout{};
    nodeLines_.clear();
    hasGraph_ = false;
    selectedBlock_ = -1;
    currentBlock_ = -1;
    updateScrollBars();
    viewport()->update();
}

void FunctionGraphView::setZoom(double z) {
    const double nz = std::clamp(z, kMinZoom, kMaxZoom);
    if (std::abs(nz - zoom_) < 1e-9) return;
    zoom_ = nz;
    updateScrollBars();
    viewport()->update();
}

void FunctionGraphView::zoomIn() {
    setZoom(zoom_ * 1.25);
}

void FunctionGraphView::zoomOut() {
    setZoom(zoom_ / 1.25);
}

void FunctionGraphView::zoomReset() {
    setZoom(1.0);
}

void FunctionGraphView::zoomFit() {
    if (layout_.width <= 0 || layout_.height <= 0) return;
    const double zx =
        static_cast<double>(viewport()->width()) / layout_.width;
    const double zy =
        static_cast<double>(viewport()->height()) / layout_.height;
    setZoom(std::min(zx, zy));
    centerOnContent();
}

void FunctionGraphView::rebuild() {
    layout_ = cfg::GraphLayout{};
    nodeLines_.clear();
    selectedBlock_ = -1;
    currentBlock_ = -1;
    panning_ = false;
    if (!hasGraph_ || !cfg_) {
        updateScrollBars();
        viewport()->update();
        return;
    }

    // Measure with the real monospace font so node rects fit their text.
    const QFont font = EditorTheme::baseFont();
    const QFontMetrics fm(font);
    const int charW = std::max(1, fm.horizontalAdvance(QLatin1Char('0')));

    // Per-block text first: line counts feed the layout, maxChars too.
    struct BlockText {
        int block = -1;
        QStringList lines;
    };
    std::vector<BlockText> texts;
    for (const cfg::CfgBlock& b : cfg_->blocks()) {
        if (b.startAddr < funcStart_ || b.startAddr > funcEnd_) continue;
        QStringList lines = text_(b.index);
        // Guarantee a non-empty node even for blocks with no text.
        if (lines.isEmpty())
            lines << QStringLiteral("0x%1").arg(b.startAddr, 8, 16,
                                                QLatin1Char('0'));
        texts.push_back({b.index, lines});
    }
    if (texts.empty()) {
        updateScrollBars();
        viewport()->update();
        return;
    }

    std::vector<cfg::GraphBlockInput> inputs;
    inputs.reserve(texts.size());
    for (const BlockText& t : texts) {
        cfg::GraphBlockInput in;
        in.blockIndex = t.block;
        in.lineCount = t.lines.size();
        // Real pixel measurement, not per-character math: proportional
        // fallback glyphs (comments, odd symbols) break '0'-advance math
        // and let text overflow its node. Round up to whole characters.
        int maxPx = 0;
        for (const QString& ln : t.lines)
            maxPx = std::max(maxPx, fm.horizontalAdvance(ln));
        in.maxChars = (maxPx + charW - 1) / charW;
        inputs.push_back(in);
    }

    cfg::GraphMetrics metrics;
    metrics.lineHeight = std::max(1, fm.height());
    metrics.charWidth = charW;
    metrics.padX = charW;
    metrics.padY = fm.ascent() / 2 + 2;
    metrics.colGap = charW * 6;
    metrics.rowGap = fm.height() * 2;

    layout_ = cfg::layoutFunctionGraph(cfg_->blocks(), cfg_->edges(),
                                       funcStart_, funcEnd_, inputs, metrics);
    usedMetrics_ = metrics;

    nodeLines_.resize(layout_.nodes.size());
    for (size_t i = 0; i < layout_.nodes.size(); ++i) {
        const int bi = layout_.nodes[i].blockIndex;
        for (const BlockText& t : texts) {
            if (t.block == bi) {
                nodeLines_[i] = t.lines;
                break;
            }
        }
    }

    // New graph opens with its center on the viewport center, not pinned
    // to the top-left corner.
    centerOnContent();
}

void FunctionGraphView::updateScrollBars() {
    const int vpW = viewport()->width();
    const int vpH = viewport()->height();
    const int contentW = static_cast<int>(std::ceil(layout_.width * zoom_));
    const int contentH = static_cast<int>(std::ceil(layout_.height * zoom_));
    // Free canvas: when content overflows, allow a full viewport of margin
    // past every edge so no part of the map is ever stuck out of reach.
    // (Fitting content stays locked at 0 with the centering origin.)
    if (contentW <= vpW) {
        horizontalScrollBar()->setRange(0, 0);
    } else {
        horizontalScrollBar()->setRange(-vpW, contentW);
    }
    horizontalScrollBar()->setPageStep(std::max(1, vpW));
    horizontalScrollBar()->setSingleStep(std::max(1, contentW / 100));
    if (contentH <= vpH) {
        verticalScrollBar()->setRange(0, 0);
    } else {
        verticalScrollBar()->setRange(-vpH, contentH);
    }
    verticalScrollBar()->setPageStep(std::max(1, vpH));
    verticalScrollBar()->setSingleStep(std::max(1, contentH / 100));
}

void FunctionGraphView::centerOnContent() {
    updateScrollBars();
    const int vpW = viewport()->width();
    const int vpH = viewport()->height();
    const int contentW = static_cast<int>(std::ceil(layout_.width * zoom_));
    const int contentH = static_cast<int>(std::ceil(layout_.height * zoom_));
    horizontalScrollBar()->setValue((contentW - vpW) / 2);
    verticalScrollBar()->setValue((contentH - vpH) / 2);
    viewport()->update();
}

QRect FunctionGraphView::nodeRectPx(int i) const {
    const cfg::GraphNode& n = layout_.nodes[static_cast<size_t>(i)];
    double ox = 0.0, oy = 0.0;
    contentOrigin(ox, oy);
    const int x = static_cast<int>(std::floor(n.x * zoom_ + ox)) -
                  horizontalScrollBar()->value();
    const int y = static_cast<int>(std::floor(n.y * zoom_ + oy)) -
                  verticalScrollBar()->value();
    const int w = static_cast<int>(std::ceil(n.w * zoom_));
    const int h = static_cast<int>(std::ceil(n.h * zoom_));
    return QRect(x, y, w, h);
}

void FunctionGraphView::contentOrigin(double& ox, double& oy) const {
    ox = std::max(0.0, (viewport()->width() - layout_.width * zoom_) / 2.0);
    oy = std::max(0.0, (viewport()->height() - layout_.height * zoom_) / 2.0);
}

void FunctionGraphView::paintEvent(QPaintEvent* event) {
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), EditorTheme::backgroundColor());

    if (!hasGraph_ || layout_.nodes.empty()) {
        painter.setPen(QColor(0x88, 0x88, 0x88));
        painter.drawText(viewport()->rect(), Qt::AlignCenter,
                         QStringLiteral("No function graph"));
        return;
    }

    const QFont font = EditorTheme::baseFont();
    QFont scaledFont = font;
    // Keep text crisp: draw glyphs at the zoomed size.
    if (font.pointSizeF() > 0) {
        scaledFont.setPointSizeF(std::max(1.0, font.pointSizeF() * zoom_));
    } else if (font.pixelSize() > 0) {
        scaledFont.setPixelSize(
            std::max(1, static_cast<int>(std::round(font.pixelSize() *
                                                    zoom_))));
    }
    painter.setFont(scaledFont);
    // Float metrics + the layout's own line stride: integer QFontMetrics
    // rounds per zoom level, which accumulates over tall nodes and pushes
    // trailing lines outside their rect. Deriving both origin and stride
    // from the layout numbers keeps text inside by construction.
    const QFontMetricsF fmf(scaledFont);
    const double ascent = fmf.ascent();
    const double stride = usedMetrics_.lineHeight * zoom_;

    const QRect vis = event->rect();
    double ox = 0.0, oy = 0.0;
    contentOrigin(ox, oy);
    const double sx = horizontalScrollBar()->value();
    const double sy = verticalScrollBar()->value();

    // ---- Edges under nodes ----
    for (const cfg::GraphEdge& e : layout_.edges) {
        if (e.points.size() < 2) continue;
        QColor color = EditorTheme::cfaColor(e.kind);
        const bool dashed = (e.kind == cfg::EdgeKind::Computed ||
                             e.kind == cfg::EdgeKind::ComputedCall ||
                             e.kind == cfg::EdgeKind::Conditional);
        QPen pen(color, 2, dashed ? Qt::DashLine : Qt::SolidLine,
                 Qt::FlatCap, Qt::MiterJoin);
        pen.setCosmetic(true);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        QPolygonF poly;
        for (const cfg::GraphPoint& p : e.points) {
            const double dx = p.x * zoom_ + ox - sx;
            const double dy = p.y * zoom_ + oy - sy;
            poly << QPointF(dx, dy);
        }
        painter.drawPolyline(poly);

        // Arrowhead on the final segment (exit stubs get none).
        if (e.toBlock >= 0 && poly.size() >= 2) {
            const QPointF tip = poly.back();
            const QPointF prev = poly[poly.size() - 2];
            QPointF dir = tip - prev;
            const double len = std::hypot(dir.x(), dir.y());
            if (len > 1e-6) {
                dir /= len;
                const QPointF normal(-dir.y(), dir.x());
                const double hl = kHeadLen * zoom_;
                const double hw = kHeadHalfW * zoom_;
                QPolygonF head;
                head << tip << (tip - dir * hl + normal * hw)
                     << (tip - dir * hl - normal * hw);
                painter.setPen(Qt::NoPen);
                painter.setBrush(color);
                painter.drawPolygon(head);
            }
        }
    }

    // ---- Nodes over edges ----
    for (size_t i = 0; i < layout_.nodes.size(); ++i) {
        const QRect r = nodeRectPx(static_cast<int>(i));
        if (!r.intersects(vis)) continue;
        const int bi = layout_.nodes[i].blockIndex;
        const bool isEntry = (i == 0);
        const bool isSelected = (bi == selectedBlock_);
        const bool isCurrent = (bi == currentBlock_);

        painter.setPen(Qt::NoPen);
        QColor fill = EditorTheme::blockTint(layout_.nodes[i].row & 1);
        if (isSelected)
            fill = EditorTheme::primarySelectionColor().lighter(165);
        else if (isCurrent)
            fill = EditorTheme::caretLineColor();
        painter.setBrush(fill);
        painter.drawRoundedRect(r, 6.0, 6.0);

        QPen borderPen(isEntry ? EditorTheme::cfaColor(cfg::EdgeKind::Unconditional)
                               : QColor(0x8a, 0x93, 0xa0),
                       isEntry ? 2 : 1);
        borderPen.setCosmetic(true);
        painter.setPen(borderPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(r, 6.0, 6.0);

        painter.setPen(EditorTheme::textColor());
        const QStringList& lines = nodeLines_[i];
        // Text origin mirrors the layout metrics: left pad in, first
        // baseline one ascent below the top pad; advance by the exact
        // layout stride (see above) so lines never drift out of the rect.
        const double tx = r.x() + usedMetrics_.padX * zoom_;
        double ty = r.y() + usedMetrics_.padY * zoom_ + ascent;
        for (const QString& ln : lines) {
            painter.drawText(QPointF(tx, ty), ln);
            ty += stride;
        }
    }
}

void FunctionGraphView::resizeEvent(QResizeEvent* event) {
    QAbstractScrollArea::resizeEvent(event);
    updateScrollBars();
}

void FunctionGraphView::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        // Zoom anchored under the cursor.
        const QPointF cursor = event->position();
        const double sx = horizontalScrollBar()->value();
        const double sy = verticalScrollBar()->value();
        const double ax = (cursor.x() + sx) / zoom_;
        const double ay = (cursor.y() + sy) / zoom_;
        const double nz = std::clamp(zoom_ * (event->angleDelta().y() > 0 ? 1.15 : 1.0 / 1.15),
                                     kMinZoom, kMaxZoom);
        if (std::abs(nz - zoom_) > 1e-9) {
            zoom_ = nz;
            updateScrollBars();
            horizontalScrollBar()->setValue(
                static_cast<int>(std::round(ax * nz - cursor.x())));
            verticalScrollBar()->setValue(
                static_cast<int>(std::round(ay * nz - cursor.y())));
            viewport()->update();
        }
        event->accept();
        return;
    }
    QAbstractScrollArea::wheelEvent(event);
}

int FunctionGraphView::nodeAt(const QPoint& pos) const {
    if (!hasGraph_ || layout_.nodes.empty()) return -1;
    for (size_t i = 0; i < layout_.nodes.size(); ++i) {
        if (nodeRectPx(static_cast<int>(i)).contains(pos))
            return layout_.nodes[i].blockIndex;
    }
    return -1;
}

int FunctionGraphView::blockForAddress(uint64_t addr) const {
    if (!hasGraph_ || !cfg_) return -1;
    for (const cfg::GraphNode& n : layout_.nodes) {
        const cfg::CfgBlock& b = cfgCopy_.blocks()[static_cast<size_t>(n.blockIndex)];
        if (addr >= b.startAddr && addr <= b.endAddr) return n.blockIndex;
    }
    return -1;
}

void FunctionGraphView::setCurrentAddress(uint64_t addr) {
    const int nb = blockForAddress(addr);
    if (nb == currentBlock_) return;
    currentBlock_ = nb;
    viewport()->update();
}

void FunctionGraphView::mousePressEvent(QMouseEvent* event) {
    // Middle-drag pans immediately. Left-drag pans once past a small
    // threshold so a plain click still selects; the decision happens on
    // move/release, which makes dragging work from anywhere — node or not.
    if (event->button() == Qt::MiddleButton) {
        panning_ = true;
        panLast_ = event->pos();
        viewport()->setCursor(Qt::ClosedHandCursor);
        viewport()->grabMouse();
        event->accept();
        return;
    }
    if (event->button() == Qt::LeftButton) {
        pressPos_ = event->pos();
        pressBlock_ = nodeAt(event->pos());
        pressMoved_ = false;
    }
    QAbstractScrollArea::mousePressEvent(event);
}

void FunctionGraphView::mouseDoubleClickEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        const int nb = nodeAt(event->pos());
        if (nb >= 0 && cfg_) {
            const cfg::CfgBlock& b =
                cfgCopy_.blocks()[static_cast<size_t>(nb)];
            if (b.startAddr != 0) emit navigateRequested(b.startAddr);
        }
    }
    QAbstractScrollArea::mouseDoubleClickEvent(event);
}

void FunctionGraphView::mouseMoveEvent(QMouseEvent* event) {
    if (panning_) {
        const QPoint delta = event->pos() - panLast_;
        panLast_ = event->pos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() -
                                        delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() -
                                      delta.y());
        event->accept();
        return;
    }
    if ((event->buttons() & Qt::LeftButton) && !pressMoved_) {
        if ((event->pos() - pressPos_).manhattanLength() >
            QApplication::startDragDistance()) {
            pressMoved_ = true;
            panning_ = true;
            panLast_ = event->pos();
            viewport()->setCursor(Qt::ClosedHandCursor);
            viewport()->grabMouse();
            event->accept();
            return;
        }
    }
    viewport()->setCursor(nodeAt(event->pos()) >= 0 ? Qt::PointingHandCursor
                                                    : Qt::ArrowCursor);
    QAbstractScrollArea::mouseMoveEvent(event);
}

void FunctionGraphView::mouseReleaseEvent(QMouseEvent* event) {
    if (panning_ &&
        (event->button() == Qt::LeftButton ||
         event->button() == Qt::MiddleButton)) {
        panning_ = false;
        viewport()->releaseMouse();
        viewport()->setCursor(Qt::ArrowCursor);
        pressBlock_ = -1;
        event->accept();
        return;
    }
    // Plain left click (no drag): select the node under the cursor.
    if (event->button() == Qt::LeftButton && !pressMoved_ &&
        pressBlock_ >= 0) {
        if (pressBlock_ != selectedBlock_) {
            selectedBlock_ = pressBlock_;
            viewport()->update();
        }
        emit nodeSelected(pressBlock_);
    }
    pressBlock_ = -1;
    QAbstractScrollArea::mouseReleaseEvent(event);
}

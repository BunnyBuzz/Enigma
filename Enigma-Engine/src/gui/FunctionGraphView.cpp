#include "FunctionGraphView.h"

#include "EditorTheme.h"

#include <QApplication>
#include <QFontMetrics>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRegularExpression>
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
    setFocusPolicy(Qt::StrongFocus);
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
    emit zoomChanged(zoom_);
}

void FunctionGraphView::zoomIn() {
    setZoom(zoom_ * 1.25);
}

void FunctionGraphView::zoomOut() {
    setZoom(zoom_ / 1.25);
}

void FunctionGraphView::zoomReset() {
    setZoom(1.0);
    centerOnContent();
}

void FunctionGraphView::zoomFit() {
    if (layout_.width <= 0 || layout_.height <= 0) return;
    const int pad = 32;
    const double zx =
        static_cast<double>(std::max(1, viewport()->width() - pad)) / layout_.width;
    const double zy =
        static_cast<double>(std::max(1, viewport()->height() - pad)) / layout_.height;
    setZoom(std::clamp(std::min(zx, zy), kMinZoom, 1.25));
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
    metrics.colGap = charW * 8;
    metrics.rowGap = fm.height() * 3;

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
    // Free canvas with bounded margin so edges stay reachable without letting
    // the whole graph disappear off-screen.
    if (contentW <= vpW) {
        horizontalScrollBar()->setRange(0, 0);
    } else {
        const int marginX = vpW / 3;
        horizontalScrollBar()->setRange(-marginX, contentW - vpW + marginX);
    }
    horizontalScrollBar()->setPageStep(std::max(1, vpW));
    horizontalScrollBar()->setSingleStep(std::max(24, contentW / 40));
    if (contentH <= vpH) {
        verticalScrollBar()->setRange(0, 0);
    } else {
        const int marginY = vpH / 3;
        verticalScrollBar()->setRange(-marginY, contentH - vpH + marginY);
    }
    verticalScrollBar()->setPageStep(std::max(1, vpH));
    verticalScrollBar()->setSingleStep(std::max(24, contentH / 40));
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
                 Qt::RoundCap, Qt::RoundJoin);
        pen.setCosmetic(true);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        QPolygonF poly;
        for (const cfg::GraphPoint& p : e.points) {
            const double dx = p.x * zoom_ + ox - sx;
            const double dy = p.y * zoom_ + oy - sy;
            poly << QPointF(dx, dy);
        }

        // Stop the polyline stroke at the arrowhead base so the 2px stroke
        // never pokes past the sharp tip of the arrowhead triangle.
        if (e.toBlock >= 0 && poly.size() >= 2) {
            const QPointF tip = poly.back();
            const QPointF prev = poly[poly.size() - 2];
            QPointF dir = tip - prev;
            const double len = std::hypot(dir.x(), dir.y());
            if (len > 1e-6) {
                dir /= len;
                const double hl = kHeadLen * zoom_;
                const double hw = kHeadHalfW * zoom_;
                QPolygonF drawPoly = poly;
                if (len > hl) {
                    drawPoly.back() = tip - dir * (hl * 0.75);
                }
                painter.drawPolyline(drawPoly);

                const QPointF normal(-dir.y(), dir.x());
                QPolygonF head;
                head << tip << (tip - dir * hl + normal * hw)
                     << (tip - dir * hl - normal * hw);
                painter.setPen(Qt::NoPen);
                painter.setBrush(color);
                painter.drawPolygon(head);
            } else {
                painter.drawPolyline(poly);
            }
        } else {
            painter.drawPolyline(poly);
            // Draw a subtle terminal T-bar on Return/Computed exit stubs.
            if (poly.size() >= 2) {
                const QPointF tip = poly.back();
                const double barHalf = 6.0 * zoom_;
                painter.drawLine(QPointF(tip.x() - barHalf, tip.y()),
                                 QPointF(tip.x() + barHalf, tip.y()));
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

        QColor borderColor = QColor(0x8a, 0x93, 0xa0);
        int borderW = 1;
        if (isSelected || isCurrent) {
            borderColor = EditorTheme::cfaColor(cfg::EdgeKind::Unconditional);
            borderW = 2;
        } else if (isEntry) {
            borderColor = EditorTheme::cfaColor(cfg::EdgeKind::Unconditional);
            borderW = 2;
        }
        QPen borderPen(borderColor, borderW);
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
        // Zoom anchored under the cursor (accounting for centering origin).
        const QPointF cursor = event->position();
        double ox = 0.0, oy = 0.0;
        contentOrigin(ox, oy);
        const double sx = horizontalScrollBar()->value();
        const double sy = verticalScrollBar()->value();
        const double ax = (cursor.x() + sx - ox) / zoom_;
        const double ay = (cursor.y() + sy - oy) / zoom_;
        const double nz = std::clamp(zoom_ * (event->angleDelta().y() > 0 ? 1.15 : 1.0 / 1.15),
                                     kMinZoom, kMaxZoom);
        if (std::abs(nz - zoom_) > 1e-9) {
            zoom_ = nz;
            updateScrollBars();
            double nox = 0.0, noy = 0.0;
            contentOrigin(nox, noy);
            horizontalScrollBar()->setValue(
                static_cast<int>(std::round(ax * nz + nox - cursor.x())));
            verticalScrollBar()->setValue(
                static_cast<int>(std::round(ay * nz + noy - cursor.y())));
            viewport()->update();
            emit zoomChanged(zoom_);
        }
        event->accept();
        return;
    }
    if (event->modifiers() & Qt::ShiftModifier) {
        const int delta = event->angleDelta().y() != 0
                              ? event->angleDelta().y()
                              : event->angleDelta().x();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta);
        event->accept();
        return;
    }
    QAbstractScrollArea::wheelEvent(event);
}

void FunctionGraphView::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_Plus:
    case Qt::Key_Equal:
        zoomIn();
        event->accept();
        return;
    case Qt::Key_Minus:
        zoomOut();
        event->accept();
        return;
    case Qt::Key_0:
        zoomFit();
        event->accept();
        return;
    case Qt::Key_1:
        zoomReset();
        event->accept();
        return;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        if (selectedBlock_ >= 0 && cfg_ &&
            selectedBlock_ < static_cast<int>(cfgCopy_.blocks().size())) {
            const uint64_t addr = cfgCopy_.blocks()[static_cast<size_t>(selectedBlock_)].startAddr;
            if (addr != 0) emit navigateRequested(addr);
            event->accept();
            return;
        }
        break;
    default:
        break;
    }
    QAbstractScrollArea::keyPressEvent(event);
}

int FunctionGraphView::nodeIndexAt(const QPoint& pos) const {
    if (!hasGraph_ || layout_.nodes.empty()) return -1;
    for (size_t i = 0; i < layout_.nodes.size(); ++i) {
        if (nodeRectPx(static_cast<int>(i)).contains(pos))
            return static_cast<int>(i);
    }
    return -1;
}

int FunctionGraphView::nodeAt(const QPoint& pos) const {
    const int idx = nodeIndexAt(pos);
    return idx >= 0 ? layout_.nodes[static_cast<size_t>(idx)].blockIndex : -1;
}

uint64_t FunctionGraphView::addressAt(const QPoint& pos, bool preferTarget) const {
    const int idx = nodeIndexAt(pos);
    if (idx < 0 || !cfg_) return 0;
    const int bi = layout_.nodes[static_cast<size_t>(idx)].blockIndex;
    const cfg::CfgBlock& b = cfgCopy_.blocks()[static_cast<size_t>(bi)];
    uint64_t fallback = b.startAddr;

    if (idx >= static_cast<int>(nodeLines_.size())) return fallback;
    const QStringList& lines = nodeLines_[static_cast<size_t>(idx)];
    if (lines.isEmpty()) return fallback;

    const QRect r = nodeRectPx(idx);
    const double stride = usedMetrics_.lineHeight * zoom_;
    const double localY = pos.y() - r.y() - usedMetrics_.padY * zoom_;
    const int lineIdx = (stride > 0.0)
        ? std::clamp(static_cast<int>(std::floor(localY / stride)),
                     0, static_cast<int>(lines.size()) - 1)
        : 0;

    const QString& ln = lines[lineIdx];
    static const QRegularExpression hexRe(QStringLiteral("0x([0-9a-fA-F]+)"));
    auto it = hexRe.globalMatch(ln);
    uint64_t lineAddr = 0;
    if (it.hasNext()) {
        auto m0 = it.next();
        if (m0.capturedStart() <= 4) {
            bool ok = false;
            uint64_t v = m0.captured(1).toULongLong(&ok, 16);
            if (ok && v != 0) lineAddr = v;
        }
    }

    if (preferTarget) {
        // Check if cursor clicked specifically on an operand hex target (after the leading address),
        // or if this line is a direct branch/call edge in the CFG.
        const double charW = std::max(1.0, usedMetrics_.charWidth * zoom_);
        const double localX = pos.x() - r.x() - usedMetrics_.padX * zoom_;
        const int col = std::max(0, static_cast<int>(std::floor(localX / charW)));

        auto matchIt = hexRe.globalMatch(ln);
        bool first = true;
        while (matchIt.hasNext()) {
            auto m = matchIt.next();
            if (first && lineAddr != 0 && m.capturedStart() <= 4) {
                first = false;
                continue;
            }
            first = false;
            if (col >= m.capturedStart() - 1 && col <= m.capturedEnd() + 1) {
                bool ok = false;
                uint64_t tgt = m.captured(1).toULongLong(&ok, 16);
                if (ok && tgt != 0) return tgt;
            }
        }
        // Also follow branch/call target if clicking the instruction operand region.
        if (lineAddr != 0 && col > 12) {
            for (const cfg::CfaEdge& e : cfgCopy_.edges()) {
                if (e.fromAddr == lineAddr && e.toAddr != 0) {
                    return e.toAddr;
                }
            }
        }
    }

    return lineAddr != 0 ? lineAddr : fallback;
}

int FunctionGraphView::blockForAddress(uint64_t addr) const {
    if (!hasGraph_ || !cfg_) return -1;
    for (const cfg::GraphNode& n : layout_.nodes) {
        const cfg::CfgBlock& b = cfgCopy_.blocks()[static_cast<size_t>(n.blockIndex)];
        if (addr >= b.startAddr && addr <= b.endAddr) return n.blockIndex;
    }
    return -1;
}

void FunctionGraphView::ensureBlockVisible(int blockIndex) {
    if (blockIndex < 0 || !hasGraph_) return;
    for (size_t i = 0; i < layout_.nodes.size(); ++i) {
        if (layout_.nodes[i].blockIndex == blockIndex) {
            const QRect r = nodeRectPx(static_cast<int>(i));
            const QRect vp = viewport()->rect();
            if (vp.isEmpty() || vp.intersects(r)) return;
            const QPoint delta = r.center() - vp.center();
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() + delta.y());
            return;
        }
    }
}

void FunctionGraphView::setCurrentAddress(uint64_t addr) {
    const int nb = blockForAddress(addr);
    if (nb == currentBlock_) return;
    currentBlock_ = nb;
    ensureBlockVisible(nb);
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
        const uint64_t addr = addressAt(event->pos(), true);
        if (addr != 0) {
            emit navigateRequested(addr);
            event->accept();
            return;
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
        viewport()->setCursor(nodeAt(event->pos()) >= 0 ? Qt::PointingHandCursor
                                                        : Qt::ArrowCursor);
        pressBlock_ = -1;
        event->accept();
        return;
    }
    // Plain left click (no drag): select the node under the cursor and sync address.
    if (event->button() == Qt::LeftButton && !pressMoved_ &&
        pressBlock_ >= 0) {
        if (pressBlock_ != selectedBlock_) {
            selectedBlock_ = pressBlock_;
            viewport()->update();
        }
        emit nodeSelected(pressBlock_);
        const uint64_t addr = addressAt(event->pos(), false);
        if (addr != 0) emit addressSelected(addr);
    }
    pressBlock_ = -1;
    QAbstractScrollArea::mouseReleaseEvent(event);
}

#include "FunctionExplorer.h"
#include <QHeaderView>
#include <functional>

FunctionExplorer::FunctionExplorer(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 4);

    tree_ = new QTreeWidget(this);
    tree_->setHeaderLabels({tr("Name"), tr("Address")});
    tree_->setToolTip(tr("Function Explorer — double-click to navigate to a function"));
    tree_->setAlternatingRowColors(true);
    tree_->header()->setStretchLastSection(false);
    tree_->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    tree_->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    layout->addWidget(tree_);

    filter_ = new QLineEdit(this);
    filter_->setPlaceholderText(tr("Filter..."));
    filter_->setToolTip(tr("Type to filter functions by name"));
    filter_->setContentsMargins(4, 0, 4, 0);
    layout->addWidget(filter_);

    auto* toolsLayout = new QHBoxLayout;
    toolsLayout->setContentsMargins(4, 0, 4, 0);
    autoClearCb_ = new QCheckBox(tr("Auto clear index"), this);
    autoClearCb_->setToolTip(tr("Automatically clear function index when loading a new binary"));
    clearBtn_ = new QPushButton(tr("Clear index"), this);
    clearBtn_->setToolTip(tr("Manually clear the cached function index"));
    clearBtn_->setFixedHeight(24);
    toolsLayout->addWidget(autoClearCb_);
    toolsLayout->addWidget(clearBtn_);
    layout->addLayout(toolsLayout);

    connect(tree_, &QTreeWidget::itemDoubleClicked,
            this, &FunctionExplorer::onItemDoubleClicked);
    connect(tree_, &QTreeWidget::itemClicked,
            this, &FunctionExplorer::onItemClicked);
    connect(filter_, &QLineEdit::textChanged,
            this, &FunctionExplorer::onFilterChanged);
}

void FunctionExplorer::clear() {
    tree_->clear();
}

QTreeWidgetItem* FunctionExplorer::addCategory(const QString& name) {
    auto* item = new QTreeWidgetItem(tree_);
    item->setText(0, name);
    item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    item->setExpanded(true);
    return item;
}

QTreeWidgetItem* FunctionExplorer::addSubCategory(QTreeWidgetItem* parent, const QString& name) {
    auto* item = new QTreeWidgetItem(parent);
    item->setText(0, name);
    item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    item->setExpanded(true);
    return item;
}

void FunctionExplorer::addEntry(QTreeWidgetItem* parent, uint64_t addr, const QString& name) {
    auto* item = new QTreeWidgetItem(parent);
    item->setText(0, name);
    item->setText(1, QString("0x%1").arg(addr, 0, 16));
    item->setData(0, Qt::UserRole, static_cast<qlonglong>(addr));
}

void FunctionExplorer::setFilter(const QString& text) {
    filter_->setText(text);
}

void FunctionExplorer::onItemDoubleClicked(QTreeWidgetItem* item, int) {
    if (!item || item->childCount() > 0) return;
    uint64_t addr = static_cast<uint64_t>(item->data(0, Qt::UserRole).toLongLong());
    emit functionSelected(addr, item->text(0));
}

void FunctionExplorer::onFilterChanged(const QString& text) {
    tree_->blockSignals(true);
    tree_->setUpdatesEnabled(false);
    std::function<bool(QTreeWidgetItem*)> applyFilter = [&](QTreeWidgetItem* item) {
        bool selfMatch = text.isEmpty() ||
            item->text(0).contains(text, Qt::CaseInsensitive) ||
            item->text(1).contains(text, Qt::CaseInsensitive);
        bool childVisible = false;
        for (int j = 0; j < item->childCount(); ++j) {
            if (applyFilter(item->child(j))) childVisible = true;
        }
        bool visible = selfMatch || childVisible;
        item->setHidden(!visible);
        return visible;
    };
    for (int i = 0; i < tree_->topLevelItemCount(); ++i)
        applyFilter(tree_->topLevelItem(i));
    tree_->setUpdatesEnabled(true);
    tree_->blockSignals(false);
}

void FunctionExplorer::onItemClicked(QTreeWidgetItem* item, int) {
    if (!item || item->childCount() > 0) return;
    uint64_t addr = static_cast<uint64_t>(item->data(0, Qt::UserRole).toLongLong());
    emit functionSelected(addr, item->text(0));
}

void FunctionExplorer::highlightAddress(uint64_t addr) {
    tree_->blockSignals(true);
    std::function<bool(QTreeWidgetItem*)> findAddr = [&](QTreeWidgetItem* item) {
        if (item->childCount() == 0) {
            uint64_t itemAddr = static_cast<uint64_t>(item->data(0, Qt::UserRole).toLongLong());
            if (itemAddr == addr) {
                tree_->setCurrentItem(item);
                tree_->scrollToItem(item);
                return true;
            }
            return false;
        }
        for (int j = 0; j < item->childCount(); ++j) {
            if (findAddr(item->child(j))) return true;
        }
        return false;
    };
    for (int i = 0; i < tree_->topLevelItemCount(); ++i) {
        if (findAddr(tree_->topLevelItem(i))) break;
    }
    tree_->blockSignals(false);
}

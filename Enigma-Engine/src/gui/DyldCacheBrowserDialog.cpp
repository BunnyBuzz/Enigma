#include "DyldCacheBrowserDialog.h"

#include <ghidra/BinaryLoader.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>

DyldCacheBrowserDialog::DyldCacheBrowserDialog(ghidra::BinaryLoader* loader, QWidget* parent)
    : QDialog(parent), loader_(loader) {
    setWindowTitle(tr("Dyld Shared Cache Images"));
    resize(720, 480);

    auto* layout = new QVBoxLayout(this);
    tree_ = new QTreeWidget(this);
    tree_->setHeaderLabels({tr("Name"), tr("VM Address"), tr("File Offset"), tr("Size")});
    tree_->setAlternatingRowColors(true);
    tree_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tree_->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    for (int i = 1; i < 4; ++i)
        tree_->header()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    layout->addWidget(tree_);

    if (loader_) {
        for (const auto& img : loader_->getDyldCacheImages()) {
            auto* item = new QTreeWidgetItem(tree_);
            item->setCheckState(0, Qt::Unchecked);
            item->setText(0, QString::fromStdString(img.name));
            item->setText(1, QString("0x%1").arg(img.address, 0, 16));
            item->setText(2, QString("0x%1").arg(img.fileOffset, 0, 16));
            item->setText(3, QString("0x%1").arg(img.size, 0, 16));
        }
    }
    tree_->sortByColumn(0, Qt::AscendingOrder);
    tree_->setSortingEnabled(true);

    filter_ = new QLineEdit(this);
    filter_->setPlaceholderText(tr("Filter..."));
    layout->addWidget(filter_);
    connect(filter_, &QLineEdit::textChanged, this, &DyldCacheBrowserDialog::onFilterChanged);

    auto* btnRow = new QHBoxLayout;
    auto* allBtn = new QPushButton(tr("Select All"), this);
    auto* noneBtn = new QPushButton(tr("Select None"), this);
    connect(allBtn, &QPushButton::clicked, this, &DyldCacheBrowserDialog::onSelectAll);
    connect(noneBtn, &QPushButton::clicked, this, &DyldCacheBrowserDialog::onSelectNone);
    btnRow->addWidget(allBtn);
    btnRow->addWidget(noneBtn);
    btnRow->addStretch();
    auto* extractBtn = new QPushButton(tr("Extract..."), this);
    extractBtn->setToolTip(tr("Save checked images as .dylib files"));
    connect(extractBtn, &QPushButton::clicked, this, &DyldCacheBrowserDialog::onExtract);
    btnRow->addWidget(extractBtn);
    auto* loadBtn = new QPushButton(tr("Load"), this);
    loadBtn->setToolTip(tr("Reload the session targeting the first checked image"));
    loadBtn->setDefault(true);
    connect(loadBtn, &QPushButton::clicked, this, &DyldCacheBrowserDialog::onLoad);
    btnRow->addWidget(loadBtn);
    auto* closeBtn = new QPushButton(tr("Close"), this);
    connect(closeBtn, &QPushButton::clicked, this, &DyldCacheBrowserDialog::reject);
    btnRow->addWidget(closeBtn);
    layout->addLayout(btnRow);
}

QStringList DyldCacheBrowserDialog::checkedNames() const {
    QStringList names;
    for (int i = 0; i < tree_->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = tree_->topLevelItem(i);
        if (item->checkState(0) == Qt::Checked)
            names << item->text(0);
    }
    return names;
}

void DyldCacheBrowserDialog::onFilterChanged(const QString& text) {
    for (int i = 0; i < tree_->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = tree_->topLevelItem(i);
        bool match = text.isEmpty() ||
            item->text(0).contains(text, Qt::CaseInsensitive);
        item->setHidden(!match);
    }
}

void DyldCacheBrowserDialog::onSelectAll() {
    for (int i = 0; i < tree_->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = tree_->topLevelItem(i);
        if (!item->isHidden()) item->setCheckState(0, Qt::Checked);
    }
}

void DyldCacheBrowserDialog::onSelectNone() {
    for (int i = 0; i < tree_->topLevelItemCount(); ++i)
        tree_->topLevelItem(i)->setCheckState(0, Qt::Unchecked);
}

void DyldCacheBrowserDialog::onExtract() {
    if (!loader_) return;
    QStringList names = checkedNames();
    if (names.isEmpty()) {
        QMessageBox::information(this, tr("Extract"),
            tr("Check one or more images first."));
        return;
    }
    QString dir = QFileDialog::getExistingDirectory(this, tr("Extract dylibs to"));
    if (dir.isEmpty()) return;
    int ok = 0;
    QStringList failed;
    for (const QString& name : names) {
        std::vector<uint8_t> bytes =
            loader_->getDyldCacheImageBytes(name.toStdString());
        QString base = QFileInfo(name).fileName();
        if (bytes.empty() || base.isEmpty()) { failed << name; continue; }
        QFile out(dir + "/" + base);
        if (!out.open(QIODevice::WriteOnly) ||
            out.write(reinterpret_cast<const char*>(bytes.data()),
                      static_cast<qint64>(bytes.size())) != static_cast<qint64>(bytes.size())) {
            failed << name;
            continue;
        }
        ++ok;
    }
    if (failed.isEmpty()) {
        QMessageBox::information(this, tr("Extract"),
            tr("Extracted %1 image(s) to %2.").arg(ok).arg(dir));
    } else {
        QMessageBox::warning(this, tr("Extract"),
            tr("Extracted %1 image(s); failed: %2.").arg(ok).arg(failed.join(", ")));
    }
}

void DyldCacheBrowserDialog::onLoad() {
    QStringList names = checkedNames();
    if (names.isEmpty() && tree_->currentItem())
        names << tree_->currentItem()->text(0);
    if (names.isEmpty()) {
        QMessageBox::information(this, tr("Load"),
            tr("Check an image (or select a row) to load it."));
        return;
    }
    selectedImage_ = names.first();
    accept();
}

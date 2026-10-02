#pragma once

#include <QDialog>
#include <QTreeWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

namespace ghidra {
class BinaryLoader;
}

// G2 (GP-7046): modal multi-select browser over the embedded dylibs of a
// dyld shared cache. The loader must outlive the dialog.
class DyldCacheBrowserDialog : public QDialog {
    Q_OBJECT
public:
    explicit DyldCacheBrowserDialog(ghidra::BinaryLoader* loader, QWidget* parent = nullptr);

    // Image chosen via the Load button (empty when the dialog was
    // dismissed or only used for extraction).
    QString selectedImage() const { return selectedImage_; }

private slots:
    void onFilterChanged(const QString& text);
    void onSelectAll();
    void onSelectNone();
    void onExtract();
    void onLoad();

private:
    QStringList checkedNames() const;

    ghidra::BinaryLoader* loader_;
    QTreeWidget* tree_;
    QLineEdit* filter_;
    QString selectedImage_;
};

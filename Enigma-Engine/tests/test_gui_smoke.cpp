/**
 * Enigma Engine - GUI smoke test (offscreen platform, no display needed).
 * Covers the G-batch GUI widgets without launching the full MainWindow:
 *   - FunctionExplorer subfolders (G5): addSubCategory, recursive filter,
 *     highlightAddress into nested entries.
 *   - DyldCacheBrowserDialog (G2): image listing, filter, check + Load
 *     selection over a synthetic dyld shared cache.
 *
 * Run with: ctest -R enigma_test_gui_smoke --output-on-failure
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>
#include <cstdio>

#include <QApplication>
#include <QTreeWidgetItem>

#include "FunctionExplorer.h"
#include "DyldCacheBrowserDialog.h"
#include "ghidra/BinaryLoader.h"

int passed = 0, total = 0;
#define TEST(n, x) do { total++; if(x){std::cout<<"[PASS] "<<n<<"\n"<<std::flush;passed++;}else{std::cout<<"[FAIL] "<<n<<"\n"<<std::flush;} } while(0)

using namespace ghidra;

// ---------------------------------------------------------------- G5 explorer
static void testExplorerGrouping() {
    std::cout << "\n--- FunctionExplorer subfolders ---" << std::endl;
    FunctionExplorer explorer;
    QTreeWidgetItem* root = explorer.addCategory("Functions");
    QTreeWidgetItem* mainPkg = explorer.addSubCategory(root, "main");
    QTreeWidgetItem* fmtPkg = explorer.addSubCategory(root, "fmt");
    explorer.addEntry(mainPkg, 0x1000, "main.main");
    explorer.addEntry(mainPkg, 0x1010, "main.helper");
    explorer.addEntry(fmtPkg, 0x2000, "fmt.Println");
    explorer.addEntry(root, 0x3000, "sub_3000");

    TEST("explorer two folders", root->childCount() == 3);
    TEST("explorer folder entries",
         mainPkg->childCount() == 2 && fmtPkg->childCount() == 1);

    // Filter recurses into folders: "println" matches one nested entry.
    explorer.setFilter("println");
    bool fmtVisible = !fmtPkg->isHidden();
    bool mainHidden = mainPkg->isHidden();
    bool entryVisible = !fmtPkg->child(0)->isHidden();
    bool plainHidden = true;
    for (int i = 0; i < root->childCount(); ++i) {
        QTreeWidgetItem* ch = root->child(i);
        if (ch->childCount() == 0 && ch->text(0) == "sub_3000")
            plainHidden = ch->isHidden();
    }
    TEST("explorer filter shows matching folder", fmtVisible && entryVisible);
    TEST("explorer filter hides rest", mainHidden && plainHidden);

    explorer.setFilter("");
    TEST("explorer filter clear restores", !mainPkg->isHidden() && !fmtPkg->isHidden());

    // highlightAddress descends into folders.
    explorer.highlightAddress(0x1010);
    TEST("explorer highlight nested",
         explorer.treeWidget()->currentItem() == mainPkg->child(1));
    explorer.highlightAddress(0x3000);
    bool plainCurrent = false;
    for (int i = 0; i < root->childCount(); ++i) {
        QTreeWidgetItem* ch = root->child(i);
        if (ch->childCount() == 0 && ch->text(0) == "sub_3000")
            plainCurrent = (explorer.treeWidget()->currentItem() == ch);
    }
    TEST("explorer highlight top-level", plainCurrent);
}

// ------------------------------------------------------- G2 dyld browser dialog
static std::string writeMiniCache() {
    // Minimal classic dyld cache: 1 mapping + 2 image entries + names.
    // Embedded "image" bytes are arbitrary; the dialog only lists/carves.
    std::string p = "test_dyld_browser.bin";
    std::ofstream cf(p, std::ios::binary);
    auto wr64 = [&](uint64_t v) { cf.write((const char*)&v, 8); };
    auto wr32 = [&](uint32_t v) { cf.write((const char*)&v, 4); };
    auto padTo = [&](size_t off, size_t cur) {
        if (off > cur) {
            std::vector<uint8_t> pad(off - cur, 0);
            cf.write((const char*)pad.data(), pad.size());
        }
    };
    wr32(0x646C7964);   // 'dyld'
    wr32(0x40);         // mappingOffset
    wr32(1);            // mappingCount
    wr32(0x60);         // imagesOffset
    wr32(2);            // imagesCount
    padTo(0x18, 20);
    wr64(0x180000000);  // dyldBase
    padTo(0x40, 32);
    wr64(0x180000000); wr64(0x20000); wr64(0x1000); wr32(5); wr32(5);
    wr64(0x180000000); wr64(0); wr64(0); wr32(0xA0); wr32(0);
    wr64(0x180010000); wr64(0); wr64(0); wr32(0xC0); wr32(0);
    padTo(0xA0, 0xA0);
    const char* n1 = "/usr/lib/libSystem.B.dylib";
    const char* n2 = "/usr/lib/libobjc.A.dylib";
    cf.write(n1, strlen(n1) + 1);
    padTo(0xC0, 0xA0 + strlen(n1) + 1);
    cf.write(n2, strlen(n2) + 1);
    padTo(0x1000, 0xC0 + strlen(n2) + 1);
    std::vector<uint8_t> filler(0x200, 0xAB);
    cf.write((const char*)filler.data(), filler.size());
    cf.close();
    return p;
}

static void testDyldDialog(BinaryLoader* loader) {
    std::cout << "\n--- DyldCacheBrowserDialog ---" << std::endl;
    DyldCacheBrowserDialog dlg(loader);
    QTreeWidget* tree = dlg.findChild<QTreeWidget*>();
    TEST("dialog tree present", tree != nullptr);
    if (!tree) return;
    TEST("dialog lists two images", tree->topLevelItemCount() == 2);

    bool namesOk = false;
    for (int i = 0; i < tree->topLevelItemCount(); ++i) {
        QString n = tree->topLevelItem(i)->text(0);
        if (n == "/usr/lib/libSystem.B.dylib" || n == "/usr/lib/libobjc.A.dylib") {
            if (n == "/usr/lib/libSystem.B.dylib") namesOk = true;
        }
    }
    TEST("dialog image names", namesOk && tree->topLevelItemCount() == 2);

    bool sizesOk = true;
    for (int i = 0; i < tree->topLevelItemCount(); ++i) {
        if (tree->topLevelItem(i)->text(3).isEmpty()) sizesOk = false;
    }
    TEST("dialog size column filled", sizesOk);

    // Filter narrows to one row.
    QLineEdit* filter = dlg.findChild<QLineEdit*>();
    TEST("dialog filter present", filter != nullptr);
    if (filter) {
        filter->setText("objc");
        int visible = 0;
        for (int i = 0; i < tree->topLevelItemCount(); ++i) {
            if (!tree->topLevelItem(i)->isHidden()) ++visible;
        }
        TEST("dialog filter narrows", visible == 1);
        filter->setText("");
    }

    // Check first row + Load -> selectedImage().
    tree->topLevelItem(0)->setCheckState(0, Qt::Checked);
    bool invoked = QMetaObject::invokeMethod(&dlg, "onLoad", Qt::DirectConnection);
    TEST("dialog load invoked", invoked);
    TEST("dialog selected image",
         dlg.selectedImage() == "/usr/lib/libSystem.B.dylib");

    // Carve path behind Extract works on the same loader.
    auto bytes = loader->getDyldCacheImageBytes("/usr/lib/libSystem.B.dylib");
    TEST("dialog image bytes carve", !bytes.empty() && bytes[0] == 0xAB);
}

int main(int argc, char** argv) {
    qputenv("QT_QPA_PLATFORM", QByteArray("offscreen"));
    QApplication app(argc, argv);

    testExplorerGrouping();

    std::string cachePath = writeMiniCache();
    auto loader = ghidra::createLoader();
    bool loaded = loader->load(cachePath);
    TEST("browser fixture loads as dyld cache", loaded && loader->isDyldCache());
    if (loaded)
        testDyldDialog(loader.get());
    std::remove(cachePath.c_str());

    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "GUI Smoke Tests: " << passed << "/" << total << " passed." << std::endl;
    return (passed == total) ? 0 : 1;
}

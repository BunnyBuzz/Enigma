#include <QApplication>
#include <QStyleFactory>
#include <QStyleHints>
#include <QPalette>
#include <QMessageLogContext>
#include <QDebug>
#include "MainWindow.h"
#include <ghidra/DecompInterface.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <execinfo.h>
#include <unistd.h>
#endif
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <exception>

// ── Crash logging infrastructure ─────────────────────────────────────────

static FILE* g_crashLog = nullptr;
static FILE* crashLog() {
    if (!g_crashLog) {
#ifdef _WIN32
        g_crashLog = fopen("C:\\Users\\pc\\Desktop\\enigma_gui_crash.log", "a");
#else
        g_crashLog = fopen("enigma_gui_crash.log", "a");
#endif
    }
    return g_crashLog;
}

#define CRASHLOG(...) do { FILE* _f = crashLog(); if (_f) { fprintf(_f, __VA_ARGS__); fflush(_f); } } while(0)

static void printStack() {
#ifdef _WIN32
    void* stack[64];
    USHORT frames = CaptureStackBackTrace(1, 64, stack, NULL);
    CRASHLOG("  Stack (%d frames):\n", frames);
    for (USHORT i = 0; i < frames; ++i) {
        HMODULE hMod = nullptr;
        GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCWSTR)stack[i], &hMod);
        wchar_t modName[MAX_PATH] = L"<unknown>";
        if (hMod) GetModuleFileNameW(hMod, modName, MAX_PATH);
        CRASHLOG("    #%d: 0x%p  [%ls+0x%p]\n", i, stack[i], modName,
            (void*)((char*)stack[i] - (char*)hMod));
    }
#else
    void* stack[64];
    int frames = backtrace(stack, 64);
    CRASHLOG("  Stack (%d frames):\n", frames);
    char** symbols = backtrace_symbols(stack, frames);
    for (int i = 0; i < frames; ++i)
        CRASHLOG("    #%d: %s\n", i, symbols ? symbols[i] : "?");
    free(symbols);
#endif
}

#ifdef _WIN32
static LONG WINAPI vehHandler(EXCEPTION_POINTERS* ep) {
    // Only intercept hardware exceptions (access violations, etc.)
    DWORD code = ep->ExceptionRecord->ExceptionCode;
    if (code != EXCEPTION_ACCESS_VIOLATION &&
        code != EXCEPTION_ILLEGAL_INSTRUCTION &&
        code != EXCEPTION_STACK_OVERFLOW &&
        code != EXCEPTION_GUARD_PAGE) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    CRASHLOG("\n=== VEH EXCEPTION ===\n");
    CRASHLOG("ExceptionCode: 0x%08X\n", code);
    CRASHLOG("ExceptionAddress: 0x%p\n", ep->ExceptionRecord->ExceptionAddress);
    if (code == EXCEPTION_ACCESS_VIOLATION) {
        CRASHLOG("AccessViolation: %s at 0x%p\n",
            ep->ExceptionRecord->ExceptionInformation[0] ? "write" : "read",
            (void*)ep->ExceptionRecord->ExceptionInformation[1]);
    }
    HMODULE hCrashMod = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCWSTR)ep->ExceptionRecord->ExceptionAddress, &hCrashMod);
    wchar_t crashMod[MAX_PATH] = L"<unknown>";
    if (hCrashMod) GetModuleFileNameW(hCrashMod, crashMod, MAX_PATH);
    CRASHLOG("CrashModule: %ls\n", crashMod);
    CRASHLOG("CrashOffset: 0x%p\n",
        (void*)((char*)ep->ExceptionRecord->ExceptionAddress - (char*)hCrashMod));
    printStack();
    CRASHLOG("=== END VEH ===\n\n");
    fflush(g_crashLog);
    return EXCEPTION_CONTINUE_SEARCH;
}

static LONG WINAPI sehHandler(EXCEPTION_POINTERS* ep) {
    CRASHLOG("\n=== UNHANDLED SEH EXCEPTION ===\n");
    CRASHLOG("ExceptionCode: 0x%08X\n", ep->ExceptionRecord->ExceptionCode);
    CRASHLOG("ExceptionFlags: 0x%X\n", ep->ExceptionRecord->ExceptionFlags);
    CRASHLOG("ExceptionAddress: 0x%p\n", ep->ExceptionRecord->ExceptionAddress);
    if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
        CRASHLOG("AccessViolation: %s at 0x%p\n",
            ep->ExceptionRecord->ExceptionInformation[0] ? "write" : "read",
            (void*)ep->ExceptionRecord->ExceptionInformation[1]);
    }
    HMODULE hCrashMod = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCWSTR)ep->ExceptionRecord->ExceptionAddress, &hCrashMod);
    wchar_t crashMod[MAX_PATH] = L"<unknown>";
    if (hCrashMod) GetModuleFileNameW(hCrashMod, crashMod, MAX_PATH);
    CRASHLOG("CrashModule: %ls\n", crashMod);
    CRASHLOG("CrashOffset: 0x%p\n",
        (void*)((char*)ep->ExceptionRecord->ExceptionAddress - (char*)hCrashMod));
    printStack();
    CRASHLOG("=== END SEH ===\n\n");
    fclose(g_crashLog);
    g_crashLog = nullptr;
    return EXCEPTION_CONTINUE_SEARCH; // Let Windows show the error dialog
}

#endif // _WIN32

static void signalHandler(int sig) {
    CRASHLOG("\n=== SIGNAL %d ===\n", sig);
    printStack();
    CRASHLOG("=== END SIGNAL ===\n\n");
    fclose(g_crashLog);
    g_crashLog = nullptr;
    std::_Exit(EXIT_FAILURE);
}

static void terminateHandler() {
    CRASHLOG("\n=== UNHANDLED C++ EXCEPTION (terminate) ===\n");
    if (std::current_exception()) {
        try { throw; }
        catch (const std::exception& e) {
            CRASHLOG("what(): %s\n", e.what());
        }
        catch (...) {
            CRASHLOG("unknown exception type\n");
        }
    }
    printStack();
    CRASHLOG("=== END TERMINATE ===\n\n");
    fclose(g_crashLog);
    g_crashLog = nullptr;
    std::_Exit(EXIT_FAILURE);
}

#ifdef _WIN32
static void purecallHandler() {
    CRASHLOG("\n=== PURE VIRTUAL FUNCTION CALL ===\n");
    printStack();
    CRASHLOG("=== END PURE ===\n\n");
    fclose(g_crashLog);
    g_crashLog = nullptr;
    std::_Exit(EXIT_FAILURE);
}

#endif // _WIN32

static void qtMessageHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg) {
    const char* level = "";
    switch (type) {
    case QtDebugMsg:    level = "DEBUG";    break;
    case QtInfoMsg:     level = "INFO";     break;
    case QtWarningMsg:  level = "WARN";     break;
    case QtCriticalMsg: level = "CRITICAL"; break;
    case QtFatalMsg:    level = "FATAL";    break;
    }
    CRASHLOG("[QT-%s] %s (%s:%d)\n", level, msg.toStdString().c_str(),
        ctx.file ? ctx.file : "?", ctx.line);
    if (type == QtFatalMsg) {
        printStack();
        fclose(g_crashLog);
        g_crashLog = nullptr;
    }
}

static void installCrashHandlers() {
    CRASHLOG("=== ENIGMA ENGINE START ===\n");
#ifdef _WIN32
    CRASHLOG("PID: %lu\n", GetCurrentProcessId());
    SYSTEM_INFO si; GetSystemInfo(&si);
    CRASHLOG("PageSize: %lu, MinAddr: %p, MaxAddr: %p\n",
        si.dwPageSize, si.lpMinimumApplicationAddress, si.lpMaximumApplicationAddress);
    // VEH fires before any other handler (more reliable than SetUnhandledExceptionFilter)
    AddVectoredExceptionHandler(1, vehHandler);
    SetUnhandledExceptionFilter(sehHandler);
#else
    CRASHLOG("PID: %ld\n", static_cast<long>(getpid()));
#endif
    CRASHLOG("\n");
    signal(SIGABRT, signalHandler);
    signal(SIGSEGV, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGILL, signalHandler);
    std::set_terminate(terminateHandler);
#ifdef _MSC_VER
    _set_purecall_handler(purecallHandler);
#endif
    qInstallMessageHandler(qtMessageHandler);
}

// ── Main ─────────────────────────────────────────────────────────────────

int main(int argc, char** argv) {
    installCrashHandlers();

    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));
#if QT_VERSION >= QT_VERSION_CHECK(6, 8, 0)
    QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Light);
#endif
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, QColor(0xf0, 0xf0, 0xf0));
    lightPalette.setColor(QPalette::WindowText, QColor(0x1e, 0x1e, 0x1e));
    lightPalette.setColor(QPalette::Base, QColor(0xff, 0xff, 0xff));
    lightPalette.setColor(QPalette::AlternateBase, QColor(0xf5, 0xf5, 0xf5));
    lightPalette.setColor(QPalette::ToolTipBase, QColor(0xff, 0xff, 0xdc));
    lightPalette.setColor(QPalette::ToolTipText, QColor(0x1e, 0x1e, 0x1e));
    lightPalette.setColor(QPalette::Text, QColor(0x1e, 0x1e, 0x1e));
    lightPalette.setColor(QPalette::Button, QColor(0xf0, 0xf0, 0xf0));
    lightPalette.setColor(QPalette::ButtonText, QColor(0x1e, 0x1e, 0x1e));
    lightPalette.setColor(QPalette::BrightText, Qt::white);
    lightPalette.setColor(QPalette::Link, QColor(0x00, 0x66, 0xcc));
    lightPalette.setColor(QPalette::Highlight, QColor(0x00, 0x78, 0xd4));
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);
    lightPalette.setColor(QPalette::PlaceholderText, QColor(0x80, 0x80, 0x80));
    lightPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(0x90, 0x90, 0x90));
    lightPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(0x90, 0x90, 0x90));
    lightPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(0x90, 0x90, 0x90));
    app.setPalette(lightPalette);
    app.setApplicationName("Enigma Engine");
    app.setOrganizationName("Enigma");

    if (!ghidra::DecompInterface::initializeLibrary()) {
        return 1;
    }

    MainWindow w;
    w.setWindowTitle("Enigma Engine");
    w.resize(1400, 850);
    w.showMaximized();

    if (std::getenv("ENIGMA_DUMP_LAYOUT")) {
        for (QObject* o : w.children()) {
            auto* d = qobject_cast<QDockWidget*>(o);
            if (!d) continue;
            QRect g = d->frameGeometry();
            std::cerr << "DOCK " << d->objectName().toStdString()
                      << " geo=" << g.x() << "," << g.y() << " " << g.width() << "x" << g.height()
                      << " floating=" << d->isFloating() << " visible=" << d->isVisible() << "\n";
        }
    }

    // Command-line: first arg is binary path to auto-load for debugging
    if (argc > 1) {
        QMetaObject::invokeMethod(&w, [&w, argv]() {
            w.loadBinary(QString::fromUtf8(argv[1]));
        }, Qt::QueuedConnection);
    }

    int ret = app.exec();
    ghidra::DecompInterface::shutdownLibrary();
    CRASHLOG("=== ENIGMA ENGINE EXIT (code=%d) ===\n", ret);
    fclose(g_crashLog);
    g_crashLog = nullptr;
    return ret;
}

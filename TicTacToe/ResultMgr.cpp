#include "ResultMgr.hpp"
#include <QCoreApplication>
#include <QDir>
#include <ResultChecker/ResultChecker.hpp>
#include <filesystem>
#ifndef _WIN32
    #include <dlfcn.h>
#endif
#include "../FileMap.hpp"
#ifdef __APPLE__
    #include "../ParseMach.hpp"
#endif
#ifdef __ANDROID__
    #include "../ParseElf.hpp"
#endif
#include "../LibMetadata.hpp"


/** Get path to dylib inside framework */
static std::string DylibPath(std::filesystem::path frameworkPath, bool fullPath) {
#ifdef __APPLE__
    std::string path = fullPath ? frameworkPath : frameworkPath.filename();
    path += "/";
    path += frameworkPath.stem(); // filename without extension
    return path;
#else
    return fullPath ? frameworkPath : frameworkPath.filename();
#endif
}

static QString GetSharedLibFolder() {
    QString exePath = QCoreApplication::applicationDirPath();
#ifdef __APPLE__
  #if TARGET_OS_IPHONE
    // iOS: @executable_path/Frameworks)
    QDir libDir(exePath);
    libDir.cd("Frameworks");
    return libDir.absolutePath();
  #else
    // macOS: @executable_path/../Frameworks
    QDir libDir(exePath);
    libDir.cd("..");
    libDir.cd("Frameworks");
    return libDir.absolutePath();
  #endif
#else
    // Linux, Android, Windows: @executable_path
    return exePath;
#endif
}

std::string GetResultCheckerPath() {
    std::string libsDir = GetSharedLibFolder().toStdString();
    printf("Libs dir: %s\n", libsDir.c_str());

    for (const auto& entry : std::filesystem::directory_iterator(libsDir)) {
        printf("\n## %s\n", entry.path().filename().c_str());

        std::string path = DylibPath(entry.path(), true); // keep path prefix
        FileMap file(path.c_str());
        std::string_view data = FindSegmentInFile(file.ptr(), LibMetadata_SYMBOL_NAME);
        if (data.empty())
            continue;

        // found a compatible library
        return DylibPath(entry.path(), false); // remove path prefix
    }

    abort(); // not found
}



ResultMgr::ResultMgr() : m_mask(9, '\0') {
    printf("ResultChecker loaded.\n");

    // load ResultChecker library
#ifdef _WIN32
    m_lib = LoadLibraryW(L"ResultChecker.dll");
    m_func_ptr = (decltype(&CheckForWin))GetProcAddress(m_lib, "CheckForWin");
#else
  #ifdef __APPLE__
    m_lib = dlopen("ResultChecker.framework/ResultChecker", RTLD_LAZY); // macOS, iOS
  #else
    m_lib = dlopen("libResultChecker.so", RTLD_LAZY); // Linux, Android
  #endif
    m_func_ptr = (decltype(&CheckForWin))dlsym(m_lib, "CheckForWin");
#endif
}

ResultMgr::~ResultMgr() {
    printf("ResultChecker unloaded.\n");

    // unload ResultChecker library
#ifdef _WIN32
    FreeLibrary(m_lib);
    m_lib = nullptr;
#else
    dlclose(m_lib);
    m_lib = nullptr;
#endif
    m_func_ptr = nullptr;
}

ResultMgr::State ResultMgr::check(const QByteArray& cells) {
    assert(cells.size() == 9);

    m_mask.fill('\0');
    GameState val = m_func_ptr(cells, /*out*/m_mask);

    return (State)val;
}

QByteArray ResultMgr::mask() {
    return m_mask;
}

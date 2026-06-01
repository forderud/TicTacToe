#include "ResultMgr.hpp"
#include <ResultChecker/ResultChecker.hpp>
#ifndef _WIN32
  #include <dlfcn.h>
#endif


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

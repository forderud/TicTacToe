#include "ResultMgr.hpp"
#include <ResultChecker/ResultChecker.hpp>
#ifndef _WIN32
  #include <dlfcn.h>
#endif


ResultMgr::ResultMgr() {
    printf("ResultChecker loaded.\n");

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

#ifdef _WIN32
    FreeLibrary(m_lib);
    m_lib = nullptr;
#else
    dlclose(m_lib);
    m_lib = nullptr;
#endif
    m_func_ptr = nullptr;
}

QVariantList ResultMgr::check(const QByteArray& cells) {
    assert(cells.size() == 9);
    QByteArray mask(9, '\0');
    auto val = m_func_ptr(cells, /*out*/mask);

    QVariantList result;
    result << (int)val;
    result << mask;
    return result;
}

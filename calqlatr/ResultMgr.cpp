#include "ResultMgr.hpp"
#include <ResultChecker/ResultChecker.hpp>
#ifndef _WIN32
  #include <dlfcn.h>
#endif


ResultChecker::ResultChecker() {
    printf("ResultChecker loaded.\n");

#ifdef _WIN32
    m_lib = LoadLibraryW(L"ResultChecker.dll");
    m_func_ptr = (decltype(&CheckForWin))GetProcAddress(m_lib, "CheckForWin");
#else
    m_lib = dlopen("ResultChecker.framework/ResultChecker", RTLD_LAZY);
    m_func_ptr = (decltype(&CheckForWin))dlsym(m_lib, "CheckForWin");
#endif
}

ResultChecker::~ResultChecker() {
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

int ResultChecker::check(QString cells) {
    assert(cells.size() == 9);
    char buffer[9] = {};
    for (int i = 0; i < 9; i++)
        buffer[i] = cells[i].cell();

    return m_func_ptr(buffer);
}

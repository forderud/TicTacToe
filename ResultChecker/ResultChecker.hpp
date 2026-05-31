#pragma once
#include <QByteArray>


extern "C" // avoid C++ name mangling
#ifdef _WIN32
  __declspec(dllexport)
#endif
int CheckForWin(const QByteArray& cells);

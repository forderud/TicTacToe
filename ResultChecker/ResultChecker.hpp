#pragma once


extern "C" // avoid C++ name mangling
#ifdef _WIN32
  __declspec(dllexport)
#endif
int CheckForWin(char cells[9]);

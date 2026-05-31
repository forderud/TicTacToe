#pragma once
#include <QByteArray>

enum class GameState {
    Ongoing,
    X_won,
    O_won,
    Tie,
};

extern "C" // avoid C++ name mangling
#ifdef _WIN32
  __declspec(dllexport)
#endif
int CheckForWin(const QByteArray& cells);

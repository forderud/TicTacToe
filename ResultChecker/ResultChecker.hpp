#pragma once
#include <QByteArray>

enum class GameState {
    Ongoing = 0,
    X_won,
    O_won,
    Tie,
};

extern "C" // avoid C++ name mangling
#ifdef _WIN32
  __declspec(dllexport)
#endif
GameState CheckForWin(const QByteArray& cells);

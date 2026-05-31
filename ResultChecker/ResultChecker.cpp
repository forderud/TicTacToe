#include <cassert>
#include <stdio.h>
#include "ResultChecker.hpp"


static GameState WinCheck(char item1, char item2, char item3) {
    if (item1 == ' ')
        return GameState::Ongoing; // not filled out yet

    if ((item1 == item2) && (item1 == item3)) {
        return item1 == 'X' ? GameState::X_won : GameState::O_won;
    }

    return GameState::Ongoing;
}

extern "C"
#ifndef _WIN32
  __attribute__ ((visibility ("default")))
#endif
GameState CheckForWin(const QByteArray& cells, QByteArray& mask) {
    // check for horizontal win
    for (int row = 0; row < 3; row++) {
        auto item1 = cells[3*row + 0];
        auto item2 = cells[3*row + 1];
        auto item3 = cells[3*row + 2];
        auto win = WinCheck(item1, item2, item3);
        if (win != GameState::Ongoing)
            return win;
    }

    // check for vertical win
    for (int col = 0; col < 3; col++) {
        auto item1 = cells[3*0 + col];
        auto item2 = cells[3*1 + col];
        auto item3 = cells[3*2 + col];
        auto win = WinCheck(item1, item2, item3);
        if (win != GameState::Ongoing)
            return win;
    }

    // check for diagonal win
    {
        auto item1 = cells[3*0 + 0];
        auto item2 = cells[3*1 + 1];
        auto item3 = cells[3*2 + 2];
        auto win = WinCheck(item1, item2, item3);
        if (win != GameState::Ongoing)
            return win;
    }
    {
        auto item1 = cells[3*0 + 2];
        auto item2 = cells[3*1 + 1];
        auto item3 = cells[3*2 + 0];
        auto win = WinCheck(item1, item2, item3);
        if (win != GameState::Ongoing)
            return win;
    }

    // check for tie
    bool tie = true;
    for (char cell: cells) {
        if (cell == ' ')
            tie = false; // still an empty cell
    }
    if (tie)
        return GameState::Tie;

    return GameState::Ongoing;
}


#ifndef _WIN32

__attribute__((constructor))
void LibraryLoading() {
    printf("ResultChecker library loaded.\n");
}

__attribute__((destructor))
void LibraryUnloading() {
    printf("ResultChecker library unloaded.\n");
}

#endif

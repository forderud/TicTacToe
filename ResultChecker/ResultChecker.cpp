#include <cassert>
#include <stdio.h>
#include "ResultChecker.hpp"


static int WinCheck(char item1, char item2, char item3) {
    if (item1 == ' ')
        return 0; // not filled out yet

    if ((item1 == item2) && (item1 == item3)) {
        return item1 == 'X' ? 1 : -1;
    }

    return 0;
}

extern "C"
#ifndef _WIN32
  __attribute__ ((visibility ("default")))
#endif
int CheckForWin(char cells[9]) {
    // check for horizontal win
    for (int row = 0; row < 3; row++) {
        auto item1 = cells[3*row + 0];
        auto item2 = cells[3*row + 1];
        auto item3 = cells[3*row + 2];
        int win = WinCheck(item1, item2, item3);
        if (win)
            return win;
    }

    // check for vertical win
    for (int col = 0; col < 3; col++) {
        auto item1 = cells[3*0 + col];
        auto item2 = cells[3*1 + col];
        auto item3 = cells[3*2 + col];
        int win = WinCheck(item1, item2, item3);
        if (win)
            return win;
    }

    // check for diagonal win
    {
        auto item1 = cells[3*0 + 0];
        auto item2 = cells[3*1 + 1];
        auto item3 = cells[3*2 + 2];
        int win = WinCheck(item1, item2, item3);
        if (win)
            return win;
    }
    {
        auto item1 = cells[3*0 + 2];
        auto item2 = cells[3*1 + 1];
        auto item3 = cells[3*2 + 0];
        int win = WinCheck(item1, item2, item3);
        if (win)
            return win;
    }

    return 0;
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

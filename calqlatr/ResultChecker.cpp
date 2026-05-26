#include "ResultChecker.hpp"

ResultChecker::ResultChecker() {
}

ResultChecker::~ResultChecker() {
}

static int WinCheck(QChar item1, QChar item2, QChar item3) {
    if (item1 == ' ')
        return 0; // not filled out yet

    if ((item1 == item2) && (item1 == item3)) {
        return item1 == 'x' ? 1 : -1;
    }

    return 0;
}

int ResultChecker::check(QString cells) {
    // check for horizontal win
    for (int row = 0; row < 3; row++) {
        QChar item1 = cells[3*row + 0];
        QChar item2 = cells[3*row + 1];
        QChar item3 = cells[3*row + 2];
        int win = WinCheck(item1, item2, item3);
        if (win)
            return win;
    }

    // check for vertical win
    for (int col = 0; col < 3; col++) {
        QChar item1 = cells[3*0 + col];
        QChar item2 = cells[3*1 + col];
        QChar item3 = cells[3*2 + col];
        int win = WinCheck(item1, item2, item3);
        if (win)
            return win;
    }

    // check for diagonal win
    {
        QChar item1 = cells[3*0 + 0];
        QChar item2 = cells[3*1 + 1];
        QChar item3 = cells[3*2 + 2];
        int win = WinCheck(item1, item2, item3);
        if (win)
            return win;
    }
    {
        QChar item1 = cells[3*0 + 2];
        QChar item2 = cells[3*1 + 1];
        QChar item3 = cells[3*2 + 0];
        int win = WinCheck(item1, item2, item3);
        if (win)
            return win;
    }

    return 0;
}

#include "ResultChecker.hpp"

ResultChecker::ResultChecker() {
}

ResultChecker::~ResultChecker() {
}

int ResultChecker::Check(QString cells) {
    // check for horizontal win
    for (int row = 0; row < 3; row++) {
        QChar item1 = cells[3*row + 0];
        QChar item2 = cells[3*row + 1];
        QChar item3 = cells[3*row + 2];
        if (item1 != ' ') {
            if ((item1 == item2) && (item1 == item3)) {
                return item1 == 'x' ? 1 : -1;
            }
        }
    }

    // check for vertical win
    for (int col = 0; col < 3; col++) {
        QChar item1 = cells[3*0 + col];
        QChar item2 = cells[3*1 + col];
        QChar item3 = cells[3*2 + col];
        if (item1 != ' ') {
            if ((item1 == item2) && (item1 == item3)) {
                return item1 == 'x' ? 1 : -1;
            }
        }
    }

    // TODO: Add diagonal check
    return 0;
}

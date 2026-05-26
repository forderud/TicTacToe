#include "ResultChecker.hpp"
#include <ResultChecker/ResultChecker.hpp>

ResultChecker::ResultChecker() {
    printf("ResultChecker loaded.\n");
}

ResultChecker::~ResultChecker() {
    printf("ResultChecker unloaded.\n");
}

int ResultChecker::check(QString cells) {
    char buffer[9] = {};
    for (int i = 0; i < 9; i++)
        buffer[i] = cells[i].cell();

    return CheckForWin(buffer);
}

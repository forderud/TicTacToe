import QtQml

QtObject {
    required property Display display

    function checkForWin(grid) {
        // convert game state to a string
        let state = ""
        for (let i = 0; i < 9; i++)
            state += grid.children[i].text

        // check if someone have won
        var checker = Qt.createQmlObject('ResultChecker {}', this);
        let res = checker.check(state)
        if (res > 0) {
            display.displayText(("X won"))
            // reset game
            for (let i = 0; i < 9; i++)
                grid.children[i].text = " "

        } else if (res < 0) {
            display.displayText(("O won"))
            // reset game
            for (let i = 0; i < 9; i++)
                grid.children[i].text = " "
        }
    }
}

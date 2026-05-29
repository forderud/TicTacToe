import QtQml

QtObject {
    required property Display display

    function checkForWin(grid) {
        // convert game state to a string
        let state = ""
        for (let i = 0; i < 9; i++)
            state += grid.children[i].text

        // check if someone have won
        let checker = Qt.createQmlObject('ResultMgr {}', this);
        let res = checker.check(state)
        if (res === ResultMgr.X_won) {
            display.displayText(("X won"))
            // reset game
            for (let i = 0; i < 9; i++)
                grid.children[i].text = " "
        } else if (res === ResultMgr.O_won) {
            display.displayText(("O won"))
            // reset game
            for (let i = 0; i < 9; i++)
                grid.children[i].text = " "
        } else if (res === ResultMgr.Tie) {
            display.displayText(("Tie"))
            // reset game
            for (let i = 0; i < 9; i++)
                grid.children[i].text = " "
        }

        // unload ResultChecker
        checker.destroy()
    }
}

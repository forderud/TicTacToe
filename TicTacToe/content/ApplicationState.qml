import QtQml

QtObject {
    required property Display display

    property Timer resetTimer: Timer {
        property var gridRef
        interval: 1000 // 1 second
        repeat: false

        onTriggered: {
            gridRef.reset()
        }
    }

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
            resetTimer.gridRef = grid
            resetTimer.start() // schedule game reset
        } else if (res === ResultMgr.O_won) {
            display.displayText(("O won"))
            resetTimer.gridRef = grid
            resetTimer.start() // schedule game reset
        } else if (res === ResultMgr.Tie) {
            display.displayText(("Tie"))
            resetTimer.gridRef = grid
            resetTimer.start() // schedule game reset
        }

        // unload ResultChecker
        checker.destroy()
    }
}

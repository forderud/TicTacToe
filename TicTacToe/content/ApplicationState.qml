import QtQml
import QmlExtras

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
        let cells = ""
        for (let i = 0; i < 9; i++)
            cells += grid.children[i].text

        // check if someone have won
        let checker = Qt.createQmlObject('ResultMgr {}', this);
        let res = checker.check(cells)
        if (res.state === ResultMgr.X_won) {
            display.displayText("X won")
            resetTimer.gridRef = grid
            resetTimer.start() // schedule game reset
        } else if (res.state === ResultMgr.O_won) {
            display.displayText("O won")
            resetTimer.gridRef = grid
            resetTimer.start() // schedule game reset
        } else if (res.state === ResultMgr.Tie) {
            display.displayText("Tie")
            resetTimer.gridRef = grid
            resetTimer.start() // schedule game reset
        }

        // unload ResultChecker
        checker.destroy()
    }
}

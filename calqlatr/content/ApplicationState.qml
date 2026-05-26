import QtQml

QtObject {
    required property Display display

    function fieldPressed(grid) {
        // convert game state to a string
        let state = ""
        for (let i = 0; i < 9; i++)
            state += grid.children[i].text

        // check if someone have won
        var checker = Qt.createQmlObject('ResultChecker {}', this);
        let res = checker.Check(state)
        if (res > 0) {
            display.displayText(("X won"))
            for (let i = 0; i < 9; i++)
                grid.children[i].text = " "

        } else if (res < 0) {
            display.displayText(("O won"))
            for (let i = 0; i < 9; i++)
                grid.children[i].text = " "
        }
    }
}

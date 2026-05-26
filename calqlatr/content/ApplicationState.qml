import QtQml

QtObject {
    required property Display display

    function fieldPressed(grid) {
        let state = ""
        for (let i = 0; i < 9; i++)
            state += grid.children[i].text

        //let state = "xxx000   "
        let res = ResultChecker.Check(state)
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

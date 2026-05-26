
function fieldPressed(grid, display) {
    // check for horizontal win
    for (let row = 0; row < 3; row++) {
        let item1 = grid.children[3*row + 0]
        let item2 = grid.children[3*row + 1]
        let item3 = grid.children[3*row + 2]
        if (item1.text !== "") {
            if ((item1.text === item2.text) && (item1.text === item3.text)) {
                display.newTextLine(`Horizontal win at row ${row}`)
            }
        }
    }

    // check for vertical win
    for (let col = 0; col < 3; col++) {
        let item1 = grid.children[3*0 + col]
        let item2 = grid.children[3*1 + col]
        let item3 = grid.children[3*2 + col]
        if (item1.text !== "") {
            if ((item1.text === item2.text) && (item1.text === item3.text)) {
                display.newTextLine(`Vertical win at col ${col}`)
            }
        }
    }

    // TODO: Check for diagonal win
}

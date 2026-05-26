
function clearGrid(grid) {
    for (let row = 0; row < 3; row++) {
        for (let col = 0; col < 3; col++) {
            let item = grid.children[3*row + col]
            item.text = ""
        }
    }
}

function fieldPressed(grid, display) {
    // check for horizontal win
    for (let row = 0; row < 3; row++) {
        let item1 = grid.children[3*row + 0]
        let item2 = grid.children[3*row + 1]
        let item3 = grid.children[3*row + 2]
        if (item1.text !== "") {
            if ((item1.text === item2.text) && (item1.text === item3.text)) {
                display.displayText(`Horizontal win at row ${row}`)
                clearGrid(grid)
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
                display.displayText(`Vertical win at col ${col}`)
                clearGrid(grid)
            }
        }
    }

    // check for diagonal win
    {
        let item1 = grid.children[3*0 + 0]
        let item2 = grid.children[3*1 + 1]
        let item3 = grid.children[3*2 + 2]
        if (item1.text !== "") {
            if ((item1.text === item2.text) && (item1.text === item3.text)) {
                display.displayText(`Diagonal win`)
                clearGrid(grid)
            }
        }
    }
    {
        let item1 = grid.children[3*0 + 2]
        let item2 = grid.children[3*1 + 1]
        let item3 = grid.children[3*2 + 0]
        if (item1.text !== "") {
            if ((item1.text === item2.text) && (item1.text === item3.text)) {
                display.displayText(`Diagonal win`)
                clearGrid(grid)
            }
        }
    }
}

let accumulator = 0
let pendingOperator = ""
let lastButton = ""
let digits = ""

function isOperationDisabled(op, display) {
    if (digits !== "" && lastButton !== "=" && (op === "π" || op === "e"))
        return true
    if (digits === "" && !((op >= "0" && op <= "9") || op === "π" || op === "e" || op === "AC"))
        return true
    if (op === '=' && pendingOperator.length != 1)
        return true
    if (op === "AC" && display.isDisplayEmpty())
        return true

    return false
}

function digitPressed(op, display) {
    if (isOperationDisabled(op, display))
        return
    if (lastButton === "π" || lastButton === "e")
        return
    // handle mathematical constants
    if (op === "π") {
        lastButton = op
        digits = Math.PI.toPrecision(display.maxDigits - 1).toString()
        display.appendDigit(digits)
        return
    }
    if (op === "e") {
        lastButton = op
        digits = Math.E.toPrecision(display.maxDigits - 1).toString()
        display.appendDigit(digits)
        return
    }

    // append a digit to another digit
    if (lastButton.toString().length === 1 && ((lastButton >= "0" && lastButton <= "9")) ) {
        if (digits.length >= display.maxDigits)
            return
        digits = digits + op.toString()
        display.appendDigit(op.toString())
    // else just write a single digit to display
    } else {
        digits = op.toString()
        display.appendDigit(digits)
    }
    lastButton = op
}

function operatorPressed(op, display) {
    if (isOperationDisabled(op, display))
        return

    lastButton = op

    if (pendingOperator === "+") {
        digits = (Number(accumulator) + Number(digits.valueOf())).toString()
    }

    if (op === "+") {
        pendingOperator = op
        accumulator = digits.valueOf()
        digits = ""
        display.displayOperator(pendingOperator)
        return
    }

    accumulator = 0
    pendingOperator = ""

    if (op === "=") {
        display.newLine("=", Number(digits))
    }

    if (op === "AC") {
        display.allClear()
        accumulator = 0
        lastButton = ""
        digits = ""
        pendingOperator = ""
    }
}

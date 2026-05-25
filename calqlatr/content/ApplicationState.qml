import QtQml
import "calculator.js" as CalcEngine

QtObject {
    required property Display display

    function operatorPressed(operator) {
        CalcEngine.operatorPressed(operator, display);
    }
    function digitPressed(digit) {
        CalcEngine.digitPressed(digit, display);
    }
}

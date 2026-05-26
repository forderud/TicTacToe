import QtQml
import "calculator.js" as CalcEngine

QtObject {
    required property Display display

    function fieldPressed(grid) {
        CalcEngine.fieldPressed(grid, display);
    }
}

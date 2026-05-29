pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts

Item {
    id: controller

    required property ApplicationState applicationState

    readonly property int spacing: 5

    property bool lastWasX: false

    component PlayField: CalculatorButton {
        text: " "
        onClicked: {
            if (text !== " ")
                return; // cell already set

            text = lastWasX ? "O" : "X"
            lastWasX = !lastWasX
            controller.applicationState.checkForWin(mainGrid)
        }
    }

    GridLayout {
        id: mainGrid
        columns: 3
        columnSpacing: controller.spacing
        rowSpacing: controller.spacing

        PlayField {}
        PlayField {}
        PlayField {}

        PlayField {}
        PlayField {}
        PlayField {}

        PlayField {}
        PlayField {}
        PlayField {}
    }
}

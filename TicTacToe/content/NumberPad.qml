pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts

Item {
    id: controller

    required property ApplicationState applicationState

    readonly property int spacing: 5

    property bool lastWasX: false

    Component.onCompleted: {
        controller.applicationState.display.displayText("X starts")
    }

    component PlayField: CalculatorButton {
        text: " "
        onClicked: {
            if (text !== " ")
                return; // cell already set

            if (!applicationState.resetTimer.running) {
                controller.applicationState.display.displayText("")

                text = lastWasX ? "O" : "X"
                lastWasX = !lastWasX
                controller.applicationState.checkForWin(mainGrid)
            }
        }
    }

    GridLayout {
        id: mainGrid
        anchors.fill: parent
        columns: 3
        columnSpacing: controller.spacing
        rowSpacing: controller.spacing

        function reset() {
            // reset game state
            for (let i = 0; i < 9; i++) {
                children[i].text = " "
                children[i].background.color = "black"
            }

            controller.applicationState.display.displayText("")
        }

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

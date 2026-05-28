pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts

Item {
    id: controller

    required property ApplicationState applicationState

    readonly property color qtGreenColor: "#2CDE85"
    readonly property color backspaceRedColor: "#DE2C2C"
    readonly property int spacing: 5

    implicitWidth: mainGrid.width
    implicitHeight: mainGrid.height

    property bool lastWasX: false

    component PlayField: CalculatorButton {
        text: " "
        onClicked: {
            if (text !== " ")
                return; // cell already set

            text = lastWasX ? "o" : "x"
            lastWasX = !lastWasX
            controller.applicationState.checkForWin(mainGrid)
        }
    }

    Rectangle {
        id: numberPad
        anchors.fill: parent
        radius: 8
        color: "transparent"

        RowLayout {
            spacing: controller.spacing

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
    }
}

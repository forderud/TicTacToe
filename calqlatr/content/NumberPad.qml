pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts

Item {
    id: controller

    required property ApplicationState applicationState

    readonly property color qtGreenColor: "#2CDE85"
    readonly property color backspaceRedColor: "#DE2C2C"
    readonly property int spacing: 5

    property int portraitModeWidth: mainGrid.width

    implicitWidth: portraitModeWidth
    implicitHeight: mainGrid.height

    component DigitButton: CalculatorButton {
        onClicked: {
            text = "x"
        }
    }

    component OperatorButton: CalculatorButton {
        implicitWidth: 48
        textColor: controller.qtGreenColor

        onClicked: {
            controller.applicationState.operatorPressed(text);
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
                columns: 4
                columnSpacing: controller.spacing
                rowSpacing: controller.spacing

                PlayButton {
                    onClicked: {
                        controller.applicationState.fieldPressed(mainGrid)
                    }
                }
                DigitButton { text: "" }
                DigitButton { text: "" }
                DigitButton { text: "" }

                OperatorButton {
                    text: "+"
                }
                DigitButton { text: "" }
                DigitButton { text: "" }
                DigitButton { text: "" }

                OperatorButton {
                    text: "="
                }
                DigitButton { text: "" }
                DigitButton { text: "" }
                DigitButton { text: "" }
            }
        } // RowLayout
    }
}

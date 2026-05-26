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
            controller.applicationState.digitPressed(text);
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
                    text: "AC"
                    onClicked: {
                        controller.applicationState.operatorPressed(this.text);
                    }
                }

                DigitButton { text: "7" }
                DigitButton { text: "8" }
                DigitButton { text: "9" }                

                Item { Layout.fillWidth: true } // empty cell
                DigitButton { text: "4" }
                DigitButton { text: "5" }
                DigitButton { text: "6" }

                OperatorButton {
                    text: "="
                    implicitHeight: 81
                    Layout.rowSpan: 2
                }
                DigitButton { text: "1" }
                DigitButton { text: "2" }
                DigitButton { text: "3" }

                Item { Layout.fillWidth: true } // empty cell
                DigitButton { text: "0" }
                OperatorButton {
                    text: "+"
                    implicitWidth: 38
                }
            }
        } // RowLayout
    }
}

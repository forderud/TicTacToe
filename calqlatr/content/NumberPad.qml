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

    function updateDimmed() {
        for (let i = 0; i < mainGrid.children.length; i++) {
            mainGrid.children[i].dimmed = applicationState.isButtonDisabled(mainGrid.children[i].text);
        }
    }

    component DigitButton: CalculatorButton {
        onClicked: {
            controller.applicationState.digitPressed(text);
            controller.updateDimmed();
        }
    }

    component OperatorButton: CalculatorButton {
        dimmable: true
        implicitWidth: 48
        textColor: controller.qtGreenColor

        onClicked: {
            controller.applicationState.operatorPressed(text);
            controller.updateDimmed();
        }
    }

    Component.onCompleted: updateDimmed()

    Rectangle {
        id: numberPad
        anchors.fill: parent
        radius: 8
        color: "transparent"

        RowLayout {
            spacing: controller.spacing

            GridLayout {
                id: mainGrid
                columns: 5
                columnSpacing: controller.spacing
                rowSpacing: controller.spacing

                BackspaceButton {
                    onClicked: {
                        controller.applicationState.operatorPressed(this.text);
                        controller.updateDimmed();
                    }
                }

                DigitButton { text: "7" }
                DigitButton { text: "8" }
                DigitButton { text: "9" }                
                Item { Layout.fillWidth: true } // empty cell

                OperatorButton {
                    text: "AC"
                    textColor: controller.backspaceRedColor
                    accentColor: controller.backspaceRedColor
                }
                DigitButton { text: "4" }
                DigitButton { text: "5" }
                DigitButton { text: "6" }
                Item { Layout.fillWidth: true } // empty cell

                OperatorButton {
                    text: "="
                    implicitHeight: 81
                    Layout.rowSpan: 2
                }
                DigitButton { text: "1" }
                DigitButton { text: "2" }
                DigitButton { text: "3" }
                OperatorButton {
                    text: "−"
                    implicitWidth: 38
                }

                Item { Layout.fillWidth: true } // empty cell
                DigitButton { text: "0" }
                DigitButton {
                    text: "."
                    dimmable: true
                }
                OperatorButton {
                    text: "+"
                    implicitWidth: 38
                }
            }
        } // RowLayout
    }
}

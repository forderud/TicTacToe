pragma ComponentBehavior: Bound

import QtQuick

Item {
    id: display
    property int fontSize: 22
    readonly property int maxDigits: Math.min((width / fontSize) + 1, 9)
    readonly property color backgroundColor: "#262626"
    readonly property color qtGreenColor: "#2CDE85"
    property string displayedOperand: ""
    readonly property string errorString: qsTr("ERROR")
    readonly property bool isError: displayedOperand === errorString
    property bool enteringDigits: false

    function displayText(message) {
        calculationsListView.model.append({
                                              "operator": "",
                                              "operand": message
                                          });
    }

    function clear() {
        displayedOperand = "";
        if (enteringDigits) {
            const i = calculationsListView.model.count - 1;
            if (i >= 0)
                calculationsListView.model.remove(i);
            enteringDigits = false;
        }
    }

    function allClear() {
        display.clear();
        calculationsListView.model.clear();
        enteringDigits = false;
    }

    Item {
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            radius: 8
            color: display.backgroundColor

            ListView {
                id: calculationsListView
                x: 5
                y: 10
                width: parent.width
                height: parent.height - 2 * y
                clip: true
                delegate: Item {
                    height: display.fontSize * 1.1
                    width: calculationsListView.width

                    required property string operator
                    required property string operand

                    Text {
                        x: 6
                        font.pixelSize: display.fontSize
                        color: display.qtGreenColor
                        text: parent.operator
                    }
                    Text {
                        font.pixelSize: display.fontSize
                        anchors.right: parent.right
                        anchors.rightMargin: 16
                        text: parent.operand
                        color: "white"
                    }
                }
                model: ListModel {}
                onHeightChanged: positionViewAtEnd()
            }
        }
    }
}

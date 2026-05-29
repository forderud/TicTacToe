pragma ComponentBehavior: Bound

import QtQuick

Item {
    id: display
    property int fontSize: 22
    readonly property color backgroundColor: "#262626"
    readonly property color qtGreenColor: "#2CDE85"

    function displayText(message) {
        calculationsListView.text = message
    }

    function allClear() {
        calculationsListView.text = ""
    }

    Rectangle {
        anchors.fill: parent
        radius: 8
        color: display.backgroundColor

        Text {
            id: calculationsListView
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: display.fontSize
            color: "white"
        }
    }
}

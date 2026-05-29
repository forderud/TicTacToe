pragma ComponentBehavior: Bound

import QtQuick

Item {
    id: display

    function displayText(message) {
        calculationsListView.text = message
    }

    function allClear() {
        calculationsListView.text = ""
    }

    Rectangle {
        anchors.fill: parent
        radius: 8
        color: "#262626"

        Text {
            id: calculationsListView
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 22
            color: "white"
        }
    }
}

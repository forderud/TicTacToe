pragma ComponentBehavior: Bound

import QtQuick

Rectangle {
    id: display
    radius: 8
    color: "#262626"

    function displayText(message) {
        calculationsListView.text = message
    }

    function allClear() {
        calculationsListView.text = ""
    }

    Text {
        id: calculationsListView
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 60
        color: "white"
    }
}

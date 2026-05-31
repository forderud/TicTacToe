import QtQuick

Text {
    id: display
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    font.pixelSize: 60
    color: "black"

    function displayText(message) {
        display.text = message
    }

    function allClear() {
        display.text = ""
    }
}

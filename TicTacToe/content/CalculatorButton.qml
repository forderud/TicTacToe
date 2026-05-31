import QtQuick
import QtQuick.Controls

RoundButton {
    id: button
    implicitWidth: 0.3 * parent.width
    implicitHeight: 0.3 * parent.height
    radius: buttonRadius

    readonly property int fontSize: 100
    readonly property int buttonRadius: 8

    background: Rectangle {
        radius: button.buttonRadius
        color: "#222222"
        border.color: "#A9A9A9"
    }

    contentItem: Text {
        text: button.text
        font.pixelSize: button.fontSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "#FFFFFF"
        Behavior on color {
            ColorAnimation {
                duration: 120
                easing.type: Easing.OutElastic
            }
        }
    }
}

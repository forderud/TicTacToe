import QtQuick
import QtQuick.Controls

RoundButton {
    id: button
    implicitWidth: 90
    implicitHeight: 90
    radius: buttonRadius

    readonly property int fontSize: 80
    readonly property int buttonRadius: 8
    property color textColor: "#FFFFFF"
    property color accentColor: "#2CDE85"
    readonly property color backgroundColor: "#222222"
    readonly property color borderColor: "#A9A9A9"

    function getBackgroundColor() {
        if (button.pressed)
            return accentColor;
        return backgroundColor;
    }

    function getBorderColor() {
        if (button.pressed || button.hovered)
            return accentColor;
        return borderColor;
    }

    function getTextColor() {
        if (button.pressed)
            return backgroundColor;
        if (button.hovered)
            return accentColor;
        return textColor;
    }

    background: Rectangle {
        radius: button.buttonRadius
        color: button.getBackgroundColor()
        border.color: button.getBorderColor()
    }

    contentItem: Text {
        text: button.text
        font.pixelSize: button.fontSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: button.getTextColor()
        Behavior on color {
            ColorAnimation {
                duration: 120
                easing.type: Easing.OutElastic
            }
        }
    }
}

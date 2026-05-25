import QtQuick
import QtQuick.Controls

RoundButton {
    id: button
    implicitWidth: 48
    implicitHeight: 38
    radius: buttonRadius
    icon.source: getIcon()
    icon.width: 38
    icon.height: 38
    icon.color: getIconColor()
    // The text is never drawn.
    text: ""

    readonly property color backgroundColor: "#222222"
    readonly property color borderColor: "#A9A9A9"
    readonly property color backspaceRedColor: "#DE2C2C"
    readonly property int buttonRadius: 8

    function getBackgroundColor() {
        if (button.pressed)
            return backspaceRedColor;
        return backgroundColor;
    }

    function getBorderColor() {
        if (button.pressed || button.hovered)
            return backspaceRedColor;
        return borderColor;
    }

    function getIconColor() {
        if (button.pressed)
            return backgroundColor;
        return backspaceRedColor;
    }

    function getIcon() {
        if (button.pressed)
            return "images/x.svg";
        return "images/duck.svg";
    }

    background: Rectangle {
        radius: button.buttonRadius
        color: button.getBackgroundColor()
        border.color: button.getBorderColor()
    }
}

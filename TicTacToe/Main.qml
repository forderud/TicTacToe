import QtQuick
import QtQuick.Layouts


Window {
    visible: true
    width: 320
    height: 480
    color: "#DDDDDD"

    ColumnLayout {
        id: root
        anchors.fill: parent

        anchors.topMargin: parent.SafeArea.margins.top
        anchors.leftMargin: parent.SafeArea.margins.left
        anchors.rightMargin: parent.SafeArea.margins.right
        anchors.bottomMargin: parent.SafeArea.margins.bottom

        readonly property int margin: 18

        ApplicationState {
            id: appState
            display: calcDisplay
        }

        Display {
            id: calcDisplay

            Layout.preferredHeight: 0.3 * parent.height
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: root.margin
        }

        NumberPad {
            id: numberPad

            Layout.preferredHeight: 0.7 * parent.height
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: root.margin

            applicationState: appState
        }
    }
}

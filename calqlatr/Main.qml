import QtQuick
import QtQuick.Layouts


Window {
    visible: true
    width: 320
    height: 480
    minimumWidth: Math.max(numberPad.portraitModeWidth, calcDisplay.minWidth) + root.margin * 2
    minimumHeight: calcDisplay.minHeight + numberPad.height + root.margin * 3
    color: root.backgroundColor

    Item {
        id: root
        anchors.fill: parent

        anchors.topMargin: parent.SafeArea.margins.top
        anchors.leftMargin: parent.SafeArea.margins.left
        anchors.rightMargin: parent.SafeArea.margins.right
        anchors.bottomMargin: parent.SafeArea.margins.bottom

        readonly property int margin: 18
        readonly property color backgroundColor: "#DDDDDD"

        ApplicationState {
            id: appState
            display: calcDisplay
        }

        Display {
            id: calcDisplay
            readonly property int minWidth: 210
            readonly property int minHeight: 60

            Layout.minimumWidth: minWidth
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: root.margin

            // remove the margin on the side that the numberPad is on, to prevent a double margin
            Layout.bottomMargin: 0
            Layout.rightMargin: root.margin
        }

        NumberPad {
            id: numberPad
            Layout.margins: root.margin

            applicationState: appState
        }

        // define the responsive layouts
        ColumnLayout {
            id: portraitMode
            anchors.fill: parent

            LayoutItemProxy {
                target: calcDisplay
                Layout.minimumHeight: calcDisplay.minHeight
            }
            LayoutItemProxy {
                target: numberPad
                Layout.alignment: Qt.AlignHCenter
            }
        }
    }
}

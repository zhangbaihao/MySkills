import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600

    // Add custom buttons and dragging functionality
    Row {
        id: customButtons
        anchors.top: parent.top
        spacing: 10

        Button {
            text: "Custom Button 1"
            anchors.topMargin: 10
            onClicked: mainWindow.drag.target = null
        }

        Button {
            text: "Custom Button 2"
            anchors.topMargin: 10
            onClicked: mainWindow.drag.target = null
        }
    }

    // Main window content
    Rectangle {
        width: parent.width
        height: parent.height - customButtons.height
        anchors.top: customButtons.bottom
        color: "white"
    }
}
import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtGraphicalEffects 1.0

import "./ContentView"
import "./TopPanel"

Window {
    id: mainWindow
    visibility: "Windowed"
    width: 1024
    height: 680
    title: qsTr("Quwi Test")
    color: "white"

    minimumWidth: 600
    minimumHeight: 250

    function updateWarningText(warning) {
        waringView.text = warning;
    }

    Column {
        anchors.topMargin: parent.topMargin
        anchors.verticalCenter: parent.verticalCenter
        spacing: 0

        TopPanel {
            id: topPanel
            width: mainWindow.width
            height: 70
            visible: true
            projectsButtonState: "Pressed"

            onProjectsClicked: {
                contentView.showProjectsView(true);
            }

            onLogoutClicked: {
                contentView.showLoginView(true);
                topPanel.showTopMenu(false);
            }
        }

        ContentView {
            id: contentView
            objectName:"contentView"
            height: mainWindow.height - topPanel.height - 20
            width: mainWindow.width

            onLogedIn: {
                topPanel.showTopMenu(true);
                topPanel.projectsButtonState = "Pressed"
            }

            onEditProject: {
                topPanel.projectsButtonState = "Normal"
            }
        }

        Text {
            id: waringView
            objectName: "warningView"
            color: "red"

            width: mainWindow.width
            height: 20
        }
    }
}

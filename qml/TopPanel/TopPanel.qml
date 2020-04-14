import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0

Rectangle {
    id: topPanel
    property alias projectsButtonState: projectsButton.state
    property alias logoutButtonState: logoutButton.state

    function showTopMenu(show) {
        if (show) {
            topMenu.visible = true;
            topMenu.x = appIcon.x + appIcon.width;
        } else {
            topMenu.visible = false;
            topMenu.x = topPanel.width;
        }
    }

    signal projectsClicked()
    signal logoutClicked();

    Image {
        id: appIcon
        x: 10
        y: 15
        width: 40
        height: 40
        visible: true;
        sourceSize.width: 40
        sourceSize.height: 40
        source: "qrc:/resources/quwi-logo.png"
    }

    Rectangle {
        id: topMenu
        x: topPanel.width
        y: 0
        width: topPanel.width - appIcon.width
        height: topPanel.height
        visible: false;
//        gradient: Gradient {
//            GradientStop { position: 0.0; color: "lightgray" }
//            GradientStop { position: 1.0; color: "white" }
//        }

        Behavior on x {
            NumberAnimation {
                //This specifies how long the animation takes
                duration: 600
                //This selects an easing curve to interpolate with, the default is Easing.Linear
                easing.type: Easing.OutBounce
            }
        }

        RowLayout {
            anchors.fill: topMenu
            anchors.margins: 0
            spacing: 0

            MenuButton {
                id: projectsButton
                buttonText: qsTr("Projects")
                state: "Pressed"
                imageNormal: ""
                imageHover: ""
                imagePressed: ""
                fontColor: Qt.rgba(0, 0, 0, 1);
                fontColorPressed: "gray"
                fontColorHover: Qt.rgba(0.1, 0.1, 0.1, 0.7);


                onClicked: {
                    topPanel.projectsClicked()
                }
            }

            MenuButton {
                id: logoutButton
                buttonText: qsTr("Logout")
                imageNormal: ""
                imageHover: ""
                imagePressed: ""
                fontColor: Qt.rgba(0, 0, 0, 1);
                fontColorPressed: "gray"
                fontColorHover: Qt.rgba(0.1, 0.1, 0.1, 0.7);

                onClicked: {
                    topPanel.logoutClicked()
                    logoutButton.state = "Normal"
                }
            }

            Item {
                // spacer item
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}



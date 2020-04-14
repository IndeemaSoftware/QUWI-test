import QtQuick 2.0
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4

import "../../TopPanel"

Rectangle {
    id: loginView
    objectName: "loginView"

    property string message: "You are using wrong credentials."

    color: Qt.rgba(0.925, 0.945, 0.976, 1)

    function showWrongCredentials(message){
        loginView.message = message
        warningView.visible = true;
    }

    function hideWrongCredentials(){
        warningView.visible = false;
    }

    signal logedIn();
    signal logedOut();
    signal loginPressed(string login, string password);

    DropShadow {
        anchors.fill: centralView
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8.0
        samples: 17
        color: "#80000000"
        source: centralView
    }

    Rectangle {
        id: centralView
        anchors.horizontalCenter: loginView.horizontalCenter
        anchors.verticalCenter: loginView.verticalCenter
        width: 500;
        height: 300
        color: Qt.rgba(0.9, 0.9, 0.9, 1)

        Rectangle {
            id: borderView
            y: 30
            width: 365
            height: 200
            color: Qt.rgba(0.9, 0.9, 0.9, 1)
            anchors.horizontalCenter: centralView.horizontalCenter
            anchors.verticalCenter: centralView.verticalCenter

            ColumnLayout {
                id: layout
                anchors.fill: borderView
                spacing: 20

                Text {
                    anchors.horizontalCenter: layout.horizontalLeft
                    text: "LOGIN"
                    color: "black"
                    font.weight: Font.DemiBold
                    font.pointSize: 14
                }

                LoginTextArea {
                    id: loginTextArea
                    width: 365
                    height: 40
                    placeholderText: qsTr("Email")

                    text:"volodymyr.shevchyk@indeema.com"

                    onTabPressed: {
                        passwordTextArea.inputFocus = true;
                    }
                }

                LoginTextArea {
                    id: passwordTextArea
                    width: 365
                    height: 40

                    text: "qwerty123"
                    echoMode: TextInput.Password
                    placeholderText: qsTr("Password")
                    onTabPressed: {
                        loginButtonImage.focus = true;
                    }
                }

                MenuButton {
                    id: loginButtonImage
                    width: 120
                    height: 35
                    buttonText: "LOGIN"
                    anchors.horizontalCenter: layout.horizontalLeft
                    color: Qt.rgba(0.18, 0.285, 0.417, 1)
                    hoverColor: Qt.rgba(0.18, 0.285, 0.417, 0.5)
                    pressColor: Qt.rgba(0.28, 0.385, 0.517, 1)

                    fontSize: 12
                    fontColor: "white";
                    fontColorPressed: "white"
                    fontColorHover: Qt.rgba(1, 1, 1, 0.7);

                    onClicked: {
                        var login = true;

                        hideWrongCredentials();

                        if (loginTextArea.text === "") {
                            loginTextArea.state = "Warning"
                            login = false;
                        }

                        if (passwordTextArea.text === "") {
                            passwordTextArea.state = "Warning"
                            login = false;
                        }

                        if (login)
                        {
                            loginPressed(loginTextArea.text, passwordTextArea.text);                         }
                        }

                    onReleased: {
                        loginButtonImage.state = 'Normal'
                    }
                }

                Rectangle {
                    id: warningView
                    width: 400
                    Layout.fillHeight: true
                    visible: false

                    Image {
                        id: icon
                        source: "qrc:/resources/login/warning_icon.png"
                    }

                    Text {
                        x: icon.width
                        color: "red"
                        text: loginView.message
                    }
                }

                Item {
                    id: spacer
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }
}

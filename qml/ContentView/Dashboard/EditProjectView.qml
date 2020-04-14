import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.14
import QtQuick.Controls 2.14

import "../../TopPanel"
import "../Login"

Rectangle {
    id: editProjectView
    objectName: "editProjectView"
    width: 550
    height: 300
    radius: 5
    border.color: "gray"
    border.width: 1

    property string imageUrl: "https://api.quwi.com/files/projects/730-thumb.png"
    property string projectName: "Test"
    property bool   isActive: true
    property int spacing: 30
    property string ava:  "https://api.quwi.com/files/projects/730-thumb.png"
    property string message: ""

    signal updateProject

    onVisibleChanged: {
        editProjectView.message = ""
    }

    Rectangle {
        id: test
        anchors.fill: parent
        color: "white"
        radius: 5
    }

    DropShadow {
        anchors.fill: test
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8.0
        samples: 17
        color: "#80000000"
        source: test
    }

    RowLayout {
        id: layout
        y: 20
        x: 20
        anchors.fill: projectModel
        spacing: 5

        Rectangle {
            id:data
            x: 0
            y: 0
            width: 420

            ColumnLayout {
                x: 0
                y: 0
                spacing: 15
                anchors.fill: data

                Rectangle {
                    id: first
                    width: parent.width
                    height: 100
                    color:"green"

                    RowLayout {
                        anchors.fill: first

                        Rectangle {
                            width: 420
                            height: 170
                            ColumnLayout {

                                Rectangle {
                                    width: parent.width
                                    height: 70
                                    RowLayout {
                                        spacing: editProjectView.spacing
                                        Text{
                                            text:"Active"
                                        }

                                        Switch {
                                            width: 50
                                            height: 20
                                            checked: editProjectView.isActive
                                        }
                                    }
                                }
                                Rectangle {
                                    width: parent.width
                                    height: 100

                                    RowLayout {
                                        spacing: 10

                                        Text {
                                            text:"Name"
                                        }

                                        LoginTextArea {
                                            id: projectName
                                            width:250
                                            height:40
                                            placeholderText: qsTr("Project name")
                                            text: editProjectView.projectName

                                            onTextChanged: {
                                                editProjectView.projectName = text;
                                            }
                                        }

                                        MenuButton {
                                            id: updateProjectNameButton
                                            width: 50
                                            height: 40
                                            buttonText: "OK"

                                            onClicked: {
                                                updateProjectNameButton.state = "Normal"
                                                editProjectView.updateProject()
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Image {
                            id: projectImage
                            y: 0
                            width: 80
                            height: 80
                            sourceSize.width: 80
                            sourceSize.height: 80
                            source: editProjectView.imageUrl
                            fillMode: Image.PreserveAspectCrop
                            layer.enabled: true
                            layer.effect: OpacityMask {
                                maskSource: Item {
                                    width: projectImage.width
                                    height: projectImage.height
                                    Rectangle {
                                        anchors.centerIn: parent
                                        width: projectImage.adapt ? projectImage.width : Math.min(projectImage.width, projectImage.height)
                                        height: projectImage.adapt ? projectImage.height : width
                                        radius: Math.min(width, height)
                                    }
                                }
                            }
                        }
                    }

                }
                Rectangle {
                    y:50
                    width: parent.width
                    height: 50

                    RowLayout {
                        spacing: editProjectView.spacing
                        anchors.fill: first
                        Text {
                            height: parent.height
                            text:"Users"
                            verticalAlignment: parent.verticalCenter
                        }

                        RowLayout {
                            spacing: editProjectView.spacing
                            anchors.fill: first

                            Repeater {
                                model: 3

                              Rectangle {
                                    width: 100
                                    height: 50
                                    color: "transparent"
                                    RowLayout {
                                        spacing: 3
                                        anchors.fill: first

                                        CheckBox {
                                            width: 10
                                            height: 10
                                        }

                                        UserView {
                                            ava: editProjectView.ava
                                            width: 25
                                            height: 25
                                            userName: "Vova S"
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: 50

                    RowLayout {
                        spacing: 3
                        anchors.fill: first

                        Switch {
                            width: 50
                            height: 20
                            checked: editProjectView.isActive
                        }

                        Text {
                            text: "Add me as watcher to tickets created by others"
                        }
                    }
                }

                Text {
                    id: message
                    text: editProjectView.message
                    color: "green"
                }
            }
        }
    }
}

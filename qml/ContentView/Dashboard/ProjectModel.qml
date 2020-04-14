import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.14

Rectangle {
    id: projectModel
    objectName: "projectModel"
    radius: 5
    border.color: "gray"
    border.width: 1
    color: "white"

    implicitWidth: 550
    implicitHeight: 100

    signal pressed

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
        anchors.fill: projectModel
        spacing: 5

        Rectangle {
            id: space1
            color: "transparent"
            width: 20
        }

        Image {
            id: projectImage
            width: 40
            height: 40
            sourceSize.width: 40
            sourceSize.height: 40
            source: logo_url
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

        Rectangle {
            width: 50
            height: 20
            color: "transparent"
            Text {
                text: name
                horizontalAlignment:parent.horizontalLeft
            }
        }

        Rectangle {
            id: space2
            color: "transparent"
            width: 40
        }

        Rectangle {
            id: status
            width: 100
            height: 75
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 5

                Rectangle {
                    height: 8
                    color: "transparent"
                }

                Text {
                    color: Qt.rgba(0.007, 0.46, 0.101, 1)
                    text: is_active? "Active" : "Inactive"
                }
                Text {
                    text: "No Workers"
                }
            }
        }

        RowLayout {
            id: timeReport
            width: 150
            height: 75
            spacing: 15

            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 5

                Rectangle {
                    height: 3
                    color: "transparent"
                }
                Text {
                    text: "time this week"
                }
                Text {
                    text: "this month"
                }
                Text {
                    text: "total"
                }
            }
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 5

                Rectangle {
                    height: 3
                    color: "transparent"
                }
                Text {
                    text: "00:00:00"
                }
                Text {
                    text: "00:00:00"
                }
                Text {
                    text: "00:00:00"
                }
            }
        }
    }

    Rectangle {
        x: 0
        y: 0
        visible: !is_active
        width: projectModel.width
        height: projectModel.height
        radius: 5
        color: Qt.rgba(0.2, 0.2, 0.2, 0.5)
    }

    MouseArea {
        propagateComposedEvents: true
        hoverEnabled: true
        anchors.fill: projectModel

        onEntered: {
        }

        onExited: {
        }

        onPressed: {
        }

        onReleased: {
            projectModel.pressed();
        }
    }
}

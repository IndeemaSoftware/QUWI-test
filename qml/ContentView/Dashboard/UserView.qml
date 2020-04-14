import QtQuick 2.0
import QtGraphicalEffects 1.14
import QtQuick.Layouts 1.0

Rectangle {
    id: userView
    objectName: "userView"
    color: "transparent"

    property string ava:""
    property int status: 1
    property string userName:""

    RowLayout {
        spacing: 3
        anchors.fill: parent

        Image {
            id: userAva
            y: 0
            width: userView.width
            height: userView.height
            sourceSize.width: userView.width
            sourceSize.height: userView.height
            source: userView.ava
            fillMode: Image.PreserveAspectCrop
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: userAva.width
                    height: userAva.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: userAva.adapt ? userAva.width : Math.min(userAva.width, userAva.height)
                        height: userAva.adapt ? userAva.height : width
                        radius: Math.min(width, height)
                    }
                }
            }
        }

        Text {
            text: userView.userName
        }
    }
}

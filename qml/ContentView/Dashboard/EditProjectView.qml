import QtQuick 2.0
import QtGraphicalEffects 1.14

Rectangle {
    id: editProjectView
    objectName: "editProjectView"
    width: 550
    height: 400
    radius: 5
    border.color: "gray"
    border.width: 1

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

}

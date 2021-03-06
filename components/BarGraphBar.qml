/***************************************************************************
 * Whatsoever ye do in word or deed, do all in the name of the             *
 * Lord Jesus, giving thanks to God and the Father by him.                 *
 * - Colossians 3:17                                                       *
 *                                                                         *
 * Ubuntu UI Extras - A collection of QML widgets not available            *
 *                    in the default Ubuntu UI Toolkit                     *
 * Copyright (C) 2013 Michael Spencer <sonrisesoftware@gmail.com>          *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 2 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.    *
 ***************************************************************************/
import QtQuick 2.0
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0

Item {
    id: root

    property var graph
    property var values: []
    property string label

    anchors {
        bottom: parent.bottom
        bottomMargin: 1
    }

    Item {
        width: labelItem.height
        height: labelItem.width
        anchors.top: parent.bottom
        anchors.topMargin: units.gu(1.5)
        anchors.horizontalCenter: parent.horizontalCenter
        Label {
            id: labelItem
            rotation: -90
            text: label
            anchors.centerIn: parent
        }
    }

    Column {
        id: column
        anchors.bottom: parent.bottom
        width: parent.width

        Repeater {
            id: repeater
            model: values

            delegate: Rectangle {
                property int reversedIndex: repeater.count - index - 1
                width: root.width
                height: values[reversedIndex] * (graph.scale)
                color: graph.colors[reversedIndex]
            }
        }
    }
}

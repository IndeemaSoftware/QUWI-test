import QtQuick 2.12
import Qt.labs.qmlmodels 1.0

TableView {
    id: projectsView
    objectName: "projectsView"
    anchors.fill: parent
    columnSpacing: 1
    topMargin: 20
    leftMargin: projectsView.width/2 -275
    rowSpacing: 10
    clip: true
    contentWidth: 550

    property alias data: projectList

    property int index: -1

    signal projectPressed

    signal updateProjectName(int id, string newName)
    signal updateMessage(string msg)

    ListModel { id: projectList }

    function clearProjectsList() {
        projectList.clear();
    }

    function updateProjectMessage(msg) {
        projectsView.updateMessage(msg)
    }

    function updateName(name) {
        console.log("Update project name");
        console.log(index);
        console.log(name);
        projectsView.updateProjectName(index, name);
    }

    function updateProjectList(name, logo, is_active) {
        var obj = {"name":name, "logo_url": logo, "is_active": is_active}
        projectList.append(obj)
    }

    model: projectList

    delegate: ProjectModel {
        id:cell

        onPressed: {
            projectsView.index = index
            projectsView.projectPressed()
        }
    }
}

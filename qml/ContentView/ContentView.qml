import QtQuick 2.0

import "./Dashboard"
import "./Login"

Rectangle {
    id: contentPanel

    signal logedIn
    signal logedOut
    signal editProject

    function showProjectsView(show) {
        projectsView.visible = show;
        editProjectView.visible = !show;
        loginView.visible = !show;
    }

    function showEditProjectView(show) {
        editProjectView.visible = show;
        projectsView.visible = !show;
        loginView.visible = !show;
        editProject();
    }

    function showLoginView(show) {
        loginView.visible = show;
        editProjectView.visible = !show;
        projectsView.visible = !show;
    }

    LoginView {
        id: loginView
        anchors.fill: contentPanel
        visible: true

        onLogedIn: {
            loginView.visible = false;
            projectsView.visible = true;

            contentPanel.logedIn();
        }

        onLogedOut: {
            loginView.visible = true;
            projectsView.visible = false;

            contentPanel.logedOut();
        }
    }

    ProjectsView {
        id: projectsView
        visible: false

        onProjectPressed: {
            console.log("We are here");
            showEditProjectView(true);
        }
    }

    EditProjectView {
        id: editProjectView
        visible: false
    }

    Rectangle {
        id: shadow1
        width: mainWindow.width
        height: 5
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(0.5, 0.5, 0.5, 0.5); }
            GradientStop { position: 1.0; color: Qt.rgba(1, 1, 1, 0.0); }
        }
    }
}

#include "maincontroller.h"
#include "QuwiAPI/quwiapi.h"
#include "quwidatamodel.h"
#include "quwiprojectmodel.h"

#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMovie>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QSignalMapper>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QMetaObject>
#include <QQmlContext>

MainController::MainController(QObject *parent) : QObject(parent)
{
    QString lBasicURL = "https://api.quwi.com";
    //initializing apiclass
    mAPI = new QuwiAPI(lBasicURL);
    mAPI->setAPIVersion("v2");

    connect(mAPI, SIGNAL(loginSucced()), this, SLOT(loginSucced()));
    connect(mAPI, SIGNAL(loginFailed(QString)), this, SLOT(loginFailed(QString)));
    connect(mAPI, SIGNAL(logoutSucced()), this, SLOT(logoutSucced()));

    connect(mAPI, SIGNAL(projectsRecived(QList<QuwiProject>*)), this, SLOT(projectsReceived(QList<QuwiProject>*)));

    connect(mAPI, SIGNAL(error(QString)), this, SLOT(apiCallError(QString)));
}

void MainController::setEngine(QQmlApplicationEngine *engine)
{
    mEngine = engine;
    QObject *lRoot = mEngine->rootObjects()[0];
    mLoginView = lRoot->findChild<QQuickItem *>("loginView");
    mProjectsView = lRoot->findChild<QQuickItem *>("projectsView");
    connect(mLoginView, SIGNAL(loginPressed(QString, QString)), this, SLOT(login(QString, QString)));
}

void MainController::getProjects()
{
    mAPI->getProjects();
}

void MainController::cleanWarningMessage()
{
}

void MainController::login(QString email, QString pass)
{
    mAPI->login(email, pass);
}

void MainController::loginSucced()
{
    QMetaObject::invokeMethod(mLoginView,
                              "logedIn",
                              Qt::DirectConnection);
    getProjects();
}

void MainController::loginFailed(QString message)
{
    logoutSucced();

    QMetaObject::invokeMethod(mLoginView,
                              "showWrongCredentials",
                              Qt::DirectConnection,
                              Q_ARG(QVariant, QVariant::fromValue(message)));
}

void MainController::logout()
{
    mAPI->logout();
}

void MainController::logoutSucced()
{
}

void MainController::projectsReceived(QList<QuwiProject> *projectsList)
{
    mProjectList = projectsList;

    QMetaObject::invokeMethod(mProjectsView,
                             "clearProjectsList",
                             Qt::DirectConnection);


    QList<QObject*> dataList;
    foreach (const QuwiProject &project, *mProjectList) {
        QMetaObject::invokeMethod(mProjectsView,
                                 "updateProjectList",
                                 Qt::DirectConnection,
                                 Q_ARG(QVariant, QVariant::fromValue(project.name())),
                                 Q_ARG(QVariant, QVariant::fromValue(project.logoUrl().toString())),
                                 Q_ARG(QVariant, QVariant::fromValue(project.isActive())));
    }
}

void MainController::updateProjectName(int id)
{
    if (mProjectList != nullptr) {
        QModelIndex index = mModel->index(id, 1, QModelIndex());
        QuwiProject lProject = mProjectList->at(id);
        lProject.setName(mModel->data(index).toString());
        mProjectList->replace(id, lProject);

        mAPI->updateProject(lProject);
    }
}

void MainController::apiCallError(QString msg)
{
    logout();
}

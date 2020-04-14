#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QMainWindow>
#include <QList>

#include "QuwiAPI/quwiproject.h"

class QuwiAPI;
class QStandardItemModel;
class QSignalMapper;
class QQmlApplicationEngine;
class QQuickItem;

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);

    void setEngine(QQmlApplicationEngine *engine);

    void getProjects();

private slots:
    void cleanWarningMessage();

    void login(QString, QString);
    void loginSucced();
    void loginFailed(QString);
    void logout();
    void logoutSucced();

    void projectsReceived(QList<QuwiProject>*);
    void updateProjectName(int id);

    void apiCallError(QString);

signals:
    void updateProject(int);
private:
    QQmlApplicationEngine *mEngine;
    QQuickItem *mLoginView;
    QQuickItem *mProjectsView;

    QuwiAPI *mAPI;
    QList<QuwiProject> *mProjectList;
    QStandardItemModel *mModel;
    QSignalMapper *mSignalMapper; //is used to set id for each button in table
};

#endif // MAINCONTROLLER_H

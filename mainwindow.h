#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QuwiAPI/quwiproject.h"

#include <QMainWindow>
#include <QList>

class QuwiAPI;
class QMovie;
class QStandardItemModel;
class QSignalMapper;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getProjects();
    void initTabelModel(int);

private slots:
    void cleanWarningMessage();
    void frameChanged();
    void stopFrames();

    void login();
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
    Ui::MainWindow *ui;
    QuwiAPI *mAPI;
    QMovie *mLoading;
    QList<QuwiProject> *mProjectList;
    QStandardItemModel *mModel;
    QSignalMapper *mSignalMapper; //is used to set id for each button in table
};
#endif // MAINWINDOW_H

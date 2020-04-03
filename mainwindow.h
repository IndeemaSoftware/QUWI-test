#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QuwiAPI;
class QMovie;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void cleanWarningMessage();
    void login();
    void loginSucced();
    void loginFailed(QString);
    void logout();
    void logoutSucced();

    void frameChanged();
    void stopFrames();

private:
    Ui::MainWindow *ui;
    QuwiAPI *mAPI;
    QMovie *mLoading;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QuwiAPI/quwiapi.h"

#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMovie>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mProjectList{nullptr},
      mModel{nullptr}
{
    ui->setupUi(this);
    ui->logoutButton->setVisible(false);
    ui->tableView->setDisabled(true);
    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->lineEmail->setValidator(new QRegularExpressionValidator(rx, this));

    mSignalMapper = new QSignalMapper(this);
    connect(mSignalMapper, SIGNAL(mapped(int)), this, SIGNAL(updateProject(int)));

    mLoading = new QMovie(ui->loginButton);
    mLoading->setFileName(":/assets/assets/CWjOv.gif");
    connect(mLoading, SIGNAL(frameChanged(int )), this, SLOT(frameChanged()));
    if (mLoading->loopCount() != -1) {
        connect(mLoading, SIGNAL(finished()), mLoading, SLOT(start()));
    }
    initTabelModel(0);

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(ui->lineEmail, SIGNAL(textChanged(const QString)), this, SLOT(cleanWarningMessage()));
    connect(ui->linePassword, SIGNAL(textChanged(const QString)), this, SLOT(cleanWarningMessage()));

    connect(this, SIGNAL(updateProject(int)), this, SLOT(updateProjectName(int)));

    QString lBasicURL = "https://api.quwi.com";
    //initializing apiclass
    mAPI = new QuwiAPI(lBasicURL);
    mAPI->setAPIVersion("v2");

    connect(mAPI, SIGNAL(loginSucced()), this, SLOT(loginSucced()));
    connect(mAPI, SIGNAL(loginFailed(QString)), this, SLOT(loginFailed(QString)));
    connect(mAPI, SIGNAL(logoutSucced()), this, SLOT(logoutSucced()));

    connect(mAPI, SIGNAL(projectsRecived(QList<QuwiProject>*)), this, SLOT(projectsReceived(QList<QuwiProject>*)));
}

MainWindow::~MainWindow()
{
    delete mModel;
    if (mProjectList != nullptr) {
        delete mProjectList;
    }
    delete mAPI;
    delete ui;
}

void MainWindow::getProjects()
{
    mAPI->getProjects();
}

void MainWindow::initTabelModel(int rows)
{
    if (mModel != nullptr) {
        delete mModel;
    }

    mModel = new QStandardItemModel(rows, 3);
    QStandardItem *it = new QStandardItem(QObject::tr("ID"));
    mModel->setHorizontalHeaderItem(0,it);
    QStandardItem *it1 = new QStandardItem(QObject::tr("Name"));
    mModel->setHorizontalHeaderItem(1,it1);
    QStandardItem *it3 = new QStandardItem(QObject::tr(""));
    mModel->setHorizontalHeaderItem(2,it3);

    ui->tableView->setModel(mModel);
    ui->tableView->show();
}

void MainWindow::cleanWarningMessage()
{
    ui->labelWarning->setText("");

    //and nowlet's validate if in email field we are entering email
    if(!ui->lineEmail->hasAcceptableInput())
        ui->lineEmail->setStyleSheet("QLineEdit { color: red;}");
    else
        ui->lineEmail->setStyleSheet("QLineEdit { color: black;}");
}

void MainWindow::login()
{
    if (ui->lineEmail->text().isEmpty()
            || ui->linePassword->text().isEmpty()) {
        ui->labelWarning->setText("Fields can not be empty");
    } else if(!ui->lineEmail->hasAcceptableInput()) {
        ui->labelWarning->setText("Invalid email entered");
    } else {
        mLoading->start();
        mAPI->login(ui->lineEmail->text(), ui->linePassword->text());
    }
}

void MainWindow::loginSucced()
{
    stopFrames();
    ui->lineEmail->setEnabled(false);
    ui->linePassword->setEnabled(false);
    ui->loginButton->setVisible(false);
    ui->logoutButton->setVisible(true);
    ui->tableView->setDisabled(false);

    getProjects();
}

void MainWindow::loginFailed(QString message)
{
    stopFrames();
    ui->labelWarning->setText(message);
    logoutSucced();
}

void MainWindow::logout()
{
    mAPI->logout();
}

void MainWindow::logoutSucced()
{
    ui->lineEmail->setEnabled(true);
    ui->linePassword->setEnabled(true);
    ui->loginButton->setVisible(true);
    ui->logoutButton->setVisible(false);
    ui->tableView->setDisabled(true);
}

void MainWindow::projectsReceived(QList<QuwiProject> *projectsList)
{
    mProjectList = projectsList;

    initTabelModel(projectsList->size());

    int raw = 0;
    foreach (QuwiProject project, *projectsList) {
        QModelIndex index = mModel->index(raw, 0, QModelIndex());

        qDebug() << project.id();
        mModel->setData(index, project.id());

        index = mModel->index(raw, 1, QModelIndex());
        mModel->setData(index, project.name());

        index = mModel->index(raw, 2, QModelIndex());

        QPushButton *lButton = new QPushButton("Update");
        connect(lButton, SIGNAL(clicked()), mSignalMapper, SLOT(map()));
        mSignalMapper->setMapping(lButton, raw);
        ui->tableView->setIndexWidget(index, lButton);

        raw++;
    }
}

void MainWindow::updateProjectName(int id)
{
    if (mProjectList != nullptr) {
        QModelIndex index = mModel->index(id, 1, QModelIndex());
        QuwiProject lProject = mProjectList->at(id);
        lProject.setName(mModel->data(index).toString());
        mProjectList->replace(id, lProject);

        mAPI->updateProject(lProject);
    }
}

void MainWindow::frameChanged()
{
    ui->loginButton->setIcon(QIcon(mLoading->currentPixmap()));
}

void MainWindow::stopFrames()
{
    mLoading->stop();
    ui->loginButton->setIcon(QIcon());
}

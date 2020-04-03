#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quwiapi.h"

#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->logoutButton->setVisible(false);
    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->lineEmail->setValidator(new QRegularExpressionValidator(rx, this));

    mLoading = new QMovie(ui->loginButton);
    mLoading->setFileName(":/assets/assets/CWjOv.gif");
    connect(mLoading, SIGNAL(frameChanged(int )), this, SLOT(frameChanged()));
    if (mLoading->loopCount() != -1) {
        connect(mLoading, SIGNAL(finished()), mLoading, SLOT(start()));
    }

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(ui->lineEmail, SIGNAL(textChanged(const QString)), this, SLOT(cleanWarningMessage()));
    connect(ui->linePassword, SIGNAL(textChanged(const QString)), this, SLOT(cleanWarningMessage()));

    QString lBasicURL = "https://api.quwi.com";
    //initializing apiclass
    mAPI = new QuwiAPI(lBasicURL);
    mAPI->setAPIVersion("v2");

    connect(mAPI, SIGNAL(loginSucced()), this, SLOT(loginSucced()));
    connect(mAPI, SIGNAL(loginFailed(QString)), this, SLOT(loginFailed(QString)));
    connect(mAPI, SIGNAL(logoutSucced()), this, SLOT(logoutSucced()));
}

MainWindow::~MainWindow()
{
    delete mAPI;
    delete ui;
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
}

void MainWindow::frameChanged()
{
    qDebug() << "New frame";
    ui->loginButton->setIcon(QIcon(mLoading->currentPixmap()));
}

void MainWindow::stopFrames()
{
    mLoading->stop();
    ui->loginButton->setIcon(QIcon());
}

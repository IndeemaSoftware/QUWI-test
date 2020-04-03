#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quwiapi.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));

    QString lBasicURL = "https://api.quwi.com";
    //initializing apiclass
    mAPI = new QuwiAPI(lBasicURL);
    mAPI->setAPIVersion("v2");
}

MainWindow::~MainWindow()
{
    delete mAPI;
    delete ui;
}

void MainWindow::login()
{
    qDebug() << "Login pressed";
    mAPI->login("volodymyr.shevchyk@indeema.com", "qwerty123");
}


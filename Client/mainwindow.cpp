#include "mainwindow.h"
#include "config.h"
#include <QPushButton>
#include "ui_mainwindow.h"
#include "user.h"
#include <QHostAddress>
#include <QTcpServer>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

extern User user;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_NAME);
    setWindowIcon(QIcon(ICON_PATH));
    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->startButton, &QPushButton::clicked, this, [=, this](){
        loginDialog = new LoginDialog();
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::connectServer);
        loginDialog->exec();
    });
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(user.tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::connectServer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectServer()
{
    QByteArray array = user.tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    user.socketID = json["socketID"].toInt();
}


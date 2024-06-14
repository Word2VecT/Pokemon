#include "logindialog.h"
#include "ui_logindialog.h"
#include "config.h"
#include "user.h"
#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QPixmap>

extern User user;

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->PasswordLine->setEchoMode(QLineEdit::Password);
    setWindowFlags(Qt::FramelessWindowHint);

    QPixmap pixmap(DIAG_PATH);
    resize(pixmap.size());
    setMask(pixmap.mask());

    connect(ui->backButton, &QPushButton::clicked, this, [=, this](){
        this->hide();
    });
    connect(ui->LoginButton, &QPushButton::clicked, this, &LoginDialog::login);
    connect(ui->RegistButton, &QPushButton::clicked, this, &LoginDialog::regist);
    connect(user.tcpSocket, &QTcpSocket::readyRead, this, &LoginDialog::connectServer);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::connectServer()
{
    QByteArray array = user.tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();

    qDebug() << "LoginDialog 收到服务器" << json << Qt::endl;

    if (json["socketID"].toInt() != user.socketID) {
        return;
    }
    int type = json["type"].toInt();
    switch (type) {
    case LOGIN_SUCCEED:
        user.name = json["username"].toString();
        user.id = json["userID"].toInt();
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &LoginDialog::connectServer);
        this->close();
        home = new Home;
        home->show();
        break;
    case LOGIN_FAILED:
        user.showMsgBox("错误", "密码错误，请重新输入");
        break;
    case REGIST_SUCCEED:
        user.showMsgBox("成功", "注册成功");
        break;
    case REGIST_FAILED:
        user.showMsgBox("错误", "该用户名已存在");
        break;
    default:
        break;
    }
}

void LoginDialog::login()
{
    QString name = ui->UsernameLine->text().toUtf8().data();
    QString password = ui->PasswordLine->text();

    if (name == "") {
        user.showMsgBox("错误", "用户名不能为空");
        return;
    }
    if (password == "") {
        user.showMsgBox("错误", "密码不能为空");
        return;
    }

    QJsonObject json = {
        {"type", LOGIN},
        {"socketID", user.socketID},
        {"username", name},
        {"password", password}
    };
    user.tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    qDebug() << "Client 发送" << json << Qt::endl;
}

void LoginDialog::regist()
{
    QString name = ui->UsernameLine->text().toUtf8().data();
    QString password = ui->PasswordLine->text();

    if (name == "") {
        user.showMsgBox("错误", "用户名不能为空");
        return;
    }
    if (password == "") {
        user.showMsgBox("错误", "密码不能为空");
        return;
    }

    QJsonObject json = {
        {"type", REGIST},
        {"socketID", user.socketID},
        {"username", name},
        {"password", password}
    };
    user.tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    qDebug() << "Client 发送" << json << Qt::endl;
}

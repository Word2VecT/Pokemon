#include "pokemoninfo.h"
#include "ui_pokemoninfo.h"
#include "user.h"
#include "config.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

extern User user;

pokemonInfo::pokemonInfo(int pokemonID, QWidget *parent)
    : QWidget(parent), ui(new Ui::pokemonInfo), pokemonID(pokemonID)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);
    QPixmap pixmap(POP_PATH);
    resize(pixmap.size());
    setMask(pixmap.mask());

    connect(ui->backButton, &QPushButton::clicked, this, [this](){
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &pokemonInfo::connectServer);
        this->close();
    });

    QJsonObject json = {
        {"type", POKEMON_INFO},
        {"socketID", user.socketID},
        {"pokemonID", pokemonID}
    };
    qDebug() << "pokemonInfo 发出请求：" << json << Qt::endl;
    user.tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());

    connect(user.tcpSocket, &QTcpSocket::readyRead, this, &pokemonInfo::connectServer);
}

pokemonInfo::~pokemonInfo()
{
    delete ui;
}

void pokemonInfo::connectServer()
{
    QByteArray array = user.tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();
    qDebug() << "pokemonInfo 收到服务器:" << json << Qt::endl;

    // if (json["socketID"].toInt() != user.socketID) {
    //     qDebug() << "socketID 不匹配" << json << Qt::endl;
    //     return;
    // }

    QString name = json["name"].toString();

    if (json["type"].toInt() == POKEMON_INFO) {
        ui->pokemonName->setText(name);
        ui->pokemonAtk->setText(QString::number(json["ATK"].toInt()));
        ui->pokemonDef->setText(QString::number(json["DEF"].toInt()));
        ui->pokemonExp->setText(QString::number(json["EXP"].toInt()));
        ui->pokemonHp->setText(QString::number(json["HP"].toInt()));
        ui->pokemonLv->setText(QString::number(json["LV"].toInt()));
        ui->pokemonSpeed->setText(QString::number(json["Speed"].toInt()));
        ui->pokemonImg->setStyleSheet(QString("image: url(%1);background: transparent;border: none;").arg(user.pokemonImg[name]));
    }
}

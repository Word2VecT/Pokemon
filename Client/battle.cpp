#include "battle.h"
#include "ui_battle.h"
#include "config.h"
#include "user.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

extern User user;

Battle::Battle(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Battle)
{
    ui->setupUi(this);

    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_NAME);
    setWindowIcon(QIcon(ICON_PATH));
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);

    connect(ui->backButton, &QPushButton::clicked, this, [=, this](){
        this->close();
    });

    connect(ui->fightBattleButton, &QPushButton::clicked, this, [=, this](){
        this->close();

        bag = new Bag(0, BATTLE_LIST);
        bag->exec();

        Bag *newBag;
        newBag = new Bag(user.id, CHOSE);
        newBag->exec();

        QJsonObject json = {
            {"type", FIGHT_BATTLE},
            {"socketID", user.socketID},
            {"userID", user.id},
            {"pokemonID", user.pokemonID},
            {"enemyID", user.enemyID}
        };

        user.tcpSocket->write(QString (QJsonDocument(json).toJson()).toUtf8().data());
        qDebug() << "Client 发送" << json << Qt::endl;

        connect(user.tcpSocket, &QTcpSocket::readyRead, this, &Battle::connectServer);
    });

    connect(ui->lvUpButton, &QPushButton::clicked, this, [=, this](){
        this->close();

        bag = new Bag(0, BATTLE_LIST);
        bag->exec();

        Bag *newBag;
        newBag = new Bag(user.id, CHOSE);
        newBag->exec();

        QJsonObject json = {
            {"type", LV_UP_BATTLE},
            {"socketID", user.socketID},
            {"pokemonID", user.pokemonID},
            {"enemyID", user.enemyID}
        };

        user.tcpSocket->write(QString (QJsonDocument(json).toJson()).toUtf8().data());
        qDebug() << "Client 发送" << json << Qt::endl;

        connect(user.tcpSocket, &QTcpSocket::readyRead, this, &Battle::connectServer);
    });
}

Battle::~Battle()
{
    delete ui;
}

void Battle::connectServer()
{
    QByteArray array = user.tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();

    qDebug() << "Bag 收到服务器" << json << Qt::endl;
    // if (json["socketID"].toInt() != user.socketID) {
    //     return;
    // }
    int type = json["type"].toInt();
    if (type == LV_UP_BATTLE || type == FIGHT_BATTLE) {
        stadium = new Stadium(json);
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Battle::connectServer);
        stadium->show();
    }
}

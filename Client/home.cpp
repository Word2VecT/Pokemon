#include "home.h"
#include "ui_home.h"
#include "config.h"
#include "user.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

extern User user;

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_NAME);
    setWindowIcon(QIcon(ICON_PATH));
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);

    connect(ui->backButton, &QPushButton::clicked, this, [=, this](){
        QJsonObject json = {
            {"type", LOGOUT},
            {"userID", user.id}
        };
        user.tcpSocket->write(QString (QJsonDocument(json).toJson()).toUtf8().data());
        qDebug() << "Client 发送" << json << Qt::endl;
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Home::connectServer);
        this->close();
    });

    connect(ui->bagButton, &QPushButton::clicked, this, [=, this] {
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Home::connectServer);
        bag = new Bag(user.id, BAG);
        bag->show();
    });

    connect(ui->rankButton, &QPushButton::clicked, this, [=, this] {
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Home::connectServer);
        rank = new Rank();
        rank->show();
    });

    connect(ui->battleButton, &QPushButton::clicked, this, [=, this] {
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Home::connectServer);
        battle = new Battle();
        battle->show();
    });

    connect(ui->flashButton, &QPushButton::clicked, this, [=, this] {
        connect(user.tcpSocket, &QTcpSocket::readyRead, this, &Home::connectServer);
        checkPokemonAndUserInfo();
        this->update();
    });

    connect(user.tcpSocket, &QTcpSocket::readyRead, this, &Home::connectServer);

    if (user.tcpSocket->state() == QTcpSocket::ConnectedState) {
        qDebug() << "Socket is connected.";
    } else {
        qDebug() << "Socket is not connected.";
    }

    checkPokemonAndUserInfo();
}

Home::~Home()
{
    delete ui;
}

void Home::checkPokemonAndUserInfo()
{
    QJsonObject json = {
        {"type", CHECK_POKEMON_AND_USER_INFO},
        {"socketID", user.socketID},
        {"userID", user.id}
    };
    user.tcpSocket->write(QString (QJsonDocument(json).toJson()).toUtf8().data());
    qDebug() << "Client 发送" << json << Qt::endl;
}

void Home::connectServer()
{
    QByteArray array = user.tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();

    qDebug() << "checkPokemonAndUserInfo 收到服务器" << json << Qt::endl;
    if (json["socketID"].toInt() != user.socketID) {
        return;
    }

    int pokemonCnt = json["pokemonCnt"].toInt();
    if (!pokemonCnt) {
        user.showMsgBox("糟糕", "您似乎没有宝可梦了!\n系统为你赠送了一只" + json["randomPokemon"].toString());
    } else {
        qDebug() << pokemonCnt << Qt::endl;
    }
    int highPokemonCnt = json["highPokemonCnt"].toInt();
    ui->pokemonCntMedalBronzeLabel->setText("x" + QString::number(pokemonCnt % 10));
    ui->pokemonCntMedalSilverLabel->setText("x" + QString::number((pokemonCnt / 10) % 10));
    ui->pokemonCntMedalGoldenLabel->setText("x" + QString::number(pokemonCnt / 100));
    ui->highPokemonMedalBronzeLabel->setText("x" + QString::number(highPokemonCnt % 10));
    ui->highPokemonMedalSilverLabel->setText("x" + QString::number((highPokemonCnt / 10) % 10));
    ui->highPokemonMedalGoldenLabel->setText("x" + QString::number(highPokemonCnt / 100));

    int battleCnt = json["battleCnt"].toInt();
    int battleWinCnt = json["battleWinCnt"].toInt();
    ui->battleCnt->setText(QString::number(battleCnt));
    ui->battleWinCnt->setText(QString::number(battleWinCnt));
    QString winRate;
    if (battleCnt) {
        winRate = QString::number(static_cast<double>(battleWinCnt) / battleCnt * 100, 'f', 2) + "%";
    } else {
        winRate = "暂无";
    }
    ui->battleWinRate->setText(winRate);
    ui->nameLabel->setText("训练师 " + user.name);
    ui->nameLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

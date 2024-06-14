#include "bag.h"
#include "ui_bag.h"
#include "config.h"
#include "ui_listitem.h"
#include "user.h"
#include "listitem.h"
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScroller>
#include <QJsonArray>

extern User user;

Bag::Bag(int queryUserID, int type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Bag), list(new QListWidget(this)), queryUserID(queryUserID), type(type)
{
    ui->setupUi(this);

    setWindowTitle(GAME_NAME);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);
    QPixmap pixmap(BAG_PATH);
    resize(pixmap.size());
    setMask(pixmap.mask());

    list->setViewMode(QListView::ListMode);
    list->setFlow(QListView::LeftToRight);
    list->setFixedSize(640, 450);
    list->setStyleSheet("background:transparent");
    list->setFrameShape(QListWidget::NoFrame);
    list->move(10, 125);
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if (type != BAG) {
        ui->backButton->hide();
    }

    connect(ui->backButton, &QPushButton::clicked, this, [this](){
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Bag::connectServer);
        this->close();
    });

    int cnt = list->count();
    for (int i = 0; i < cnt; ++i) {
        QListWidgetItem *item = list->takeItem(0);
        list->removeItemWidget(item);
        delete item;
    }

    QJsonObject json = {
            {"type", type},
            {"socketID", user.socketID},
            {"userID", queryUserID}
        };

    qDebug() << "Bag 发出请求：" << json << Qt::endl;
    user.tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());

    connect(user.tcpSocket, &QTcpSocket::readyRead, this, &Bag::connectServer);
}

Bag::~Bag()
{
    delete ui;
}

void Bag::connectServer()
{
    QByteArray array = user.tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();

    qDebug() << "Bag 收到服务器" << json << Qt::endl;
    // if (json["socketID"].toInt() != user.socketID) {
    //     return;
    // }

    list->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(list, QScroller::LeftMouseButtonGesture);

    // disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Bag::connectServer);

    if (type == BAG || type == CHOSE) {
        getUserPokemonList(json);
    } else if (type == BATTLE_LIST) {
        getSystemPokemonList(json);
    } else if (type == ABANDON) {
        get3UserPokemonList(json);
    }
}

void Bag::getUserPokemonList(QJsonObject json)
{
    QJsonArray pokemons(json["pokemons"].toArray());
    int pokemonCnt = pokemons.size();
    qDebug() << pokemonCnt << "只" << json << Qt::endl;

    if (type == CHOSE) {
        ui->text->setText(QString("选择自己的宝可梦"));
    }

    for (int i = 0; i < pokemonCnt; ++i) {
        QJsonObject pokemon = pokemons[i].toObject();
        QString name = pokemon["name"].toString();
        int pokemonID = pokemon["pokemonID"].toInt();
        int LV = pokemon["LV"].toInt();

        ListItem *item = new ListItem(name, pokemonID, LV, this);
        QListWidgetItem *item0 = new QListWidgetItem();
        item0->setSizeHint(QSize(205,300));
        list->addItem(item0);
        list->setItemWidget(item0, item);

        connect(item->ui->img, &QPushButton::clicked, this, [=, this](){
            qDebug() << "选中的宝可梦ID:" << pokemonID << Qt::endl;
            if (type == BAG) {
                if (info) {
                    delete info;
                }
                disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Bag::connectServer);
                info = new pokemonInfo(pokemonID);
                info->show();
            } else if (type == CHOSE) {
                user.pokemonID = pokemonID;
                qDebug() << "选中己方宝可梦ID:" << user.pokemonID << "\n" << "选中敌方宝可梦ID:" << user.enemyID << Qt::endl;
                ui->backButton->click();
            }
        });
    }
}

void Bag::getSystemPokemonList(QJsonObject json)
{
    QJsonArray pokemons(json["pokemons"].toArray());
    int pokemonCnt = pokemons.size();
    qDebug() << pokemonCnt << "只" << json << Qt::endl;
    ui->text->setText(QString("选择要挑战的宝可梦"));

    for (int i = 0; i < pokemonCnt; ++i) {
        QJsonObject pokemon = pokemons[i].toObject();
        QString name = pokemon["name"].toString();
        int pokemonID = pokemon["pokemonID"].toInt();
        int LV = pokemon["LV"].toInt();

        ListItem *item = new ListItem(name, pokemonID, LV, this);
        QListWidgetItem *item0 = new QListWidgetItem();
        item0->setSizeHint(QSize(205,300));
        list->addItem(item0);
        list->setItemWidget(item0, item);

        connect(item->ui->img, &QPushButton::clicked, this, [=, this](){
            qDebug() << "选中的宝可梦ID:" << pokemonID << Qt::endl;
            user.enemyID = pokemonID;
            ui->backButton->click();
        });
    }
}

void Bag::get3UserPokemonList(QJsonObject json)
{
    QJsonArray pokemons(json["pokemons"].toArray());
    int pokemonCnt = pokemons.size();
    qDebug() << pokemonCnt << "只" << json << Qt::endl;
    ui->text->setText(QString("选择要抛弃的宝可梦"));

    for (int i = 0; i < pokemonCnt; ++i) {
        QJsonObject pokemon = pokemons[i].toObject();
        QString name = pokemon["name"].toString();
        int pokemonID = pokemon["pokemonID"].toInt();
        int LV = pokemon["LV"].toInt();

        ListItem *item = new ListItem(name, pokemonID, LV, this);
        QListWidgetItem *item0 = new QListWidgetItem();
        item0->setSizeHint(QSize(205,300));
        list->addItem(item0);
        list->setItemWidget(item0, item);

        connect(item->ui->img, &QPushButton::clicked, this, [=, this](){
            qDebug() << "选中的宝可梦ID:" << pokemonID << Qt::endl;
            QJsonObject abandonJson = {
                {"type", ABANDON_CONFIRM},
                {"socketID", user.socketID},
                {"pokemonID", pokemonID},
                {"userID", user.id},
            };
            qDebug() << "Bag 发出请求：" << json << Qt::endl;
            user.tcpSocket->write(QString(QJsonDocument(abandonJson).toJson()).toUtf8().data());
            ui->backButton->click();
        });
    }
}

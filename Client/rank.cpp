#include "rank.h"
#include "ui_rank.h"
#include "user.h"
#include "config.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

extern User user;

Rank::Rank(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Rank), model(new QStandardItemModel(0, 5, this))
{
    ui->setupUi(this);
    setWindowTitle(GAME_NAME);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);
    QPixmap pixmap(BAG_PATH);
    resize(pixmap.size());
    setMask(pixmap.mask());

    model->setHeaderData(0, Qt::Horizontal, "用户名");
    model->setHeaderData(1, Qt::Horizontal, "用户 ID");
    model->setHeaderData(2, Qt::Horizontal, "宠物个数");
    model->setHeaderData(3, Qt::Horizontal, "高级宠物个数");
    model->setHeaderData(4, Qt::Horizontal, "是否在线");

    ui->rankList->setModel(model);

    ui->rankList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 列宽自适应
    ui->rankList->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->backButton, &QPushButton::clicked, this, [this](){
        disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Rank::connectServer);
        this->close();
    });

    QJsonObject json = {
        {"type", RANK},
        {"socketID", user.socketID}
    };

    qDebug() << "Rank 发出请求：" << json << Qt::endl;
    user.tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());

    connect(user.tcpSocket, &QTcpSocket::readyRead, this, &Rank::connectServer);

    connect(ui->rankList, &QTableView::clicked, this, &Rank::showUserPokemons);
}

Rank::~Rank()
{
    delete ui;
}

void Rank::connectServer()
{
    QByteArray array = user.tcpSocket->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
    QJsonObject json = jsonDocument.object();

    qDebug() << "Rank 收到服务器" << json << Qt::endl;
    if (json["socketID"].toInt() != user.socketID) {
        return;
    }
    if (json["type"] == RANK) {
        QJsonArray users(json["users"].toArray());
        int userCnt = users.size();
        qDebug() << userCnt << "个" << json << Qt::endl;
        for (int i = 0; i < userCnt; ++i) {
            QJsonObject userItem = users[i].toObject();
            QString username = userItem["username"].toString();
            int userID = userItem["userID"].toInt();
            int pokemonCnt = userItem["pokemonCnt"].toInt();
            int highPokemonCnt = userItem["highPokemonCnt"].toInt();
            QString online = "不在线";
            if (userItem["online"].toInt()) {
                online = "在线";
            }
            int row = model->rowCount();
            model->insertRow(row);
            model->setData(model->index(row, 0), username);
            model->setData(model->index(row, 1), userID);
            model->setData(model->index(row, 2), pokemonCnt);
            model->setData(model->index(row, 3), highPokemonCnt);
            model->setData(model->index(row, 4), online);
        }
    }
}

void Rank::showUserPokemons(const QModelIndex &index)
{
    int row = index.row();
    int userID = model->data(model->index(row, 1)).toInt();

    disconnect(user.tcpSocket, &QTcpSocket::readyRead, this, &Rank::connectServer);

    bag = new Bag(userID, BAG);
    bag->show();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manager.h"
#include "config.h"
#include <QJsonDocument>
#include <QString>
#include <QByteArray>
#include <QSqlQuery>
#include <QJsonArray>
#include <QSqlRecord>
#include <QRandomGenerator>

extern Manager manager;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), tcpServer(new QTcpServer(this))
{
    ui->setupUi(this);

    tcpServer->listen(QHostAddress::Any, 8888);

    setWindowTitle("Server Port: 8888");

    connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::whenNewConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendAllScokets(QJsonObject json)
{
    int clientNum = socketList.size();
    qDebug() << "向" << clientNum << "个 Client 发送 Socket" << Qt::endl;
    qDebug() << json << Qt::endl;
    for (int i = 0; i < clientNum; ++i) {
        socketList[i]->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    }
}

void MainWindow::whenNewConnection()
{
    QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
    QJsonObject json = {
        {"socketID", socketID++}
    };
    tcpSocket->write(QString(QJsonDocument(json).toJson()).toUtf8().data());
    socketList.append(tcpSocket);

    connect(tcpSocket, &QTcpSocket::readyRead, this, [=, this](){
        QByteArray array = tcpSocket->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(array);
        QJsonObject json = jsonDocument.object();

        qDebug() << "请求为" << json["type"].toInt() << "操作" << Qt::endl;
        switch (json["type"].toInt()) {
        case LOGIN:
            qDebug() << "请求登陆" << Qt::endl;
            login(json);
            break;
        case REGIST:
            qDebug() << "请求注册" << Qt::endl;
            regist(json);
            break;
        case CHECK_POKEMON_AND_USER_INFO:
            qDebug() << "请求查询是否没有宝可梦和其他个人信息" << Qt::endl;
            checkPokemonAndUserInfo(json);
            break;
        case POKEMON_INFO:
            qDebug() << "请求查询宝可梦信息" << Qt::endl;
            getPokeminInfo(json);
            break;
        case BAG:
        case CHOSE:
            qDebug() << "请求查询背包信息" << Qt::endl;
            getAllPokemon(json);
            break;
        case ABANDON:
            qDebug() << "请求查询背包3个宝可梦信息" << Qt::endl;
            get3Pokemon(json);
            break;
        case RANK:
            qDebug() << "请求查询所有在线用户" << Qt::endl;
            getOnlineUser(json);
            break;
        case BATTLE_LIST:
            qDebug() << "请求查询系统虚拟精灵" << Qt::endl;
            getSystemPokemon(json);
            break;
        case LV_UP_BATTLE:
        case FIGHT_BATTLE:
            qDebug() << "请求进行战斗" << Qt::endl;
            battle(json);
            break;
        case ABANDON_CONFIRM:
            qDebug() << "请求丢弃一只精灵" << Qt::endl;
            abandonOnePokemon(json);
            break;
        case LOGOUT:
            qDebug() << "请求登出" << Qt::endl;
            logout(json);
            break;
        default:
            break;
        }
    });
}

void MainWindow::login(QJsonObject json)
{
    QSqlQuery query(db);
    if (!db.isOpen()) {
        qDebug() << "数据库未连接" << Qt::endl;
    }
    QString username = json["username"].toString();
    QString password = json["password"].toString();
    QString result;
    int userID;
    int _socketID = json["socketID"].toInt();
    qDebug() << "username:" << username << Qt::endl;

    QString sql = QString("SELECT password, userID FROM user WHERE username = '%1';").arg(username);
    qDebug() << "sql:" << sql << Qt::endl;
    query.exec(sql);
    while (query.next()) {
        result = query.value(0).toString();
        userID = query.value(1).toInt();
    }
    qDebug() << "password" << result << Qt::endl;

    if (result == password) {
        qDebug() << "密码正确" << Qt::endl;
        json = {
            {"type", LOGIN_SUCCEED},
            {"socketID", _socketID},
            {"username", username},
            {"userID", userID}
    };
        qDebug() << QString(QJsonDocument(json).toJson()) << Qt::endl;
        sql = QString("UPDATE user SET online = 1 WHERE username = '%1';").arg(username);
        qDebug() << "sql:" << sql << Qt::endl;
        query.exec(sql);
    } else {
        qDebug() << "密码错误" << Qt::endl;
        qDebug() << "password" << result << ":" << password << Qt::endl;
        json = {
            {"type", LOGIN_FAILED}
        };
    }
    qDebug() << QString(QJsonDocument(json).toJson()) << Qt::endl;

    sendAllScokets(json);
}

void MainWindow::regist(QJsonObject json)
{
    QSqlQuery query(db);
    QString username = json["username"].toString();
    QString password = json["password"].toString();
    int _socketID = json["socketID"].toInt();

    QString sql = QString("SELECT username FROM user WHERE username = '%1';").arg(username);
    qDebug() << "sql:" << sql << Qt::endl;
    query.exec(sql);
    query.next();
    if (query.value(0).toString().isEmpty()) {
        qDebug() << "插入新用户信息" << Qt::endl;
        sql = QString("INSERT INTO user (username, password, online) VALUES ('%1', '%2', %3);").arg(username, password, QString::number(0));
        qDebug() << "sql:" << sql << Qt::endl;
        query.exec(sql);

        qDebug() << "查找用户 ID" << Qt::endl;
        sql = QString("SELECT userID FROM user WHERE username = '%1';").arg(username);
        qDebug() << "sql:" << sql << Qt::endl;
        query.exec(sql);
        query.first();

        int userID = query.value(0).toInt();
        qDebug() << "ID:" << userID << Qt::endl;
        json = {
            {"type", REGIST_SUCCEED},
            {"socketID", _socketID},
            };
    } else {
        qDebug() << "用户名已存在" << Qt::endl;
        json = {
            {"type", REGIST_FAILED},
            {"socketID", _socketID},
            };
    }

    sendAllScokets(json);
}

void MainWindow::getPokeminInfo(QJsonObject json)
{
    int pokemonID = json["pokemonID"].toInt();
    int _socketID = json["socketID"].toInt();

    QSqlQuery query(db);
    QString sql = QString("SELECT * FROM pokemon WHERE pokemonID = %1;").arg(pokemonID);
    query.exec(sql);
    query.next();

    json = {
        {"type", POKEMON_INFO},
        {"scoketID", _socketID},
        {"name", query.value(1).toString()},
        {"HP", query.value(2).toInt()},
        {"ATK", query.value(3).toInt()},
        {"DEF", query.value(4).toInt()},
        {"EXP", query.value(5).toInt()},
        {"LV", query.value(6).toInt()},
        {"Speed", query.value(7).toInt()}
    };
    qDebug() << "返回 pokemonInfo："<< json << Qt::endl;
    sendAllScokets(json);
}

void MainWindow::checkPokemonAndUserInfo(QJsonObject json)
{
    int userID = json["userID"].toInt();
    int _socketID = json["socketID"].toInt();

    QSqlQuery query(db);
    QString sql = QString("SELECT pokemonCnt, highPokemonCnt, battleCnt, battleWinCnt FROM user WHERE userID = %1;").arg(QString::number(userID));
    qDebug() << sql << Qt::endl;
    query.exec(sql);
    query.next();
    int pokemonCnt = query.value(0).toInt();
    int highPokemonCnt = query.value(1).toInt();
    int battleCnt = query.value(2).toInt();
    int battleWinCnt = query.value(3).toInt();

    if (pokemonCnt) {
        json = {
            {"type", CHECK_POKEMON_AND_USER_INFO},
            {"socketID", _socketID},
            {"pokemonCnt", pokemonCnt},
            {"highPokemonCnt", highPokemonCnt},
            {"battleCnt", battleCnt},
            {"battleWinCnt", battleWinCnt}
            };
    } else {
        int index = QRandomGenerator::global()->bounded(ALL_POKEMON_CNT);
        QString randomPokemon = manager.allPokemon[index];
        json = {
            {"type", CHECK_POKEMON_AND_USER_INFO},
            {"socketID", _socketID},
            {"pokemonCnt", pokemonCnt},
            {"highPokemonCnt", highPokemonCnt},
            {"randomPokemon", randomPokemon},
            {"battleCnt", battleCnt},
            {"battleWinCnt", battleWinCnt}
        };

        sql = QString("INSERT INTO pokemon (name, HP, ATK, DEF, EXP, LV, Speed, userID) VALUES ('%1', %2, %3, %4, %5, %6, %7, %8);").arg(randomPokemon, QString::number(INIT_HP), QString::number(INIT_ATK), QString::number(INIT_DEF), QString::number(0), QString::number(1), QString::number(INIT_SPEED), QString::number(userID));
        query.exec(sql);
        query.next();

        sql = QString("UPDATE user SET pokemonCnt = COALESCE(pokemonCnt, 0) + 1 WHERE userID = %1;").arg(userID);
        query.exec(sql);
    }

    qDebug() << "checkPokemonAndUserInfo 发送" << json << Qt::endl;
    sendAllScokets(json);
}

void MainWindow::getAllPokemon(QJsonObject json)
{
    qDebug() << "Bag 传来" << json << Qt::endl;
    QJsonArray array;
    int userID = json["userID"].toInt();
    int _socketID = json["socketID"].toInt();

    QSqlQuery query(db);
    QString sql = QString("SELECT pokemonID, name, LV FROM pokemon WHERE userID = %1;").arg(userID);
    query.exec(sql);
    while (query.next()) {
        int pokemonID = query.value(0).toInt();
        QString name = query.value(1).toString();
        int LV = query.value(2).toInt();
        QJsonObject pokemon = {
            {"pokemonID", pokemonID},
            {"name", name},
            {"LV", LV}
        };
        qDebug() << "宝可梦" << pokemon << Qt::endl;
        array.append(pokemon);
    }

    int type = json["type"].toInt();
    json = {
        {"type", type},
        {"socketID", _socketID},
        {"pokemons", array}
        };
    qDebug() << "getAllPokemon 发送" << json << Qt::endl;
    sendAllScokets(json);
}

void MainWindow::getOnlineUser(QJsonObject json)
{
    int _socketID = json["socketID"].toInt();
    QJsonArray array;

    QSqlQuery query(db);
    QString sql = QString("SELECT username, userID, pokemonCnt, highPokemonCnt, online FROM user ORDER BY online DESC, pokemonCnt DESC, highPokemonCnt DESC;");
    query.exec(sql);
    while (query.next()) {
        QString username = query.value(0).toString();
        int userID = query.value(1).toInt();
        int pokemonCnt = query.value(2).toInt();
        int highPokemonCnt = query.value(3).toInt();
        int online = query.value(4).toInt();
        QJsonObject userItem = {
            {"username", username},
            {"userID", userID},
            {"pokemonCnt", pokemonCnt},
            {"highPokemonCnt", highPokemonCnt},
            {"online", online}
        };
        qDebug() << "用户" << userItem << Qt::endl;
        array.append(userItem);
    }

    json = {
        {"type", RANK},
        {"socketID", _socketID},
        {"users", array}
    };
    qDebug() << "getOnlineUser 发送" << json << Qt::endl;
    sendAllScokets(json);
}

void MainWindow::getSystemPokemon(QJsonObject json)
{
    qDebug() << "Battle 传来" << json << Qt::endl;
    QJsonArray array;
    int _socketID = json["socketID"].toInt();

    QSqlQuery query(db);
    QString sql = QString("SELECT pokemonID, name, LV FROM pokemon ORDER BY RAND() LIMIT 5;");
    query.exec(sql);
    while (query.next()) {
        int pokemonID = query.value(0).toInt();
        QString name = query.value(1).toString();
        int LV = query.value(2).toInt();
        QJsonObject pokemon = {
            {"pokemonID", pokemonID},
            {"name", name},
            {"LV", LV}
        };
        qDebug() << "宝可梦" << pokemon << Qt::endl;
        array.append(pokemon);
    }

    json = {
        {"type", BATTLE_LIST},
        {"socketID", _socketID},
        {"pokemons", array}
    };
    qDebug() << "getSystemPokemon 发送" << json << Qt::endl;
    sendAllScokets(json);
}

void MainWindow::battle(QJsonObject json)
{
    qDebug() << "Battle 传来" << json << Qt::endl;
    int _socketID = json["socketID"].toInt();

    int pokemonID = json["pokemonID"].toInt();
    int enemyID = json["enemyID"].toInt();

    QSqlQuery query(db);
    QString sql = QString("SELECT * FROM pokemon WHERE pokemonID = %1;").arg(pokemonID);
    query.exec(sql);
    query.next();
    QString name = query.value(1).toString();
    int HP = query.value(2).toInt();
    int ATK = query.value(3).toInt();
    int DEF = query.value(4).toInt();
    int LV = query.value(6).toInt();
    int Speed = query.value(7).toInt();
    int userID = query.value(8).toInt();
    int pokemonMaxHp = HP;
    int pokemonLV = LV;

    sql = QString("UPDATE user SET battleCnt = COALESCE(battleCnt, 0) + 1 WHERE userID = %1;").arg(userID);
    query.exec(sql);
    query.next();

    sql = QString("SELECT * FROM pokemon WHERE pokemonID = %1;").arg(enemyID);
    query.exec(sql);
    query.next();
    QString enemyName = query.value(1).toString();
    int enemyHP = query.value(2).toInt();
    int enemyATK = query.value(3).toInt();
    int enemyDEF = query.value(4).toInt();
    int enemyLV = query.value(6).toInt();
    int enemySpeed = query.value(7).toInt();
    int enemyMaxHp = enemyHP;

    Pokemon *pokemon = manager.createPokemon(name, LV, ATK, DEF, HP, Speed);
    Pokemon *beforeBattle = manager.createPokemon(name, LV, ATK, DEF, HP, Speed);
    Pokemon *enemy = manager.createPokemon(enemyName, enemyLV, enemyATK, enemyDEF, enemyHP, enemySpeed);

    QJsonArray array;
    QJsonObject turn;
    bool firstEnemy = false;
    if (enemy->getSpeed() > pokemon->getSpeed()) {
        firstEnemy = true;
        int random = enemy->attack(pokemon);
        QString ability = "普通攻击";
        if (enemyLV >= 10) {
            ability = enemy->getAbility();
        }
        turn = {
            {"pokemonHP", pokemon->getHp()},
            {"enemyHP", enemy->getHp()},
            {"attacker", enemy->getName()},
            {"random", random},
            {"ability", ability}
            };
        qDebug() << "攻击" << turn << Qt::endl;
        array.append(turn);
    }
    while (enemy->getHp() > 0 && pokemon->getHp() > 0) {
        int random = pokemon->attack(enemy);
        QString ability = "普通攻击";
        if (LV >= 10) {
            ability = pokemon->getAbility();
        }
        turn = {
            {"pokemonHP", pokemon->getHp()},
            {"enemyHP", enemy->getHp()},
            {"attacker", pokemon->getName()},
            {"random", random},
            {"ability", ability}
        };
        qDebug() << "攻击" << turn << Qt::endl;
        array.append(turn);
        if (enemy->getHp() > 0) {
            int random = enemy->attack(pokemon);
            QString ability = "普通攻击";
            if (LV >= 10) {
                ability = enemy->getAbility();
            }
            turn = {
                {"pokemonHP", pokemon->getHp()},
                {"enemyHP", enemy->getHp()},
                {"attacker", enemy->getName()},
                {"random", random},
                {"ability", ability}
            };
            qDebug() << "攻击" << turn << Qt::endl;
        }
        array.append(turn);
    }

    bool win = pokemon->getHp() > 0;
    int type = json["type"].toInt();
    bool lvUp = false;
    if (type == LV_UP_BATTLE) {
        if (win) {
            sql = QString("SELECT EXP, LV FROM pokemon WHERE pokemonID = %1;").arg(pokemonID);
            query.exec(sql);
            query.next();
            int tempEXP = query.value(0).toInt();
            int tempLV = query.value(1).toInt();
            if (tempEXP == MAX_LV - 1 && tempLV == MAX_LV - 1) {
                sql = QString("UPDATE user SET highPokemonCnt = pokmonCnt - 1 WHERE userID = %1;").arg(userID);
                query.exec(sql);
            }
            if (tempLV != MAX_LV && ++tempEXP >= tempLV) {
                tempEXP = 0;
                tempLV++;
                lvUp = true;
                beforeBattle->lvUp();
            }
            sql = QString("UPDATE pokemon SET HP = %1, ATK = %2, DEF = %3, Speed = %4, EXP = %5, LV = %6 WHERE pokemonID = %7;").arg(QString::number(beforeBattle->getHp()), QString::number(beforeBattle->getAtk()), QString::number(beforeBattle->getDef()), QString::number(beforeBattle->getSpeed()), QString::number(tempEXP), QString::number(tempLV), QString::number(pokemonID));
            query.exec(sql);
            query.next();
            qDebug() << sql << Qt::endl;
            sql = QString("UPDATE user SET pokemonCnt = pokemonCnt + 1, battleWinCnt = COALESCE(battleWinCnt, 0) + 1 WHERE userID = %1;").arg(userID);
            query.exec(sql);
            query.next();
        }
        json = {
            {"type", LV_UP_BATTLE},
            {"socketID", _socketID},
            {"pokemonName", pokemon->getName()},
            {"enemyName", enemy->getName()},
            {"pokemonAbility", pokemon->getAbility()},
            {"enemyAbility", enemy->getAbility()},
            {"pokemonLv", pokemonLV},
            {"enemyLv", enemy->getLv()},
            {"pokemonHp", pokemonMaxHp},
            {"enemyHp", enemyMaxHp},
            {"firstEnemy", firstEnemy},
            {"turn", array},
            {"win", win},
            {"lvUp", lvUp}
        };
    } else if (type == FIGHT_BATTLE){
        if (win) {
            sql = QString("INSERT INTO pokemon (name, HP, ATK, DEF, EXP, LV, Speed, UserID) SELECT name, HP, ATK, DEF, EXP, LV, Speed, %1 FROM pokemon WHERE pokemonID = %2;").arg(QString::number(userID), QString::number(enemyID));
            query.exec(sql);
            query.next();
            qDebug() << sql << Qt::endl;
            sql = QString("UPDATE user SET pokemonCnt = pokemonCnt + 1, battleWinCnt = COALESCE(battleWinCnt, 0) + 1 WHERE userID = %1;").arg(userID);
            query.exec(sql);
            query.next();
        }
        json = {
            {"type", FIGHT_BATTLE},
            {"socketID", _socketID},
            {"pokemonName", pokemon->getName()},
            {"enemyName", enemy->getName()},
            {"pokemonAbility", pokemon->getAbility()},
            {"enemyAbility", enemy->getAbility()},
            {"pokemonLv", pokemonLV},
            {"enemyLv", enemy->getLv()},
            {"pokemonHp", pokemonMaxHp},
            {"enemyHp", enemyMaxHp},
            {"firstEnemy", firstEnemy},
            {"turn", array},
            {"win", win}
        };
    }

    qDebug() << "battle 发送" << json << Qt::endl;
    sendAllScokets(json);
}

void MainWindow::get3Pokemon(QJsonObject json)
{
    qDebug() << "Stadium 传来" << json << Qt::endl;
    QJsonArray array;
    int _socketID = json["socketID"].toInt();
    int userID = json["userID"].toInt();

    QSqlQuery query(db);
    QString sql = QString("SELECT pokemonID, name, LV FROM pokemon WHERE userID = %1 ORDER BY RAND() LIMIT 3;").arg(userID);
    qDebug() << sql << Qt::endl;
    query.exec(sql);
    while (query.next()) {
        int pokemonID = query.value(0).toInt();
        QString name = query.value(1).toString();
        int LV = query.value(2).toInt();
        QJsonObject pokemon = {
            {"pokemonID", pokemonID},
            {"name", name},
            {"LV", LV}
        };
        qDebug() << "宝可梦" << pokemon << Qt::endl;
        array.append(pokemon);
    }

    json = {
        {"type", ABANDON},
        {"socketID", _socketID},
        {"pokemons", array}
    };
    qDebug() << "get3Pokemon 发送" << json << Qt::endl;
    sendAllScokets(json);
}

void MainWindow::abandonOnePokemon(QJsonObject json)
{
    QSqlQuery query(db);
    int pokemonID = json["pokemonID"].toInt();
    int userID = json["userID"].toInt();

    QString sql = QString("DELETE FROM pokemon WHERE pokemonID = %1;").arg(QString::number(pokemonID));
    query.exec(sql);
    query.next();
    sql = QString("UPDATE user SET pokemonCnt = pokmonCnt - 1 WHERE userID = %1;").arg(QString::number(userID));
    query.exec(sql);
    query.next();

    sql = QString("SELECT pokemonCnt WHERE userID = %1;").arg(QString::number(userID));
    qDebug() << sql << Qt::endl;
    query.exec(sql);
    query.next();
    int pokemonCnt = query.value(0).toInt();
    if (!pokemonCnt) {
        int index = QRandomGenerator::global()->bounded(ALL_POKEMON_CNT);
        QString randomPokemon = manager.allPokemon[index];

        sql = QString("INSERT INTO pokemon (name, HP, ATK, DEF, EXP, LV, Speed, userID) VALUES ('%1', %2, %3, %4, %5, %6, %7, %8);").arg(randomPokemon, QString::number(INIT_HP), QString::number(INIT_ATK), QString::number(INIT_DEF), QString::number(0), QString::number(1), QString::number(INIT_SPEED), QString::number(userID));
        query.exec(sql);
        query.next();
        sql = QString("UPDATE user SET pokemonCnt = 1 WHERE userID = %1;").arg(QString::number(userID));
        query.exec(sql);
        query.next();
    }
}

void MainWindow::logout(QJsonObject json)
{
    QSqlQuery query(db);
    int userID = json["userID"].toInt();
    QString sql = QString("UPDATE user SET online = 0 WHERE userID = '%1';").arg(QString::number(userID));
    query.exec(sql);
    query.next();
}

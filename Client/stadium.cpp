#include "stadium.h"
#include "ui_result.h"
#include "ui_stadium.h"
#include "config.h"
#include "user.h"
#include <QJsonDocument>
#include <QJsonArray>

extern User user;

Stadium::Stadium(QJsonObject json, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Stadium), json(json)
{
    ui->setupUi(this);

    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_NAME);
    setWindowIcon(QIcon(ICON_PATH));
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);

    int enemyLv = json["enemyLv"].toInt();
    int pokemonLv = json["pokemonLv"].toInt();
    if (pokemonLv >= 10) {
        ui->pokemonAbility->setText(QString("技能：") + json["pokemonAbility"].toString());
    } else {
        ui->pokemonAbility->setText(QString("技能：未解锁"));
    }
    if (enemyLv >= 10) {
        ui->enemyAbility->setText(QString("技能：") + json["enemyAbility"].toString());
    } else {
        ui->enemyAbility->setText(QString("技能：未解锁"));
    }

    ui->enemyLv->setText(QString("Lv. ") + QString::number(enemyLv));
    ui->pokemonLv->setText(QString("Lv. ") + QString::number(pokemonLv));

    QString pokemonName = json["pokemonName"].toString();
    QString enemyName = json["enemyName"].toString();
    ui->enemyImg->setStyleSheet(QString("image: url(%1);background: transparent;border: none;").arg(user.pokemonImg[enemyName]));
    ui->pokemonImg->setStyleSheet(QString("image: url(%1);background: transparent;border: none;").arg(user.pokemonImg[pokemonName]));
    ui->pokemonName->setText(pokemonName);
    ui->enemyName->setText(enemyName);
    ui->textWe->setText("");
    ui->textName->setText("");
    ui->textUse->setText("");
    ui->textEffect->setText("");

    int pokemonMaxHp = json["pokemonHp"].toInt();
    int enemyMaxHp = json["enemyHp"].toInt();
    ui->pokemonHp->setRange(0, pokemonMaxHp);
    ui->enemyHp->setRange(0, enemyMaxHp);

    QJsonArray turns(json["turn"].toArray());
    int turnCnt = turns.size();
    qDebug() << turnCnt << "回合" << json << Qt::endl;

    timer = new QTimer(this);
    firstEnemy = json["firstEnemy"].toInt();
    turnNum = 0;

    bool win = json["win"].toBool();
    bool lvUp = json["lvUp"].toBool();
    int type = json["type"].toInt();
    connect(timer, &QTimer::timeout, this, [=, this](){
        QJsonObject turn = turns[turnNum].toObject();
        turnNum++;

        if (turnNum >= turnCnt - 1) {
            timer->stop();
            result = new Result();
            this->close();
            QString text;

            if (type == LV_UP_BATTLE) {
                if (win) {
                    if (lvUp) {
                        text = "EXP + 10\n宝可梦升级啦！";
                    } else {
                        text = "EXP + 10\n宝可梦还没有升级\n再练练吧！";
                    }
                } else {
                    text = "无事发生";
                    result->setStyleSheet(QString("background-image: url(:/background/elements/lose.png);"));
                    result->ui->title->setText(QString("你输了！"));
                }
                result->ui->img->setStyleSheet(QString("image: url(%1);background: transparent;border: none;").arg(user.pokemonImg[pokemonName]));
            } else if (type == FIGHT_BATTLE) {
                if (win) {
                    text = "恭喜！\n你得到了这只精灵";
                } else {
                    result->setStyleSheet(QString("background-image: url(:/background/elements/lose.png);"));
                    result->ui->title->setText(QString("你输了！"));
                    text = "很遗憾！\n你要失去一只精灵\n放心，没有了会给你再一个";
                }
                result->ui->img->setStyleSheet(QString("image: url(%1);background: transparent;border: none;").arg(user.pokemonImg[enemyName]));
            }
            result->ui->text->setText(text);
            result->exec();

            if (type == FIGHT_BATTLE && !json["win"].toBool()) {
                bag = new Bag(user.id, ABANDON);
                bag->exec();
            }
        }

        QString name = turn["attacker"].toString();
        QString ability = turn["ability"].toString();
        int pokemonHP = turn["pokemonHP"].toInt();
        int enemyHP = turn["enemyHP"].toInt();
        int random = turn["random"].toInt();
        QString effect;
        if (random == 0) {
            effect = "无事发生";
        } else if (random == 2) {
            effect = "效果拔群！";
        } else {
            effect = "普普通通";
        }
        ui->textEffect->setText(effect);
        ui->pokemonHp->setValue(pokemonHP);
        ui->enemyHp->setValue(enemyHP);
        ui->turnNum->setText(QString("第%1回合").arg(QString::number(turnNum)));
        if (firstEnemy) {
            ui->textWe->setText(QString("敌方"));
            ui->pokemonHpLabel->setText(QString("%1/%2").arg(QString::number(pokemonHP), QString::number(pokemonMaxHp)));
            firstEnemy = false;
        } else {
            ui->textWe->setText(QString("我方"));
            ui->enemyHpLabel->setText(QString::number(enemyHP) + QString("/") + QString::number(enemyMaxHp));
            firstEnemy = true;
        }
        ui->textName->setText(name);
        ui->textUse->setText(QString("使用了 ") + ability);
        this->update();
    });
    timer->start(1000);
}

Stadium::~Stadium()
{
    delete ui;
}

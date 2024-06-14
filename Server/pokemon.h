#ifndef POKEMON_H
#define POKEMON_H

#include <QString>
#include "config.h"
#include <QRandomGenerator>

// 基类：Pokemon
// 这个类表示一个基本的精灵，包含了精灵的基本属性和方法
class Pokemon {
protected:
    int id; // 精灵的唯一标识符

    QString name; // 精灵的名字
    bool evolved; // 精灵是否已进化

    int lv; // 精灵的等级
    int exp; // 精灵的经验值

    int atk; // 精灵的攻击力
    int def; // 精灵的防御力
    int hp; // 精灵的生命值
    int speed; // 精灵的速度

    QString type; // 精灵的种类
    QString ability; // 精灵的能力

public:
    // 构造函数，初始化精灵的属性
    Pokemon(QString name = "", int lv = 1, int atk = INIT_ATK, int def = INIT_DEF, int hp = INIT_HP, int speed = INIT_SPEED, QString ability = "");

    // 虚析构函数
    virtual ~Pokemon() {};

    // 获取精灵的名字
    QString getName() const;
    // 获取精灵的唯一标识符
    int getID() const;
    // 获取精灵的等级
    int getLv() const;
    // 获取精灵的经验值
    int getExp() const;
    // 获取精灵的攻击力
    int getAtk() const;
    // 获取精灵的防御力
    int getDef() const;
    // 获取精灵的生命值
    int getHp() const;
    // 获取精灵的速度
    int getSpeed() const;
    // 获取精灵的能力
    QString getAbility() const;

    // 设置精灵的等级
    void setLv(int);
    // 设置精灵的经验值
    void setExp(int);
    // 设置精灵的攻击力
    void setAtk(int);
    // 设置精灵的防御力
    void setDef(int);
    // 设置精灵的生命值
    void setHp(int);
    // 设置精灵的速度
    void setSpeed(int);

    // 判断精灵是否死亡
    bool isDead() const;

    // 虚函数：精灵升级，需要在派生类中实现
    virtual void lvUp() = 0;
    // 虚函数：精灵攻击另一个精灵，需要在派生类中实现
    virtual int attack(Pokemon*) = 0;
};

#endif // POKEMON_H

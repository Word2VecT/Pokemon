#ifndef ATTACKPOKEMON_H
#define ATTACKPOKEMON_H

#include "pokemon.h"

// 派生类：AttackPokemon
// 这个类继承自Pokemon，表示具有攻击能力的精灵
class AttackPokemon : public Pokemon {
public:
    // 继承基类Pokemon的构造函数
    using Pokemon::Pokemon;

    // 虚析构函数
    virtual ~AttackPokemon() {};

    // 重写基类的纯虚函数lvUp，实现精灵升级的逻辑
    void lvUp() override;

    // 纯虚函数：精灵攻击另一个精灵，需要在派生类中实现
    virtual int attack(Pokemon*) override = 0;
};

// 派生类：Charmander
// 这个类继承自AttackPokemon，表示小火龙精灵
class Charmander : public AttackPokemon {
public:
    // 构造函数，初始化小火龙的属性
    Charmander(QString name, int lv, int atk, int def, int hp, int speed);

    // 虚析构函数
    virtual ~Charmander() {};

    // 重写attack函数，实现小火龙的攻击逻辑
    int attack(Pokemon*) override;
};

// 派生类：Mankey
// 这个类继承自AttackPokemon，表示猴怪精灵
class Mankey : public AttackPokemon {
public:
    // 构造函数，初始化猴怪的属性
    Mankey(QString name, int lv, int atk, int def, int hp, int speed);

    // 虚析构函数
    virtual ~Mankey() {};

    // 重写attack函数，实现猴怪的攻击逻辑
    int attack(Pokemon*) override;
};

#endif // ATTACKPOKEMON_H

#ifndef DEFENCEPOKEMON_H
#define DEFENCEPOKEMON_H

#include "pokemon.h"

// 派生类：DefencePokemon
// 这个类继承自Pokemon，表示具有防御能力的精灵
class DefencePokemon : public Pokemon {
public:
    // 继承基类Pokemon的构造函数
    using Pokemon::Pokemon;

    // 虚析构函数
    virtual ~DefencePokemon() {};

    // 重写基类的纯虚函数lvUp，实现精灵升级的逻辑
    void lvUp() override;

    // 纯虚函数：精灵攻击另一个精灵，需要在派生类中实现
    virtual int attack(Pokemon*) override = 0;
};

// 派生类：Squirtle
// 这个类继承自DefencePokemon，表示杰尼龟精灵
class Squirtle : public DefencePokemon {
public:
    // 构造函数，初始化杰尼龟的属性
    Squirtle(QString name, int lv, int atk, int def, int hp, int speed);

    // 虚析构函数
    virtual ~Squirtle() {};

    // 重写attack函数，实现杰尼龟的攻击逻辑
    int attack(Pokemon*) override;
};

// 派生类：Machop
// 这个类继承自DefencePokemon，表示腕力精灵
class Machop : public DefencePokemon {
public:
    // 构造函数，初始化腕力的属性
    Machop(QString name, int lv, int atk, int def, int hp, int speed);

    // 虚析构函数
    virtual ~Machop() {};

    // 重写attack函数，实现腕力的攻击逻辑
    int attack(Pokemon*) override;
};

#endif // DEFENCEPOKEMON_H

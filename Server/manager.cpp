#include "manager.h"
#include "attackpokemon.h"
#include "defencepokemon.h"
#include "healthpokemon.h"
#include "speedpokemon.h"

Manager::Manager() : allPokemon({"小火龙", "猴怪", "杰尼龟", "腕力", "妙蛙种子", "飞腿郎", "波波", "皮卡丘"})
{}

Pokemon* Manager::createPokemon(QString name, int lv, int atk, int def, int hp, int speed)
{
    if (name == QString("小火龙") || name == QString("喷火龙")) {
        return new Charmander(name, lv, atk, def, hp, speed);
    } else if (name == QString("猴怪") || name == QString("火暴猴") ) {
        return new Mankey(name, lv, atk, def, hp, speed);
    } else if (name == QString("杰尼龟") || name == QString("水箭龟") ) {
        return new Squirtle(name, lv, atk, def, hp, speed);
    } else if (name == QString("腕力") || name == QString("怪力") ) {
        return new Machop(name, lv, atk, def, hp, speed);
    } else if (name == QString("妙蛙种子") || name == QString("妙蛙花") ) {
        return new Bulbasaur(name, lv, atk, def, hp, speed);
    } else if (name == QString("飞腿郎") || name == QString("快拳郎") ) {
        return new Hitmonlee(name, lv, atk, def, hp, speed);
    } else if (name == QString("波波") || name == QString("大比鸟") ) {
        return new Pidgey(name, lv, atk, def, hp, speed);
    } else if (name == QString("皮卡丘") || name == QString("雷丘") ) {
        return new Pikachu(name, lv, atk, def, hp, speed);
    } else {
        return nullptr;
    }
}

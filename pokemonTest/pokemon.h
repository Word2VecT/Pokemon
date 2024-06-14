#ifndef POKEMON_H
#define POKEMON_H

#include <QString>
#include "config.h"

class Pokemon {
protected:
    int id; //identifier

    QString name;
    bool evolved;

    int lv; //level
    int exp;

    int atk; //attack
    int def; //defence
    int hp; //health
    int speed;

    QString ability;

public:
    Pokemon(QString name = "", int lv = 1, int atk = INIT_ATK, int def = INIT_DEF, int hp = INIT_HP, int speed = INIT_SPEED, QString ability = "");
    virtual ~Pokemon() {};

    QString getName() const;
    int getID() const;
    int getLv() const;
    int getExp() const;
    int getAtk() const;
    int getDef() const;
    int getHp() const;
    int getSpeed() const;
    QString getAbility() const;

    void setLv(int);
    void setExp(int);
    void setAtk(int);
    void setDef(int);
    void setHp(int);
    void setSpeed(int);

    bool isDead() const;

    virtual void lvUp() = 0;
    virtual void attack(Pokemon*) = 0;
};

#endif // POKEMON_H

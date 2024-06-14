#include "pokemon.h"

Pokemon::Pokemon(QString name, int lv, int atk, int def, int hp, int speed, QString ability) : name(name), lv(lv), atk(atk), def(def), hp(hp), speed(speed), ability(ability) {}

QString Pokemon::getName() const {
    return this->name;
}

int Pokemon::getID() const {
    return this->id;
}

int Pokemon::getLv() const {
    return this->lv;
}

int Pokemon::getExp() const {
    return this->exp;
}

int Pokemon::getAtk() const {
    return this->atk;
}

int Pokemon::getDef() const {
    return this->def;
}

int Pokemon::getHp() const {
    return this->hp;
}

int Pokemon::getSpeed() const {
    return this->speed;
}

QString Pokemon::getAbility() const {
    return this->ability;
}

void Pokemon::setLv(int lv) {
    this->lv = lv;
}

void Pokemon::setExp(int exp) {
    this->exp = exp;
}

void Pokemon::setAtk(int atk) {
    this->atk = atk;
}

void Pokemon::setDef(int def) {
    this->def = def;
}

void Pokemon::setHp(int hp) {
    this->hp = hp;
}

void Pokemon::setSpeed(int speed) {
    this->speed = speed;
}

bool Pokemon::isDead() const {
    return hp <= 0;
}

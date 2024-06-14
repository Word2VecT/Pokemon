#include "attackpokemon.h"

void AttackPokemon::lvUp() {
    if (lv == MAX_LV) {
        return;
    }
    lv++;
    atk += INC;
    def += 2 * INC;
    hp += INC;
    speed += INC;
    if (lv == 11) {
        if (name == "小火龙") {
            name = "喷火龙";
        } else if (name == "猴怪") {
            name = "火暴猴";
        }
    }
}

Charmander::Charmander(QString name, int lv, int atk, int def, int hp, int speed) : AttackPokemon(name, lv, atk, def, hp, speed, "火花") {}

int Charmander::attack(Pokemon* enemy) {
    int damage = atk - enemy->getDef();
    QRandomGenerator *generator = QRandomGenerator::global();
    int random = generator->bounded(6);
    if (random <= 2) {
        damage *= random;
    }

    if (getLv() > 10 && generator->bounded(100) < getSpeed()) {
        damage += 0.5 * getDef();
    } //灼烧效果
    enemy->setHp(fmax(enemy->getHp() - damage, 0));

    return random;
}

Mankey::Mankey(QString name, int lv, int atk, int def, int hp, int speed) : AttackPokemon(name, lv, atk, def, hp, speed, "踢倒") {}

int Mankey::attack(Pokemon* enemy) {
    int damage = atk - enemy->getDef();
    QRandomGenerator *generator = QRandomGenerator::global();
    int random = generator->bounded(6);
    if (random <= 2) {
        damage *= random;
    }

    if (getLv() > 10 && generator->bounded(100) < getSpeed()) {
        enemy->setDef(enemy->getDef() - 0.5 * getAtk());
        setAtk(getAtk() + 0.5 * enemy->getDef());
    }//降低敌方防御

    enemy->setHp(fmax(enemy->getHp() - damage, 0));
    return random;
}

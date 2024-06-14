#include "healthpokemon.h"

void HealthPokemon::lvUp() {
    if (lv == MAX_LV) {
        return;
    }
    lv++;
    atk += INC;
    def += INC;
    hp += 2 * INC;
    speed += INC;
    if (lv == 11) {
        if (name == "妙蛙种子") {
            name = "妙蛙花";
        } else if (name == "飞腿郎") {
            name = "快拳郎";
        }
    }
}

Bulbasaur::Bulbasaur(QString name, int lv, int atk, int def, int hp, int speed) : HealthPokemon(name, lv, atk, def, hp, speed, "寄生种子") {}

int Bulbasaur::attack(Pokemon* enemy) {
    int damage = atk + enemy->getDef();
    QRandomGenerator *generator = QRandomGenerator::global();
    int random = generator->bounded(6);
    if (random <= 2) {
        damage *= random;
    }
    if (getLv() > 10 && generator->bounded(100) < getSpeed()) {
        setHp(getHp() + 0.5 * enemy->getHp());
    } // 吸取对方血量
    enemy->setHp(fmax(enemy->getHp() - damage, 0));
    return random;
}

Hitmonlee::Hitmonlee(QString name, int lv, int atk, int def, int hp, int speed) : HealthPokemon(name, lv, atk, def, hp, speed, "挺住") {}

int Hitmonlee::attack(Pokemon* enemy) {
    int damage = atk + enemy->getDef();
    QRandomGenerator *generator = QRandomGenerator::global();
    int random = generator->bounded(6);
    if (random <= 2) {
        damage *= random;
    }
    if (getLv() > 10 && generator->bounded(100) < getSpeed()) {
        setHp(1);
        setAtk(100000);
    } // 舍身秒杀对方
    enemy->setHp(fmax(enemy->getHp() - damage, 0));
    return random;
}

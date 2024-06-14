#include "defencepokemon.h"

void DefencePokemon::lvUp() {
    if (lv == MAX_LV) {
        return;
    }
    lv++;
    atk += INC;
    def += 2 * INC;
    hp += INC;
    speed += INC;
    if (lv == 11) {
        if (name == "杰尼龟") {
            name = "水箭龟";
        } else if (name == "腕力") {
            name = "怪力";
        }
    }
}

Squirtle::Squirtle(QString name, int lv, int atk, int def, int hp, int speed) : DefencePokemon(name, lv, atk, def, hp, speed, "缩入壳中") {}

int Squirtle::attack(Pokemon* enemy) {
    int damage = atk + enemy->getDef();
    QRandomGenerator *generator = QRandomGenerator::global();
    int random = generator->bounded(6);
    if (random <= 2) {
        damage *= random;
    }
    if (getLv() > 10 && generator->bounded(100) < getSpeed()) {
        setDef(1.5 * getDef());
    } //增加防御
    enemy->setHp(fmax(enemy->getHp() - damage, 0));
    return random;
}

Machop::Machop(QString name, int lv, int atk, int def, int hp, int speed) : DefencePokemon(name, lv, atk, def, hp, speed, "健美") {}

int Machop::attack(Pokemon* enemy) {
    int damage = atk + enemy->getDef();
    QRandomGenerator *generator = QRandomGenerator::global();
    int random = generator->bounded(6);
    if (random <= 2) {
        damage *= random;
    }
    if (getLv() > 10 && generator->bounded(100) < getSpeed()) {
        setAtk(getAtk() + 0.5 * getDef());
    } //根据防御增加攻击
    enemy->setHp(fmax(enemy->getHp() - damage, 0));
    return random;
}

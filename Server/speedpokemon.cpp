#include "speedpokemon.h"

void SpeedPokemon::lvUp() {
    if (lv == MAX_LV) {
        return;
    }
    lv++;
    atk += 2 * INC;
    def += INC;
    hp += INC;
    speed += INC;
    if (lv == 11) {
        if (name == "皮卡丘") {
            name = "雷丘";
        } else if (name == "波波") {
            name = "大比鸟";
        }
    }
}

Pidgey::Pidgey(QString name, int lv, int atk, int def, int hp, int speed) : SpeedPokemon(name, lv, atk, def, hp, speed, "电光一闪") {}

int Pidgey::attack(Pokemon* enemy) {
    int damage = atk + enemy->getDef();
    QRandomGenerator *generator = QRandomGenerator::global();
    int random = generator->bounded(6);
    if (random <= 2) {
        damage *= random;
    }
    if (getLv() > 10 && generator->bounded(100) < getSpeed()) {
        setSpeed(1.5 * getSpeed());
    } // 增加速度
    enemy->setHp(fmax(enemy->getHp() - damage, 0));
    return random;
}

Pikachu::Pikachu(QString name, int lv, int atk, int def, int hp, int speed) : SpeedPokemon(name, lv, atk, def, hp, speed, "电球") {}

int Pikachu::attack(Pokemon* enemy) {
    int damage = atk + enemy->getDef();
    QRandomGenerator *generator = QRandomGenerator::global();
    int random = generator->bounded(6);
    if (random <= 2) {
        damage *= random;
    }
    if (getLv() > 10 && generator->bounded(100) < getSpeed()) {
        damage += 0.5 * getSpeed();
    } // 根据速度造成伤害
    enemy->setHp(fmax(enemy->getHp() - damage, 0));
    return random;
}

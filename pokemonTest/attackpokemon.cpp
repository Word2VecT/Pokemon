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
}

Charmander::Charmander(QString name, int lv, int atk, int def, int hp, int speed) : AttackPokemon(name, lv, atk, def, hp, speed, "火花") {}

void Charmander::attack(Pokemon* enemy) {
    enemy->setHp(fmax(enemy->getHp() - atk + enemy->getDef(), 0));
}

Mankey::Mankey(QString name, int lv, int atk, int def, int hp, int speed) : AttackPokemon(name, lv, atk, def, hp, speed, "踢倒") {}

void Mankey::attack(Pokemon* enemy) {
    enemy->setHp(fmax(enemy->getHp() - atk + enemy->getDef(), 0));
}

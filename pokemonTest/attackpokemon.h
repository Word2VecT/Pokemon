#ifndef ATTACKPOKEMON_H
#define ATTACKPOKEMON_H

#include "pokemon.h"

class AttackPokemon : public Pokemon {
public:
    using Pokemon::Pokemon;
    virtual ~AttackPokemon() {};

    void lvUp() override;
    virtual void attack(Pokemon*) override = 0;
};

class Charmander : public AttackPokemon {
public:
    Charmander(QString name, int lv, int atk, int def, int hp, int speed);
    virtual ~Charmander() {};

    void attack(Pokemon*) override;
};

class Mankey : public AttackPokemon {
public:
    Mankey(QString name, int lv, int atk, int def, int hp, int speed);
    virtual ~Mankey() {};

    void attack(Pokemon*) override;
};

#endif // ATTACKPOKEMON_H

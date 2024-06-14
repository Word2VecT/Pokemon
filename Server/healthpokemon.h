#ifndef HEALTHPOKEMON_H
#define HEALTHPOKEMON_H

#include "pokemon.h"

class HealthPokemon : public Pokemon {
public:
    using Pokemon::Pokemon;
    virtual ~HealthPokemon() {};

    void lvUp() override;
    virtual int attack(Pokemon*) override = 0;
};

class Bulbasaur : public HealthPokemon {
public:
    Bulbasaur(QString name, int lv, int atk, int def, int hp, int speed);
    virtual ~Bulbasaur() {};

    int attack(Pokemon*) override;
};

class Hitmonlee : public HealthPokemon {
public:
    Hitmonlee(QString name, int lv, int atk, int def, int hp, int speed);
    virtual ~Hitmonlee() {};

    int attack(Pokemon*) override;
};

#endif // HEALTHPOKEMON_H

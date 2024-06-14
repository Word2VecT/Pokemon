#ifndef SPEEDPOKEMON_H
#define SPEEDPOKEMON_H

#include "pokemon.h"

class SpeedPokemon : public Pokemon {
public:
    using Pokemon::Pokemon;
    virtual ~SpeedPokemon() {};

    void lvUp() override;
    virtual int attack(Pokemon*) override = 0;
};

class Pidgey : public SpeedPokemon {
public:
    Pidgey(QString name, int lv, int atk, int def, int hp, int speed);
    virtual ~Pidgey() {};

    int attack(Pokemon*) override;
};

class Pikachu : public SpeedPokemon {
public:
    Pikachu(QString name, int lv, int atk, int def, int hp, int speed);
    virtual ~Pikachu() {};

    int attack(Pokemon*) override;
};

#endif // SPEEDPOKEMON_H

#ifndef MANAGER_H
#define MANAGER_H

#include "pokemon.h"
#include <QVector>
#include <QString>

class Manager
{
public:
    Manager();
    QVector<QString> allPokemon;
    Pokemon *createPokemon(QString name, int lv, int atk, int def, int hp, int speed);
};

#endif // MANAGER_H

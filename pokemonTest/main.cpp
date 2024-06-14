#include <QCoreApplication>
#include "pokemon.h"
#include "attackpokemon.h"
#include <iostream>

void printPokemonStats(const Pokemon& pokemon) {
    std::cout << "Name: " << pokemon.getName().toStdString() << std::endl;
    std::cout << "Level: " << pokemon.getLv() << std::endl;
    std::cout << "Attack: " << pokemon.getAtk() << std::endl;
    std::cout << "Defense: " << pokemon.getDef() << std::endl;
    std::cout << "HP: " << pokemon.getHp() << std::endl;
    std::cout << "Speed: " << pokemon.getSpeed() << std::endl;
    std::cout << "Ability: " << pokemon.getAbility().toStdString() << std::endl;
    std::cout << "Is Dead: " << (pokemon.isDead() ? "Yes" : "No") << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create some Pokemon instances
    Charmander charmander("Charmander", 5, 52, 43, 39, 65);
    Mankey mankey("Mankey", 5, 80, 35, 40, 70);

    // Print initial stats
    std::cout << "Initial Stats of Charmander:" << std::endl;
    printPokemonStats(charmander);

    std::cout << "\nInitial Stats of Mankey:" << std::endl;
    printPokemonStats(mankey);

    // Attack each other
    std::cout << "\nCharmander attacks Mankey!" << std::endl;
    charmander.attack(&mankey);
    printPokemonStats(mankey);

    std::cout << "\nMankey attacks Charmander!" << std::endl;
    mankey.attack(&charmander);
    printPokemonStats(charmander);

    // Level up Charmander
    std::cout << "\nCharmander levels up!" << std::endl;
    charmander.lvUp();
    printPokemonStats(charmander);

    // Level up Mankey
    std::cout << "\nMankey levels up!" << std::endl;
    mankey.lvUp();
    printPokemonStats(mankey);

    return 0;

    return a.exec();
}

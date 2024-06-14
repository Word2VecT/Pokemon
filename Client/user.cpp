#include "user.h"

User::User() {
    pokemonImg["妙蛙种子"] = QString(":/pokemon/elements/Bulbasaur.png");
    pokemonImg["妙蛙花"] = QString(":/pokemon/elements/Venusaur.png");
    pokemonImg["小火龙"] = QString(":/pokemon/elements/Charmander.png");
    pokemonImg["喷火龙"] = QString(":/pokemon/elements/Charizard.png");
    pokemonImg["杰尼龟"] = QString(":/pokemon/elements/Squirtle.png");
    pokemonImg["水箭龟"] = QString(":/pokemon/elements/Blastoise.png");
    pokemonImg["波波"] = QString(":/pokemon/elements/Pidgey.png");
    pokemonImg["大比鸟"] = QString(":/pokemon/elements/Pidgeot.png");
    pokemonImg["皮卡丘"] = QString(":/pokemon/elements/Pikachu.png");
    pokemonImg["雷丘"] = QString(":/pokemon/elements/Raichu.png");
    pokemonImg["猴怪"] = QString(":/pokemon/elements/Mankey.png");
    pokemonImg["火暴猴"] = QString(":/pokemon/elements/Primeape.png");
    pokemonImg["腕力"] = QString(":/pokemon/elements/Machop.png");
    pokemonImg["怪力"] = QString(":/pokemon/elements/Machamp.png");
    pokemonImg["飞腿郎"] = QString(":/pokemon/elements/Hitmonlee.png");
    pokemonImg["快拳郎"] = QString(":/pokemon/elements/Hitmonchan.png");
}

void User::showMsgBox(QString text, QString title)
{
    msgBox->setText(text);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setDefaultButton(QMessageBox::Ok);
    msgBox->setInformativeText(title);
    if (title == QString("成功")) {
        msgBox->setIcon(QMessageBox::Information);
    } else {
        msgBox->setIcon(QMessageBox::Critical);
    }
    msgBox->exec();
}

#ifndef BATTLE_H
#define BATTLE_H

#include "bag.h"
#include "stadium.h"
#include <QDialog>

namespace Ui {
class Battle;
}

class Battle : public QDialog
{
    Q_OBJECT

public:
    explicit Battle(QWidget *parent = nullptr);
    ~Battle();
    void connectServer();

private:
    Ui::Battle *ui;
    Bag *bag;
    Stadium *stadium;
};

#endif // BATTLE_H

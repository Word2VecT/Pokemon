#ifndef HOME_H
#define HOME_H

#include "bag.h"
#include "rank.h"
#include "battle.h"
#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();
    void checkPokemonAndUserInfo();

private:
    Ui::Home *ui;
    Bag *bag;
    Rank *rank;
    Battle *battle;

private slots:
    void connectServer();
};

#endif // HOME_H

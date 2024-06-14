#ifndef BAG_H
#define BAG_H

#include "pokemoninfo.h"
#include <QDialog>
#include <QTcpSocket>
#include <QListWidget>

namespace Ui {
class Bag;
}

class Bag : public QDialog
{
    Q_OBJECT

public:
    explicit Bag(int queryUserID, int type, QWidget *parent = nullptr);
    ~Bag();
    void getUserPokemonList(QJsonObject json);
    void getSystemPokemonList(QJsonObject json);
    void get3UserPokemonList(QJsonObject json);

private:
    Ui::Bag *ui;
    pokemonInfo *info;
    QListWidget *list;
    int queryUserID;
    int type;

private slots:
    void connectServer();
};

#endif // BAG_H

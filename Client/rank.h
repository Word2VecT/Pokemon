#ifndef RANK_H
#define RANK_H

#include "bag.h"
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>

namespace Ui {
class Rank;
}

class Rank : public QWidget
{
    Q_OBJECT

public:
    explicit Rank(QWidget *parent = nullptr);
    ~Rank();
    void connectServer();

private:
    Ui::Rank *ui;
    QStandardItemModel *model;
    Bag *bag;

private slots:
    void showUserPokemons(const QModelIndex &index);
};

#endif // RANK_H

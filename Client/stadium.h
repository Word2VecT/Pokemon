#ifndef STADIUM_H
#define STADIUM_H

#include "result.h"
#include "bag.h"
#include <QWidget>
#include <QJsonObject>
#include <QTimer>

namespace Ui {
class Stadium;
}

class Stadium : public QWidget
{
    Q_OBJECT

public:
    explicit Stadium(QJsonObject json, QWidget *parent = nullptr);
    ~Stadium();

private:
    Ui::Stadium *ui;
    QJsonObject json;
    QTimer *timer;
    int turnNum;
    bool firstEnemy;
    Result *result;
    Bag *bag;
};

#endif // STADIUM_H

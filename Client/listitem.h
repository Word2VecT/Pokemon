#ifndef LISTITEM_H
#define LISTITEM_H

#include <QWidget>
#include <QString>

namespace Ui {
class ListItem;
}

class ListItem : public QWidget
{
    Q_OBJECT

public:
    Ui::ListItem *ui;
    explicit ListItem(QString name, int pokemonID, int LV, QWidget *parent = nullptr);
    ~ListItem();

private:
    QString name;
    int pokemonID;
    int LV;
};

#endif // LISTITEM_H

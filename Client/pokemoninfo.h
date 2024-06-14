#ifndef POKEMONINFO_H
#define POKEMONINFO_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class pokemonInfo;
}

class pokemonInfo : public QWidget
{
    Q_OBJECT

public:
    explicit pokemonInfo(int pokemonID, QWidget *parent = nullptr);
    ~pokemonInfo();
    void connectServer();

private:
    Ui::pokemonInfo *ui;
    int pokemonID;
};

#endif // POKEMONINFO_H

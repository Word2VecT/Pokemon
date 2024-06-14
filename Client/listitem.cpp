#include "listitem.h"
#include "ui_listitem.h"
#include "user.h"
#include <QVBoxLayout>

extern User user;

ListItem::ListItem(QString name, int pokemonID, int LV, QWidget *parent)
    : QWidget(parent), ui(new Ui::ListItem), name(name), pokemonID(pokemonID), LV(LV)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);

    qDebug() << "listItem 构建 " << name << " " << pokemonID << Qt::endl;

    ui->img->setStyleSheet(QString("image: url(%1);background: transparent;border: none;").arg(user.pokemonImg[name]));
    ui->ID->setText(QString("ID: ") + QString::number(pokemonID));
    ui->LV->setText(QString("LV: ") + QString::number(LV));
    ui->name->setText(name);
}

ListItem::~ListItem()
{
    delete ui;
}



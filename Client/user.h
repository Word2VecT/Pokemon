#ifndef USER_H
#define USER_H

#include <QString>
#include <QTcpSocket>
#include <QMap>
#include <QVector>
#include <QMessageBox>
#include <QTcpSocket>

class User
{
public:
    QMessageBox *msgBox;
    QString name;
    int id;
    int socketID;
    int enemyID;
    int pokemonID;
    QMap<QString, QString> pokemonImg;
    QMap<QString, QString> pokemonAbility;
    QMap<QString, QString> pokemonAbilityExplain;
    QTcpSocket *tcpSocket;

    User();
    void showMsgBox(QString title, QString text);
};

#endif // USER_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QTcpServer>
#include <QList>
#include <QTcpSocket>
#include <QSqlDatabase>

extern QSqlDatabase db;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void login(QJsonObject);
    void regist(QJsonObject);
    void checkPokemonAndUserInfo(QJsonObject);
    void getPokeminInfo(QJsonObject);
    void sendAllScokets(QJsonObject);
    void getAllPokemon(QJsonObject);
    void getOnlineUser(QJsonObject);
    void getSystemPokemon(QJsonObject);
    void battle(QJsonObject);
    void get3Pokemon(QJsonObject);
    void abandonOnePokemon(QJsonObject);
    void logout(QJsonObject);

private:
    Ui::MainWindow *ui;

    QTcpServer *tcpServer;
    QList<QTcpSocket *> socketList;
    int socketID;

private slots:
    void whenNewConnection();
};
#endif // MAINWINDOW_H

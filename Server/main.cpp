#include "mainwindow.h"
#include <manager.h>
#include <QApplication>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>

QSqlDatabase db;

Manager manager;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "开始创建数据库连接" << Qt::endl;
    db = QSqlDatabase::addDatabase("QMYSQL", "pokemon_connection");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("pokemon");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        qDebug() << "连接数据库失败" << db.lastError().text() << Qt::endl;
    } else {
        qDebug() << "连接数据库成功" << Qt::endl;
    }

    MainWindow w;
    w.show();
    return a.exec();
}

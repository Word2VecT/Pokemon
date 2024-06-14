#include "mainwindow.h"
#include "user.h"
#include <QApplication>
#include <QtGui>

User user;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    user.msgBox = new QMessageBox;
    user.msgBox->setStyleSheet("QMessageBox { background: transparent; }"
                          "QPushButton {"
                          "  background-color: rgb(200, 200, 200);"
                          "  border: 1px solid rgb(0, 0, 0);"
                          "  padding: 5px;"
                          "}");
    QString ip = "127.0.0.1";
    qint16 port = 8888;
    user.tcpSocket = new QTcpSocket();
    user.tcpSocket->connectToHost(QHostAddress(ip), port);
    MainWindow w;
    w.show();

    return a.exec();
}

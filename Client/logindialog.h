#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "home.h"
#include <QTcpSocket>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    Home *home;

private slots:
    void login();
    void regist();
    void connectServer();
};

#endif // LOGINDIALOG_H

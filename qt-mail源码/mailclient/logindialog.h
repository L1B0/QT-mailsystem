#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "findpassworddialog.h"
using namespace std;

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();
    
private slots:
    void on_pb_login_clicked();

    void on_log_register_clicked();

    void on_pb_cancel_clicked();

    void on_passwd_find_clicked();

private:
    Ui::loginDialog *ui;
    registerDialog *reg;
    FindPasswordDialog *findPasswordDialog;
    int fd;
};

#endif // LOGINDIALOG_H

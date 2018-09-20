#include <QApplication>
#include <QDialog>
#include "logindialog.h"
#include "registerdialog.h"
#include <QMessageBox>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginDialog log;
    log.show();
    return a.exec();
}

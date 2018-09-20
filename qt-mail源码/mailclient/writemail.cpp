#include "writemail.h"
#include "ui_writemail.h"
#include"firststack.h"
#include"mainwindow.h"
#include "protocol.h"
#include <QMessageBox>
#include <iostream>
using namespace std;

writemail::writemail(QString username, int fd, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::writemail)
{
    ui->setupUi(this);
    ui->SENDB->setFocusPolicy(Qt::NoFocus);
    ui->SAVEB->setFocusPolicy(Qt::NoFocus);
    ui->CLOSEB->setFocusPolicy(Qt::NoFocus);
    this->username = username;
    this->fd = fd;
}

writemail::~writemail()
{
    delete ui;
}

void writemail::on_CLOSEB_clicked()
{
    this->close();
}

void writemail::on_SENDB_clicked()
{
    mail_package ch;
    strcpy(ch.recver, ui->textEdit->toPlainText().toStdString().c_str());
    strcpy(ch.title, ui->textEdit_2->toPlainText().toStdString().c_str());
    strcpy(ch.sender, this->username.toStdString().c_str());
    strcpy(ch.time, QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss").toStdString().c_str());
    ch.contextLen = strlen(ui->textEdit_3->toPlainText().toStdString().c_str());
    qDebug() << ch.title << ch.time << ch.sender << ch.recver << ch.contextLen ;

    QString text_1 = ui->textEdit_3->toPlainText();
    char text[2000];
    QByteArray dome = text_1.toLocal8Bit();
    strcpy(text, dome.data());

    qDebug() << text;
    char cmd = 0x02;
    write(fd, &cmd, sizeof(cmd));
    write(fd, &ch, sizeof(ch));
    write(fd, text, sizeof(text));

    response_header rh;
    int count = read(fd, &rh, sizeof(rh));
    check_count(count);

    if(rh.statu == 0x03){
        //发送成功
        QMessageBox msgBox;
        msgBox.setText("发送成功！！！");
        msgBox.exec();
        ui->textEdit->clear();
        ui->textEdit_2->clear();
        ui->textEdit_3->clear();
    }
    else{
        //发送失败
        char buf[200] = {0};
        count = read(fd, buf, rh.length);
        check_count(count);
        QMessageBox msgBox;
        msgBox.setText(buf);
        msgBox.exec();
    }
    return ;
}

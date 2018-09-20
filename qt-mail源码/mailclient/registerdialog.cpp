#include <QMessageBox>
#include <QDebug>
#include "protocol.h"
#include "registerdialog.h"
#include "ui_registerdialog.h"

bool registerDialog::isDigitString(const QString& src) {
    const char *s = src.toUtf8().data();
    while(*s && *s>='0' && *s<='9')s++;
    return !bool(*s);
}

registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
}

registerDialog::~registerDialog()
{
    delete ui;
}


void registerDialog::on_reg_clicked()
{
    //get_register_info
    if( ui->username->text() == "" || ui->passwd->text() == ""
            || ui->passwd_2->text() == "" || ui->number->text() == "" ){
        QMessageBox box;
        box.setText("请完善个人信息！！！");
        box.exec();
        return ;
    }
    if(ui->passwd->text() != ui->passwd_2->text()){
        QMessageBox box;
        box.setText("两次输入密码不一致！！！");
        box.exec();
        ui->passwd->clear();
        ui->passwd_2->clear();
        return ;
    }
    qDebug() << strlen(ui->number->text().toStdString().c_str())
             << !isDigitString(ui->number->text().toStdString().c_str());
    if(strlen(ui->number->text().toStdString().c_str()) != 11){
        QMessageBox box;
        box.setText("电话号码格式错误!!!");
        box.exec();
        ui->number->clear();
        return ;
    }
    if(!isDigitString(ui->number->text().toStdString().c_str())){
        QMessageBox box;
        box.setText("电话号码格式错误!!!");
        box.exec();
        ui->number->clear();
        return ;
    }
    //填充注册请求协议头
    register_info ch;
    strcpy( ch.username,ui->username->text().toStdString().c_str() );
    strcpy(ch.passwd,ui->passwd->text().toStdString().c_str());
    strcpy(ch.number,ui->number->text().toStdString().c_str());
    qDebug() << ch.username << ch.passwd << ch.number;
    //向服务器发送注册请求协议头
    char cmd=0x0B;
    write(fd,&cmd,sizeof(cmd));
    write(fd,&ch,sizeof(ch));

    //接受服务器的响应协议头
    response_header rh;
    int count = read(fd,&rh,sizeof(rh));
    check_count(count);
    qDebug() << rh.length << rh.statu;

    if(rh.statu == 0x01)
    {
        //注册成功
        QMessageBox msgBox;
        msgBox.setText("注册成功!!!");
        msgBox.exec();
        accept();
    }
    else
    {
        char buf[200] = {0};
        count = read(fd,buf,rh.length);
        QMessageBox msgBox;
        msgBox.setText(buf);
        msgBox.exec();
        return ;
    }
}

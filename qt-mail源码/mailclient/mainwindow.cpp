#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QStackedWidget>
#include"draft.h"
#include"writemail.h"
#include"recyclebin.h"
#include"sendmail.h"
#include"receive.h"
#include"firststack.h"
MainWindow::MainWindow(QString username, int fd, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("你的邮箱");
    ui->sendmail->setFocusPolicy(Qt::NoFocus);
    ui->recyclebin->setFocusPolicy(Qt::NoFocus);
    ui->receive->setFocusPolicy(Qt::NoFocus);
    ui->writemail->setFocusPolicy(Qt::NoFocus);
    ui->draft->setFocusPolicy(Qt::NoFocus);
    ui->logout->setFocusPolicy(Qt::NoFocus);
    this->username = username;
    this->fd = fd;

    stack = new QStackedWidget(this);
    firststack *fststack=new firststack();
    sendmail *smail=new sendmail();
    recyclebin *rbin=new recyclebin();
    receive *rve=new receive();
    writemail *wte=new writemail(username, fd);
    draft *dft=new draft();



    stack->addWidget(fststack);
    stack->addWidget(wte);
    stack->addWidget(rve);
    stack->addWidget(smail);
    stack->addWidget(dft);
    stack->addWidget(rbin);
    stack->move(241,61);
    stack->resize(790,510);


}

void MainWindow::get_unread_num()
{
    //未读邮件数
    char cmd = 0x09;
    client_header ch;
    ch.cmdType = cmd;
    strcpy(ch.username,username.toLatin1().data());
    ch.length = 0;
    //write
    write(fd,&cmd,sizeof(cmd));
    write(fd,&ch,sizeof(ch));

    //read
    response_header tmp;
    read(fd,&tmp,sizeof(tmp));

    qDebug()<<tmp.length<<endl;
    QMessageBox msgBox;
    msgBox.setText(tr("您有%1封未读邮件").arg(tmp.length));
    msgBox.exec();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_label_4_linkActivated(QString link)
{

}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_writemail_clicked()
{
    stack->setCurrentIndex(1);
}
void MainWindow::on_receive_clicked()
{
    stack->setCurrentIndex(2);
    //get_mail
    char cmd = 0x01;
    client_header ch;
    ch.cmdType = 0x01;
    strcpy(ch.username,username.toLatin1().data());
    ch.username[strlen(ch.username)] = '\0';
    ch.length = 0;
    qDebug()<< ch.username;
    //write
    write(fd,&cmd,sizeof(cmd));
    write(fd,&ch,sizeof(ch));

    //read
    mail_package mp;
    read(fd,&mp,sizeof(mp));
    while(mp.flag == true)
    {
        char text[2000];
        read(fd, text, sizeof(text));
        qDebug() << text;
        qDebug() << mp.recver << mp.sender << mp.time << "true";
        receive *rve = new receive(mp.sender, mp.title, mp.time, text);
        rve->show();
        read(fd,&mp,sizeof(mp));
    }
}

void MainWindow::on_sendmail_clicked()
{
    stack->setCurrentIndex(3);
    //get_mail
    char cmd = 0x06;
    client_header ch;
    ch.cmdType = 0x06;
    strcpy(ch.username,username.toLatin1().data());
    ch.username[strlen(ch.username)] = '\0';
    ch.length = 0;
    qDebug()<< ch.username;
    //write
    write(fd,&cmd,sizeof(cmd));
    write(fd,&ch,sizeof(ch));

    //read
    mail_package mp;
    read(fd,&mp,sizeof(mp));
    while(mp.flag == true)
    {
        char text[2000];
        read(fd, text, sizeof(text));
        qDebug() << mp.recver << mp.sender << mp.time;
        sendmail *smail = new sendmail(mp.recver, mp.title, mp.time, text);
        smail->show();
        read(fd,&mp,sizeof(mp));
    }
    return ;
}


void MainWindow::on_draft_clicked()
{
    stack->setCurrentIndex(4);
}

void MainWindow::on_recyclebin_clicked()
{
    stack->setCurrentIndex(5);
}

void MainWindow::on_logout_clicked()
{
    exit(0);
}

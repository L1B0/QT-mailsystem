#include "sendmail.h"
#include "ui_sendmail.h"

sendmail::sendmail(const char *recver, const char *title, const char *time, const char *text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendmail)
{
    ui->setupUi(this);
    this->recver= recver;
    this->title= title;
    this->time= time;
    this->text = text;
    qDebug() << recver << title << time << "this";
    ui->inbox->setItem(0, 1,new QTableWidgetItem(recver));
    ui->inbox->setItem(0, 2,new QTableWidgetItem(title));
    ui->inbox->setItem(0, 3,new QTableWidgetItem(time));
    ui->textEdit->setText(text);
}

sendmail::sendmail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendmail)
{
    ui->setupUi(this);
}

sendmail::~sendmail()
{
    delete ui;
}

#include "receive.h"
#include "ui_receive.h"

receive::receive(const char *sender, const char * title, const char *time, const char *text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::receive)
{
    ui->setupUi(this);
    this->sender= sender;
    this->title= title;
    this->time= time;
    this->text = text;
    qDebug() << sender << title << time << "this";
    ui->inbox->setItem(0, 1,new QTableWidgetItem(sender));
    ui->inbox->setItem(0, 2,new QTableWidgetItem(title));
    ui->inbox->setItem(0, 3,new QTableWidgetItem(time));
    ui->textEdit->setText(text);
}

receive::receive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::receive)
{
    ui->setupUi(this);
}

receive::~receive()
{
    delete ui;
}

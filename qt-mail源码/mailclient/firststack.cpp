#include "firststack.h"
#include "ui_firststack.h"

firststack::firststack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::firststack)
{
    ui->setupUi(this);
}

firststack::~firststack()
{
    delete ui;
}

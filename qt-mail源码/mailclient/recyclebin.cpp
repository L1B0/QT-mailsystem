#include "recyclebin.h"
#include "ui_recyclebin.h"

recyclebin::recyclebin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recyclebin)
{
    ui->setupUi(this);
}

recyclebin::~recyclebin()
{
    delete ui;
}

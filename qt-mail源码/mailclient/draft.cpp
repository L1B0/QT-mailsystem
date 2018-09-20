#include "draft.h"
#include "ui_draft.h"

draft::draft(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draft)
{
    ui->setupUi(this);
}

draft::~draft()
{
    delete ui;
}

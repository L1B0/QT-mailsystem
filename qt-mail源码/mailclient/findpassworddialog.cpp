#include "findpassworddialog.h"
#include "ui_findpassworddialog.h"
#include "protocol.h"
#include "registerdialog.h"
#include <QMessageBox>

FindPasswordDialog::FindPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPasswordDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("找回密码");
}

FindPasswordDialog::~FindPasswordDialog()
{
    delete ui;
}

void FindPasswordDialog::on_cancelbtn_clicked()
{
    this->close();
}

void FindPasswordDialog::on_okbtn_clicked()
{
    if(ui->phonenumStr->text() == "") {
        QMessageBox box;
        box.setText("未输入电话！！！");
        box.exec();
        return ;
    }
    if(strlen(ui->phonenumStr->text().toStdString().c_str()) != 11){
        QMessageBox box;
        box.setText("电话号码格式错误!!!");
        box.exec();
        ui->phonenumStr->clear();
        return ;
    }
    if(!registerDialog::isDigitString(ui->phonenumStr->text().toStdString().c_str())){
        QMessageBox box;
        box.setText("电话号码格式错误!!!");
        box.exec();
        ui->phonenumStr->clear();
        return ;
    }
    findpasswd_info fi;
    strcpy(fi.number, ui->phonenumStr->text().toStdString().c_str());
    fi.number[11] = '\0';
    cout<<"phonenumber: "<<fi.number<<endl;

    char cmd = 0x0C;
    write(fd, &cmd, sizeof(cmd));
    cout<<"sizeof fi: "<<sizeof(fi)<<endl;
    int cnt = write(fd, &fi, sizeof(fi));
    cout<<"send :"<<cnt<<endl;

    response_header rh;
    int count = read(fd, &rh, sizeof(rh));
    check_count(count);

    if(rh.statu == 0x01) {
        QMessageBox msgBox;
        char buf[12] = {0};
        read(fd, buf, rh.length);
        cout<<buf<<endl;
        msgBox.setText(buf);
        msgBox.exec();
        this->close();
    } else {
        char buf[200] = {0};
        count = read(fd,buf,rh.length);
        QMessageBox msgBox;
        msgBox.setText(buf);
        msgBox.exec();
    }
    return;
}

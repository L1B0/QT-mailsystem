#include <QMessageBox>
#include "mainwindow.h"
#include "protocol.h"
#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
    ui->username->setFocus();
    //连接服务器
    //1. 创建套接子
    fd = socket(PF_INET,SOCK_STREAM,0);

    if(fd < 0)
    {
        perror("socket failed");
        exit(-1);
    }
    //2. 填充服务器地址
    struct sockaddr_in serverIP;
    serverIP.sin_family = AF_INET;
    short port = ui->port->text().toShort();
    serverIP.sin_port = htons(port);
    //绑定本机地址，有系统选择具体的IP地址
    const char *ip = ui->ipaddress->text().toLatin1().data();
    cout<<"server IP: "<<ip<<endl;
    cout<<"server Port: "<<port<<endl;
    serverIP.sin_addr.s_addr = inet_addr(ip);
    if(::connect(fd,(sockaddr *)&serverIP,sizeof(serverIP)) < 0)
    {
        perror("connect to server failed!");
        exit(-1);
    }
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pb_login_clicked()
{

    //实现登录请求
    if(ui->username->text() == "" || ui->passwd->text() == "")
        return;
	//填充登录请求协议头
    login_info ch;
    strcpy(ch.username,ui->username->text().toStdString().c_str());
	cout<<"username: "<<ch.username<<endl;
    strcpy(ch.passwd,ui->passwd->text().toStdString().c_str());
    cout<<"password: "<<ch.passwd<<endl;

	//向服务器发送登录请求协议头
    char cmd=0x00;
    write(fd,&cmd,sizeof(cmd));
	write(fd,&ch,sizeof(ch));
	
	response_header rh;
	//接收服务器的响应协议头
	int count  = read(fd,&rh,sizeof(rh));
    check_count(count);

	if(rh.statu == 0x01)
	{
		//登录成功
		//显示主界面
        QMessageBox msgBox;
        msgBox.setText("登陆成功!!!");
        msgBox.exec();
        MainWindow *mw = new MainWindow(ui->username->text(), fd);
        mw->get_unread_num();
        mw->show();
        this->close();
	}
	else
	{
        char buf[200] = {0};
		count = read(fd,buf,rh.length);
        QMessageBox msgBox;
        msgBox.setText(buf);
        msgBox.exec();
        ui->passwd->clear();
	}
	return;
}

void loginDialog::on_log_register_clicked()
{
    reg = new registerDialog(this);
    reg->fd = fd;
    if(reg->exec() == QDialog::Accepted){
        return ;
    }
}

void loginDialog::on_pb_cancel_clicked()
{
    exit(-1);
}

void loginDialog::on_passwd_find_clicked()
{
    cout<<"find password fd: "<<fd<<endl;
    findPasswordDialog = new FindPasswordDialog(this);
    findPasswordDialog->fd = fd;
    findPasswordDialog->exec();
}

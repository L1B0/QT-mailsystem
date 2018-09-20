#include "protocol.h"
#include "server.h"

QSqlDatabase connect_mysql(const char*username,const char *passwd,const char *database,const char*mysqlip)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(mysqlip);
    db.setDatabaseName(database);//已建立的数据库名称
    db.setUserName(username);//用户名称
    db.setPassword(passwd);//密码
    bool ok = db.open();//如果成功ok位true，否则为false
    if(!ok)
    {
		cout<<"connect mysql failed...."<<db.lastError().text().toStdString();
        exit(-1);
    }
    else
        cout<<"connect mysql....ok!\n";
    return db;
}
int create_server(short port)
{
    //1. 创建套接子
    int sockfd = socket(PF_INET,SOCK_STREAM,0);

    if(sockfd < 0)
	{
        perror("socket failed");
		exit(-1);
	}
    //2. 填充服务器地址
    struct sockaddr_in serverIP;
    serverIP.sin_family = AF_INET;
    serverIP.sin_port = htons(port);
    //绑定本机地址，有系统选择具体的IP地址
    //inet_aton
    //inet_ntoa
    serverIP.sin_addr.s_addr = inet_addr("0.0.0.0");
    //将地址绑定至该套接子
    if(bind(sockfd,(struct sockaddr *)&serverIP,sizeof(serverIP)) < 0)
	{
        perror("bind failed");
		exit(-1);
	}
    //3. 监听，将套接子由主动连接变为被动连接状态
    if(listen(sockfd,10) < 0)
	{
        perror("listen failed");
		exit(-1);
	}
    return sockfd;
}
void do_client(int fd,QSqlDatabase &db)
{

	while(1)
	{
        char cmd;
        int count = read(fd,&cmd,sizeof(cmd));
        check_count(count);
        switch(cmd)
		{
			case 0x00:{
                login_info ch;
                //等待客户端发送请求
                int count = read(fd,&ch,sizeof(ch));
                check_count(count);

				//执行sql实现登录功能
                bool ok = do_login(ch.username,ch.passwd,db);

                response_header tmp;
				if(ok)
				{
					//登录成功
                    cout<<ch.username<<" online!!\n";
					tmp.statu = 0x01; 
					tmp.length = 0; 
					//发送响应协议头
					write(fd,&tmp,sizeof(tmp));
				}
				else
				{
					//登录失败
                    cout<<ch.username<<"login failed!!\n";
					tmp.statu = 0x00; 
                    const char *errorinfo = "用户名或密码错误!!!";
					tmp.length = strlen(errorinfo); 
                    //发送响应协议头
					if(write(fd,&tmp,sizeof(tmp)) < 0)
					{
						perror("write failed!!");
						exit(-1);
					}
					//发送失败的原因
					write(fd,errorinfo,tmp.length);
				}
				break;
            }
            case 0x01:{
                client_header ch;
                int count = read(fd,&ch,sizeof(ch));
                check_count(count);
                qDebug()<<ch.username;
                do_box_mail(ch.username,db,fd,1);
                break;
            }
            case 0x02:{
                mail_package mp;
                char text[2000];
                int count = read(fd, &mp, sizeof(mp));
                check_count(count);
                int count_text = read(fd, text, sizeof(text));
                check_count(count_text);
                qDebug() << "text:" << text;
                bool ok = do_send(mp.sender, mp.recver, mp.time, mp.title, text, db);
                response_header tmp;
                if(ok){
                    //发送成功
                    tmp.statu = 0x03;
                    tmp.length = 0;
                    write(fd, &tmp, sizeof(tmp));
                }
                else{
                    //发送失败
                    tmp.statu = 0x00;
                    const char *errorinfo = "发送失败！！！";
                    tmp.length = strlen(errorinfo);
                    if(write(fd, &tmp, sizeof(tmp)) < 0){
                        perror("write failed!!");
                        exit(-1);
                    }
                    write(fd, errorinfo, tmp.length);
                }
                break;
            }
            case 0x06:{
                client_header ch;
                int count = read(fd,&ch,sizeof(ch));
                check_count(count);
                qDebug()<<ch.username;
                do_box_mail(ch.username,db,fd,6);
                break;
            }
            case 0x09:{

                client_header ch;
                int count = read(fd,&ch,sizeof(ch));
                check_count(count);
                qDebug() << "unread username" << ch.username;

                int ok = do_get_unread_num(ch.username,db);
                response_header tmp;

                qDebug() << "ok " << ok;
                qDebug() << "get unread num for " << ch.username << "successfully!!";
                tmp.statu = 0x02;
                tmp.length = ok;
                qDebug() << "num " << tmp.length;
                //发送响应协议头
                write(fd,&tmp,sizeof(tmp));


                break;
            }
			case 0x0B:{
                register_info reg;
				//register
                int count = read(fd,&reg,sizeof(reg));
                check_count(count);
                //qDebug() << reg.username << reg.passwd << reg.number;
                //实现注册功能
                bool ok = do_register(reg.username,reg.passwd,reg.number,db);
                //qDebug() << ok;
				response_header tmp;
				if(ok)
				{
					//注册成功
                    cout<<reg.username<<" register successfully!!\n";
					tmp.statu = 0x01; 
					tmp.length = 0; 
					//发送响应协议头
					write(fd,&tmp,sizeof(tmp));
				}
				else
				{
                    //注册失败
					tmp.statu = 0x00; 
                    const char *errorinfo = "注册失败!!!";
					tmp.length = strlen(errorinfo); 
					//发送响应协议头
					if(write(fd,&tmp,sizeof(tmp)) < 0)
					{
						perror("write failed!!");
						exit(-1);
					}
					//发送失败的原因
					write(fd,errorinfo,tmp.length);
				}
				break;
			}
            case 0x0C:{
                findpasswd_info fi;
                cout<<"sizeof fi: "<<sizeof(fi)<<endl;
                int count = read(fd, &fi, sizeof(fi));
                cout<<"read bytes: "<<count<<endl;
                cout<<"read number: "<<fi.number<<endl;

                check_count(count);
                response_header tmp;
                bool ok;
                QString passwd = do_find(fi.number, db, ok);
                if(ok == false)
                {
                    cout<<"find failed!!\n";
                    tmp.statu = 0x00;
                    const char *errorinfo = "find error!!";
                    tmp.length = strlen(errorinfo);
                    //发送响应协议头
                    if(write(fd,&tmp,sizeof(tmp)) < 0)
                    {
                        perror("write failed!!");
                        exit(-1);
                    }
                    //发送失败的原因
                    write(fd,errorinfo,tmp.length);
                }
                else
                {
                    cout<<"find successfully!!"<<"result: "<<passwd.toLatin1().data()<<endl;
                    tmp.statu = 0x01;
                    tmp.length = passwd.length();
                    if(write(fd,&tmp,sizeof(tmp)) < 0)
                    {
                        perror("write failed!!");
                        exit(-1);
                    }
                    write(fd, passwd.toLatin1().data(), tmp.length);
                }
                break;
            }
        }

	}
	return;
}
bool do_login(const char *username,const char *passwd,QSqlDatabase &db)
{
	QSqlQuery query(db);
    QString sql =QString("select * from user where username='%1' and password = '%2'").arg(username,passwd);
	query.exec(sql);
    if(query.size() == 0)
        return false;
    else
        return true;
}
bool do_register(const char *username,const char *passwd,const char *phone,QSqlDatabase &db)
{
	QSqlQuery query(db);
    bool ok;
    QString sql =QString("select * from user where phone = '%1'").arg(phone);
    query.exec(sql);
    if(query.next())
        return false;
    else{
        sql =QString("insert into user(username,password,phone) "
                             "values('%1','%2','%3')").arg(username,passwd,phone);
        bool ok = query.exec(sql);
        return ok;
    }

}

int do_get_unread_num(const char *username,QSqlDatabase &db)
{
    QSqlQuery query(db);
    QString sql =QString("select * from email_inbox where user_username='%1' and mail_status='%2'").arg(username,0);
    query.exec(sql);
    int unread_num = query.size();
    qDebug() << "unread_num: " << unread_num;
    return unread_num;
}
QString do_find(const char *phonenum, QSqlDatabase &db, bool &ok) {
    QSqlQuery query(db);
    QString ret;
    QString sql = QString("select password from user where phone='%1'").arg(phonenum);
    qDebug()<<sql;
    query.exec(sql);
    if(query.size() <= 0)
    {
        ok = false;
        cout<<"not find password"<<endl;
        return ret;
    }
    ok = true;
    query.seek(0);
    if(query.first()) {
        cout<<"finding password..."<<endl;
        ret = query.value(0).toString();
    }
    qDebug()<<"find password: "<<ret;

    return ret;
}

bool do_send(const char *sender, const char *recver, const char *time,
             const char *title, const char *text, QSqlDatabase &db){
    QSqlQuery query(db);
    qDebug() << sender << recver;
    QString sql_1 = QString("insert into email_outbox(user_username, mail_name ,mail_receiptUser, mail_byTime, "
                           "mail_content, mail_status) "
                           "values('%1', '%2', '%3', '%4', '%5', 0)").arg(sender, title, recver, time, text);
    QString sql_2 = QString("insert into email_inbox(user_username, mail_name ,mail_byUser, mail_byTime, "
                          "mail_content, mail_status) "
                          "values('%1', '%2', '%3', '%4', '%5', 0)").arg(recver, title, sender, time, text);

    bool ok_2 = query.exec(sql_2);
    if(ok_2 == false)
        return ok_2;
    bool ok_1 = query.exec(sql_1);
    qDebug() << sql_1;
    qDebug() << sql_2;
    return ok_1;
}
void do_box_mail(const char *username, QSqlDatabase &db,int fd,int flag)
{
    QSqlQuery query(db);
    QString sql;
    if(flag == 1)
        sql = QString("select * from email_inbox where user_username='%1'").arg(username);
    else
        sql = QString("select * from email_outbox where user_username='%1'").arg(username);
    query.exec(sql);
    bool ok = query.next();
    qDebug() << ok ;
    if(!ok)
    {
        mail_package mp;
        mp.flag = false;
        write(fd,&mp,sizeof(mp));
        return ;
    }
    while(1)
    {
        mail_package mp;
        char content[2000];
        mp.flag = true;

        strcpy(mp.title,query.value(2).toString().toLatin1().data());
        if(flag == 1)
        {
            strcpy(mp.sender,query.value(3).toString().toLatin1().data());
            strcpy(mp.recver,query.value(1).toString().toLatin1().data());
        }
        else
        {
            strcpy(mp.sender,query.value(1).toString().toLatin1().data());
            strcpy(mp.recver,query.value(3).toString().toLatin1().data());
        }
        strcpy(mp.time,query.value(4).toString().toLatin1().data());
        mp.contextLen = strlen(query.value(5).toString().toLatin1().data());
        strcpy(content,query.value(5).toString().toLocal8Bit().data());

        write(fd,&mp,sizeof(mp));
        write(fd, content, sizeof(content));
        if(!query.next())
            break;
    }
    mail_package mp;
    mp.flag = false;
    write(fd,&mp,sizeof(mp));
    return ;
}

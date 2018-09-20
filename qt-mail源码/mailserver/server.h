#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
using namespace std;
QSqlDatabase connect_mysql(const char*username,const char *passwd,const char *database,const char* mysqlip);
int create_server(short port);
void do_client(int fd,QSqlDatabase &db);
bool do_login(const char *username,const char *passwd,QSqlDatabase &db);
bool do_register(const char *username,const char *passwd,const char *number,QSqlDatabase &db);
QString do_find(const char *phonenum, QSqlDatabase &db,bool &ok);
bool do_send(const char *sender, const char *recver, const char *time, const char *title, const char *text, QSqlDatabase &db);
int do_get_unread_num(const char *username,QSqlDatabase &db);
void do_box_mail(const char *phonenum, QSqlDatabase &db,int fd,int flag);
#endif // SERVER_H

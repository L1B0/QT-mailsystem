# QT-mailsystem使用说明

## 0x00 创建数据库

在文件`emailDatabase.sql`所在目录下打开命令行，进入mysql

```mysql
create database email_schema;
use email_schema;
source emailDatabase.sql;
```

## 0x01 编译

```
//编译mailclient
cd mailclient
qmake -project
qmake
make
vim mailclient.pro //若报fatal error: QWidget: 没有那个文件或目录
QT+=sql core gui widgets //添加这行
make

//编译mailserver
cd mailserver
qmake -project
qmake
make
vim mailserver.pro //atal error: QSqlDatabase: 没有那个文件或目录
QT+=sql //添加这行
make
```

## 0x02 运行

### mailserver

```
./mailserver [port]
```

### mailclient

```
//修改mailclient的port
vim logindialog.ui
//将第29行的4444改成你想用的port

make //重新make
./mailclient
```

## 0x03 系统功能

该邮件系统目前实现了登录，注册，找回密码，写邮件，收件箱和发件箱。


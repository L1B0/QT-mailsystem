#include <QCoreApplication>
#include<QtSql/QSqlDatabase>
#include "server.h"

int main(int argc, char *argv[])
{
    if( argc != 2 )
    {
        cout<<"input port!!"<<endl;
        return -1;
    }
    //1. connect to mysql
    QSqlDatabase db = connect_mysql("root","666666","email_schema","0.0.0.0");


    //2. create socket
    int sockfd = create_server(atoi(argv[1]));
    //3. wait client connection

    struct sockaddr_in clientInfo;
    socklen_t len = sizeof(clientInfo);

    while(1)
    {
		cout<<"wait for client connection...\n";
    	int clientfd = accept(sockfd,(struct sockaddr *)&clientInfo,&len);
		cout<<"new client connection has coming....\n";
		pid_t pid = fork();
		if(pid < 0)
		{
			perror("fork failed!!");
			exit(-1);
		}
		if(pid == 0)
		{
			close(sockfd);
			//handle client
            do_client(clientfd,db);
			return 0;
		}
		close(clientfd);
    }

    return 0;
}

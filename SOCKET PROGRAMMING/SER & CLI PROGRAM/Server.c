/*TCP server*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<strings.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	int sockfd,newsfd;
	struct sockaddr_in srv,cln;
	char rdbuf[128];

	/**********SOCKET FUNCTION**********/
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket created successfully!\n");
	srv.sin_family         =AF_INET;
	srv.sin_port           =htons(atoi(argv[1]));
	srv.sin_addr.s_addr    =inet_addr("0.0.0.0");
	
	/**********BIND FUNCTION**********/
	if(bind(sockfd,(struct sockaddr *)&srv,sizeof(srv))==0)
		printf("bind successfull!\n");
	else
	{
		perror("bind");
		return 0;
	}

	/**********LISTEN FUNCTION**********/
	listen(sockfd,1);
	int len=sizeof(cln);
	
	printf("waiting for connection!\n");

	/**********ACCEPT FUNCTION**********/
	newsfd=accept(sockfd,(struct sockaddr *)&cln,&len);
	if(newsfd<0)
	{
		perror("accept");
		return 0;
	}
	printf("connection accepted!\n");

	/**********READ FUNCTION**********/
	while(1)
	{	
	bzero(rdbuf,128);
	if(read(newsfd,rdbuf,128)==0)
	{
		printf("client%d terminated!\n",newsfd-sockfd);
		exit(0);
	}
	printf("received string is :%s\n",rdbuf);
	}
	
	
}

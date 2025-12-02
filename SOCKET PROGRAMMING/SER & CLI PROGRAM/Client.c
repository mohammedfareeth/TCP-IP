/*TCP client*/
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int sfd;
	struct sockaddr_in cln;
	char wrbuf[128];

	/**********SOCKET FUNCTION**********/
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket created successfully!!!!!!!!!!!!!!!!....\n");
	cln.sin_family         =AF_INET;
	cln.sin_port           =htons(atoi(argv[1]));
	cln.sin_addr.s_addr    =inet_addr("127.0.0.1");

	/**********CONNECT FUNCTION**********/
	if(connect(sfd,(struct sockaddr *)&cln,sizeof(cln))==0)
		printf("connect successfull!!!!!!!!!!!!!!!!\n");
	else
	{
		perror("connect");
		return 0;
	}

	/**********WRITE FUNCTION**********/
	while(1)
	{	
	printf("enter the data:");
	//scanf("%s",wrbuf);
	gets(wrbuf);
	write(sfd,wrbuf,strlen(wrbuf)+1);
	}
}

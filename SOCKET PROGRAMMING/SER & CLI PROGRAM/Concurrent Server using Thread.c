/* concurrent server using threads */
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<strings.h>
#include<unistd.h>
#include<stdlib.h>

/**********READ FUNCTION**********/
void sock_thread(int *d)
{
  char wbuf[128],rbuf[128];
  int nsfd= (int*)*d;
  while(1)
  {
  bzero(rbuf,128);
  read(nsfd,rbuf,128);
  printf("received data is =%s\n",rbuf);
  } 
}

/************************************/
int main(int argc,char **argv)
{
  int sfd,nsfd;
  pthread_t t1;
  struct sockaddr_in srv,cln;

  /**********SOCKET FUNCTION**********/
  sfd=socket(AF_INET,SOCK_STREAM,0);
  if(sfd<0)
  {
    perror("socket");
    return 0;
  } 
  printf("socket creadted successfully!\n");
  
  srv.sin_family      = AF_INET;
  srv.sin_port        = htons(atoi(argv[1]));
  srv.sin_addr.s_addr = inet_addr("0.0.0.0");

  /**********BIND FUNCTION**********/
  if(bind(sfd,(struct sockaddr*)&srv,sizeof(srv))==0)
    printf("binding address successfully!\n");
  else
    {
      perror("bind");
      return 0;
    }
  
  /**********LISTEN FUNCTION**********/
  listen(sfd,1);
  int len = sizeof(cln);
  printf("waiting for incoming connection request...\n");

  /**********ACCEPT FUNCTION**********/
  while(1)
  {
    nsfd=accept(sfd,(struct sockaddr *)&cln,&len);
    if(nsfd<0)
     {
       perror("accept");
       return 0;
     }
   printf("connection accepted!\n");

   /**********THREAD FUNCTION**********/
   pthread_create(&t1,0,sock_thread,&nsfd);
  
  }
}

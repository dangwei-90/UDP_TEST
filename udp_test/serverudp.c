/**********************************************************************
udp_test
**********************************************************************/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


#define SERVER_PORT     8888
#define MSG_MAX_LENGTH  255
int sockfd;

struct sockaddr_in client;
int client_len = sizeof(struct sockaddr_in); 
unsigned char message[MSG_MAX_LENGTH];
int recv_len = 0;
char addr_p[INET_ADDRSTRLEN];
char *sndbuf = "server: reserved.\n";


int main(int argc, char *argv[])
{
  struct sockaddr_in server;
  bzero(&server,sizeof(server));
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=htonl(INADDR_ANY);
  server.sin_port=htons(SERVER_PORT);
   
  if(-1 == (sockfd=socket(AF_INET, SOCK_DGRAM,0))) {
    perror("create socket failed");
    exit(1);
  }
  
  if(-1 == (bind(sockfd, (struct sockaddr*)&server, sizeof(server)))) {
    perror("bind error");
    exit(1);
  }

  // while(1) {
  recv_len=recvfrom(sockfd,message,sizeof(message),0,(struct sockaddr *)&client,&client_len);
  if(recv_len < 0)
  {
    printf("recvfrom error\n");
    exit(1);
  }
  
  inet_ntop(AF_INET,&client.sin_addr,addr_p,sizeof(addr_p));
  printf("client IP is %s, port is %d\n",addr_p,ntohs(client.sin_port));

  message[recv_len]='\0';
  printf("server received %d:%s\n", recv_len, message);

  if(sendto(sockfd, sndbuf, strlen(sndbuf), 0,(struct sockaddr*)&client, client_len) < 0) {
    printf("sendto error\n");
    exit(1);
  }
  // }
  
  return 0;
}

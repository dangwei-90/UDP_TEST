/**********************************************************************
upd_test
**********************************************************************/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


#define UDP_TEST_PORT       8888
#define UDP_TEST_SERVER_IP  "127.0.0.1"
#define MESSAGE_MAX_LENGTH  255

int main(int argC, char* arg[]) {
  struct sockaddr_in server;
  int sockfd, len = 0;   
  int server_len = sizeof(struct sockaddr_in);        
  char *sendStr ="client send message\n";
  char buf[MESSAGE_MAX_LENGTH];
  
  // use SOCK_DGRAM
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }

  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(UDP_TEST_PORT);
  server.sin_addr.s_addr = inet_addr(UDP_TEST_SERVER_IP);

  // while(1) {
  //printf("Please enter a string to send to server: \n");
  //len = read(STDIN_FILENO, buf, sizeof(buf));

  // send data to server
  if(sendto(sockfd, sendStr,  strlen(sendStr), 0, (struct sockaddr *)&server, server_len) < 0) {
    printf("sendto error\n");
    exit(1);
  }

  memset(buf, 0, sizeof(buf));

  // recieve the string from server
  len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&server, &server_len);
  if(len < 0) {
    printf("recvfrom error\n");
    exit(1);
  }

  printf("Receive from server: %s\n", buf);
  //}

  return 0;
}

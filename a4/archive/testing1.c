#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#define PORT 8080 
int main(int argc,char *argv)
{
  int Server_Socket, newSocket;
  char response_buffer[500];
  char request_buffer[1000];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  if(!(Server_Socket = socket(PF_INET, SOCK_STREAM, 0))<0)
  {
      printf("Socket Error:\n");
  }
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  bind(Server_Socket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if(listen(Server_Socket,5)==0)
  {
      printf("Listening\n");
  }
  else
  {
      printf("Error\n");
  }
   addr_size = sizeof serverStorage;
  newSocket = accept(Server_Socket, (struct sockaddr *) &serverStorage, &addr_size);
  strcpy(response_buffer,"\nHello  Welcome Please wait!:\n");
  recv(newSocket, request_buffer, sizeof(request_buffer), 0);
  printf("\nReceived Request from the Client is %s\n",request_buffer);
  send(newSocket,response_buffer,sizeof(response_buffer),0);
  printf("\nResponse Sent to the client Successfully:\n");
  return 0;
}



#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
int main(int argc,char *argv[])
{
  int clientSocket;
  char *IpAddress;
  int  Portno;
  char response_buffer[100];
  char request_message[]="Hi please Accept";
  char buf[100];
  time_t curtime;
  struct tm *loc_time;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  if(argc<2)
  {
      printf("\nPlease Pass IP address and Port Number as a Parameter");
      exit(0);
  }
  IpAddress=argv[1]; //Assigning first Arguement as a  IPaddress.
  printf("\nThe Ip address is %s\n",IpAddress);
  Portno=atoi(argv[2]); //Assigning Second Arguement as a Port Number.
  printf("\nThe Port Number is %d\n",Portno);
    //create The Socket Connection
  if(!(clientSocket = socket(PF_INET, SOCK_STREAM, 1)))
  {
     printf("Failed to create a Socket:\n");
  }
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(Portno);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  addr_size = sizeof serverAddr;
  //Connecting with IPaddress
  if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size)<0)
  {
   printf("Connect Error:\n");
   exit(0);
  }
  curtime = time (NULL);
  loc_time = localtime (&curtime);
  strftime (buf, 140, "Time is %I:%M %p.\n", loc_time);
  fputs (buf, stdout);
   //Send Request to The Server
  send(clientSocket,request_message,sizeof(request_message),0);
  printf("Request Successfully sent to the server:\n");
  //Receive Response from the Server
  recv(clientSocket, response_buffer, sizeof(response_buffer), 0);
  printf("Received Response from the Server is: %s\n",response_buffer);
  return 0;
 }


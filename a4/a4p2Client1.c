#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 10000 /*max text line length*/
#define SERV_PORT 10010 /*port*/
int
main(int argc, char **argv)
{
int sockfd;
struct sockaddr_in servaddr;
char sendline[MAXLINE], recvline[MAXLINE], dateline[MAXLINE];
alarm(300); // to terminate after 300 seconds

if (argc !=4) {
perror("Usage: TCPClient ");
exit(1);
}

//Create a socket for the client
//If sockfd<0 there was an error in the creation of the socket
if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
perror("Problem in creating the socket");
exit(2);
}

//Creation of the socket
memset(&servaddr, 0, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr= inet_addr(argv[1]);
servaddr.sin_port = htons(atoi(argv[2]));

//Connection of the client to the socket
if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
perror("Problem in connecting to the server");
exit(3);
}

while (fgets(sendline, MAXLINE, stdin) != NULL) {

send(sockfd, sendline, strlen(sendline), 0);

//write to file
FILE *fp;
fp = fopen(argv[3], "ab+");
fputs(sendline, fp);

FILE *in;
in=popen("hostname", "r"); 
fgets(dateline, MAXLINE, in);
fputs(dateline,fp);
in=popen("date", "r"); 
fgets(dateline, MAXLINE, in);
fputs(dateline,fp);


system("hostname; date");
//system("hostname>>text.txt; date >> text.txt");
int check = 0;
   
  if (recv(sockfd, recvline, MAXLINE,0) == 0){
     check = 1;
     fclose(fp);
     perror("Exit Command:");
     exit(4);
  }else{
  printf("%s \n", "String received from the server: ");
  fputs(recvline, stdout);
  fputs(recvline,fp);
  }
  }
exit(0);
}
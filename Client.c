#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int socket_fd;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  struct { char head; char body[100]; char tail; } msgbuf;

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  bzero((char *) &dest, sizeof(dest)); /* They say you must do this */
  hostptr = gethostbyname("localhost");
  dest.sin_family = (short) AF_INET;
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  dest.sin_port = htons((u_short)0x3333);
  for(;;){
  printf("enter your message\n");
    scanf("%s",msgbuf.body);
  msgbuf.head = '<';
  //msgbuf.body = htonl(getpid()); /* IMPORTANT! */
  msgbuf.tail = '>';
if (strcasecmp(msgbuf.body,"exit")==0)
break;
sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,
sizeof(dest));

int    fsize = sizeof(dest);
int cc = recvfrom(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,&fsize);
    if(cc!=-1)
    printf("the message we got: %c%s%c\n",msgbuf.head,msgbuf.body,msgbuf.tail);
    //fflush(stdout);
    }
  return 0;
}

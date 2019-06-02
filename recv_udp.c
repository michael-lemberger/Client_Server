#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


void printsin(struct sockaddr_in *s, char *pname, char *msg) {
  printf("%s\n", pname);
  printf("%s: ip= %s, port= %d ", msg,inet_ntoa(s->sin_addr),s->sin_port);
  //-- port: sin->sin_port (host integer type)
  //-- IP: sin->sin_addr (IP in dotted-decimal notation)
  printf("\n");
}


int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from;
  struct { char head; char body[100]; char tail;} msg;

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */

  s_in.sin_family = (short)AF_INET;
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
  s_in.sin_port = htons((u_short)0x3333);

  printsin( &s_in, "RECV_UDP", "Local socket is:");
  fflush(stdout);

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));
  for(;;) {
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
    printsin( &from, "recv_udp: ", "Packet from:");
    printf("Got data ::%c%s%c\n",msg.head,msg.body,msg.tail);
    fflush(stdout);


      //sending message
  printf("send your message here: \n");
  scanf("%s",msg.body);
  sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,
sizeof(from));
  }



  return 0;
}

#include <sys/types.h>
#include<ctype.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#define X 0.5

void printsin(struct sockaddr_in *s, char *pname, char *msg) {
  printf("%s\n", pname);
  printf("%s: ip= %s, port= %d ", msg,inet_ntoa(s->sin_addr),s->sin_port);
  //-- port: sin->sin_port (host integer type)
  //-- IP: sin->sin_addr (IP in dotted-decimal notation)
  printf("\n");
}

double RandomX(char *x){
double ans;
sscanf(x,"%lf",&ans);
printf("\n ans=%f\n",ans);
if(ans<1&&ans>0)
return ans;
return -1.1;
}

int isnumber(char *x){
int res;
int len= strlen(x);
for(int i=0; i<len;i++)
 res=isdigit(x[i]);
 if(res!=0)
 return res;
return 0;
}


int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from;
  struct { char head; char body[100]; char tail;} msg;

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */
  printf("\nargc= %d\n",argc);
   if(argc>1){
    RandomX(argv[1]);
}
  s_in.sin_family = (short)AF_INET;
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
  s_in.sin_port = htons((u_short)0x3333);

  printsin( &s_in, "RECV_UDP", "Local socket is:");
  fflush(stdout);
    /*for sending messages from a to c*/
   int i=0;
    struct sockaddr_in sFrom[2];
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

  for(;;) {
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
    printsin( &from, "recv_udp: ", "Packet from:");
    printf("Got data ::%c%s%c\n",msg.head,msg.body,msg.tail);
    fflush(stdout);
    if (i==0){
    sFrom[0]=from;
    i++;
    }
    if (i!=0&&sFrom[0].sin_port!=from.sin_port){
    sFrom[1]=from;
    }


      //sending message
      /*if it is Node A*/
     if (sFrom[0].sin_port==from.sin_port){
double randomly= rand()%10000/10000.0;//random number between 0-1
    // printf("the random number is %f\nif random >0.5 then the will send\n",randomly);
    double ans;
    if(argc>1)
    if(isnumber(argv[1])>0){
    ans = RandomX(argv[1]);
    if(ans==-1.1)
    ans=X;
    }
    else
    ans=X;
     if(randomly<ans)

     /*reset the messge of A*/
     memset((void*)&msg.body,0,sizeof(msg.body));
  sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&sFrom[1],
sizeof(from));

}
else
sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&sFrom[0],
sizeof(from));
  }



  return 0;
}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#define SIM_LENGTH 10
#define PORT 1337

void clean_up(int cond, int *sock)
{ printf("Exiting now.\n");
  close(*sock); //close a socket file descriptor
  exit(cond);
}

int main(void)
{
  int sock;
  int connect_sock;
  struct sockaddr_in serv_name;
  socklen_t len;
  int count;

  sock = socket(AF_INET, SOCK_STREAM, 0);  //create a socket
  if (sock < 0)//disconnected
    { perror ("Error opening channel");
      clean_up(1, &sock);
    }

  memset((char *)&serv_name,0, sizeof(serv_name)); //reset the values of the string into 0
  serv_name.sin_family = AF_INET;  //ipv4
  serv_name.sin_port = htons(PORT); ////host to network  short (big endian or little endian)

  if (bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name)) < 0) //try to connect
    { perror ("Error naming channel");//if their isn't connection
      clean_up(1, &sock);
    }

  printf("Server is alive and waiting for socket connection from client.\n");
  listen(sock, 1);

  len = sizeof(serv_name);
/*return a socket descriptor about the new socket,
and inform the strct sockaddr about the new connection (ip,port)*/
  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len);

  for (count = 1; count <= SIM_LENGTH; count++)
    {
	  write(connect_sock, &count, 4);//write to buffer
      printf("Server has written %d to socket.\n", count);
    }

  close(connect_sock);
  clean_up(0, &sock);

}

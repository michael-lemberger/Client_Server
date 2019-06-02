#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#define SIM_LENGTH 10
//#define IP_ADDRESS "127.0.1.1" 
#define PORT 1337

int main(int argc, char* argv[])
{
// if their is connection
  int sock;
//AF_INET,port number,internet address..
  struct sockaddr_in cli_name;
  int count;
  int value;
struct addrinfo* res;
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
printf("\nyou have %d in argc\n",argc);
printf("the values are %s\n",argv[0]);
  if (argc != 2) {//the number of args we have 
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }

  hostname = argv[1];//we need to enter the hostname in the command line

  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
	/*extruct the ip address from the hostname*/
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }

  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);

  printf("Address for %s is %s\n", hostname, hostaddr);

  printf("\nClient is alive and establishing socket connection.\n");


  sock = socket(AF_INET, SOCK_STREAM, 0);//creates connection
  if (sock < 0)//no connection
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }


  bzero(&cli_name, sizeof(cli_name)); //reset he buffer
  cli_name.sin_family = AF_INET; //ipv4
/*convert the string pointed  to an integer value suitable for use as an Internet address.*/
  cli_name.sin_addr.s_addr = inet_addr(hostaddr);
  cli_name.sin_port = htons(PORT);//host to network  short (big endian or little endian)


  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)//connect to the socket
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }


  for (count = 1; count <= SIM_LENGTH; count++)
    { read(sock, &value, 4);//read data into a buffer
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");

  close(sock);
  exit(0);

}

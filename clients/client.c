#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include "service/functions.c"
#include "service/communication.c"
#include "client.h"

int main(int argc, char **argv)
{
	int sock;
	struct sockaddr_in servaddr;

	if (argc !=2) {
		perror("Usage: ip address of the server");
		exit(1);
	}

	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) <0) {
		perror("Problem in creating the socket.");
		exit(2);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr= inet_addr(argv[1]);
	servaddr.sin_port =  htons(SERV_PORT);

	if (connect(sock, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
		perror("Problem in connecting to the server");
		exit(3);
	}
	else
	printf("\nConnected to server.\n");
	comm_service(sock);

	return 0;
}
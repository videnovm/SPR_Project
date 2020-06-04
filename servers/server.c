#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>//sockaddr_in
#include <string.h>
#include <unistd.h>
#include <dirent.h> 
#include <pthread.h>
#include <fcntl.h>
#include <linux/limits.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections*/
#define LIST_FUNC "LIST"
#define BUFSIZE 6

#include "communication/tcp_implementation.c"
#include "communication/functions.c"
#include "server.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

char buf[MAXLINE];
int n;

int main (int argc, char **argv)
{
    int base_sd;
    base_sd=connectToServer(3000);

    //accepting the maximum queud connections
    pthread_t t[10];
    struct sockaddr_in c_add;
    socklen_t addrlen;
    addrlen = sizeof(c_add);
    int i;
    for (i=0 ;i<10 ;i++ )
    {
        printf("\n\nthread id=t[%d]\n\n\n\n\n",i);
        printf ("%s","Thread created for client.");
        pthread_create(&t[i],0,body,(void *)base_sd);
        pause();
    }//end of infinite for loop
	comm_service(base_sd);
}
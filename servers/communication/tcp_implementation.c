#define BUFSIZE 6

int  n;
void* body(int *arg)
{
	struct sockaddr_in c_add;
	int addrlen;
	int i,l;
	int base_sd = (int) arg;
	int client;
	pid_t childpid;
	char buffer[1024];
	while (1) {
		//pthread_mutex_lock(&lock);
		client = accept(base_sd, &c_add, &addrlen);

		//pthread_mutex_unlock(&lock);
		printf("\n\nRequest recieved: sd=%d\n\n",client);
		comm_service(client);
		
		close(client);
	}
}

//creating socket and listening
int connectToServer(int port)
{
	int base_sd2;
	struct sockaddr_in c_add, servaddr;

	if ((base_sd2 = socket (AF_INET, SOCK_STREAM, 0)) <0) {
	perror("Problem in creating the socket");
	exit(2);
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	bind (base_sd2, (struct sockaddr *) &servaddr, sizeof(servaddr));

	//listen to the socket by creating a connection queue, then wait for clients
	if((listen(base_sd2, LISTENQ)) != 0) {
        perror("");
        return -4;
    }

	printf("%s\n","Server running...waiting for connections.");

	return base_sd2;
}


void comm_service(int client_connection_fd){
	char buffer[30];
	int option;
    printf("Enter option");
	while(1) {
        read(client_connection_fd, &option, sizeof(int));		//read(client_connection_fd, &option, sizeof(int));
		switch(option)
		{
		case 1: comm_service1(client_connection_fd); break;
		default: printf("Option does not exist\n"); break;
		}

		if( option == 10) {
			printf("Server exit");
			break;
		}
	}
}
void comm_service1(int sd2)
{
	char buf_recv[1000],buf_send[1000];
	char * filename;
	int n;
	FILE *fp;
	printf("\n\nRequesting client to send file name:\n\n");
	n=recv(sd2,buf_recv,1000,0);
	buf_recv[n]='\0';
	printf("%s\n",buf_recv);
	fflush(stdout);
	filename = buf_recv;
	printf("Checking FILE:%s exists or not...\n",buf_recv);
	fp = fopen(buf_recv,"r");
	
	printf("\n\nReceiving command option:\n\n");
	n=recv(sd2,buf_recv,1000,0);
	buf_recv[n]='\0';
	printf("%s\n",buf_recv);
	fflush(stdout);

	if(strcmp(buf_recv,"LIST")==0)
	{
		//sprintf(buf_send,"File could not be found!!!");
		list(sd2);
		exit(0);
	}
	else if(strcmp(buf_recv,"READ")==0)
	{
		//sprintf(buf_send,"File could not be found!!!");
		do_service1(sd2, filename);
  	}
	else if(strcmp(buf_recv,"LINES")==0)
	{
		//sprintf(buf_send,"File could not be found!!!");
		countLines(sd2, filename);
  	}
	
	printf("[Server] Connection with Client closed. Server will wait now...\n");
}
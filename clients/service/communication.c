void comm_service(int socket_fd){
	int n;
	int option;
	char optionString[20];
	while(1) {
		printMenu();
		fgets(optionString, sizeof(optionString), stdin);
		option = atoi(optionString);
		write(socket_fd, &option, sizeof(int));
		switch (option) {
		case 1: comm_service1(socket_fd); break;
		default: printf("Option does not exist"); break;
		}
		if( option == 10) {
			printf("Client exit");
			close(socket_fd);
			break;
		}
	}
}

void comm_service1(int sd){
    int n;
    char buf_recv[1000];
    char buf_send[1000];
    char *filename;
    char *file_buffer[300000];
    char f_buffer = MAXBUF;
    int len, expect, received;
    long s = MAXBUF;
    char buff[MAXBUF];       
    int pos1,pos2;

    FILE *fp;
    printf("\n\nNow sending the file name: \n\n");
    scanf("%s",buf_send);
    filename = buf_send;
    send(sd,buf_send,strlen(buf_send),0);

    printf("\n\nEnter option [READ, LIST, LINES]: \n\n");
    scanf("%s",buf_send);
    send(sd,buf_send,strlen(buf_send),0);

    if(strcmp(buf_send,"READ")==0)
    {
        //sprintf(buf_send,"File could not be found!!!");
        service_handle1(sd, filename);
        exit(0);
    }
    else if(strcmp(buf_send,"LIST")==0)
    {
        //sprintf(buf_send,"File could not be found!!!");
        list(sd);
    }
    else if(strcmp(buf_send,"LINES")==0)
    {
        //sprintf(buf_send,"File could not be found!!!");
        countLines(sd);
    }
    close(sd);
}
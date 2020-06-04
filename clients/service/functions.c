void printMenu(){
	printf("\n");
	printf("Welcome!\n");
	printf("1. USE BOOK;\n");
	printf("\n");
}
int service_handle1(int sd, char *filename){

	int n;
	char buf_recv[1000];
	char buf_send[1000];
	FILE *fp;
	char *file_buffer[300000];
	char f_buffer = MAXBUF;
	int len, expect, received;
	long s = MAXBUF;
	char buff[MAXBUF];       
	int pos1,pos2;

	printf("\n\nNow enter the first line position: \n\n");
	scanf("%d",pos1);
	write(sd, &pos1, sizeof(int));

    printf("\n\nNow enter the second line position: \n\n");
	scanf("%d",pos2);
	write(sd, &pos2, sizeof(int));
	
	n=recv(sd, file_buffer, sizeof(file_buffer), 0);
	printf(file_buffer);
	//file_buffer[n]='\0';
	fflush(stdout);

	fp = fopen("received_file.txt","w");
	fputs(file_buffer,fp);
	fclose(fp);
	close(sd);
	exit(0);
}


int countLines(int sd){
	char buf_recv[1000],buf_send[1000];

	int file_linescount;
	read(sd, &file_linescount, sizeof(file_linescount));
	printf("\nSize in number of lines of the selected book: %d\n\n", file_linescount);
	memset(&file_linescount, 0, sizeof(file_linescount));

	close(sd);
	exit(0);
}


int list(int sd) {
	char returnData[1] = ""; 
	printf("List of all available books:\n");
	while(1){
		read(sd, &returnData, sizeof(returnData));
		printf("%s", returnData);
	}
	comm_service(sd);
}
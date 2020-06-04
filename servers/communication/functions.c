void do_service1(int sd2, char *filename)
{
	int n;
	FILE *fp;
	char * buffer;
	size_t result;
	int len, pos1,pos2;
	
	fp = fopen(filename,"r");
	printf("\n\nReceiving the first line position:\n\n");
	read(sd2, &pos1, sizeof(int));

	printf("\n\nReceiving the second line position:\n\n");
	read(sd2, &pos2, sizeof(int));
	
	fseek (fp , 0, SEEK_SET);
    len = ftell (fp);

	len = len - pos2;
    fseek (fp, len, SEEK_SET);
    //rewind (fp);
	buffer = (char*) malloc (sizeof(char)*len);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	// copy the file into the buffer:
	result = fread (buffer,1,len,fp);
	if (result != len) {fputs ("Reading error",stderr); exit (3);}

	printf("buffer size: %d", buffer);
    fclose(fp);

    printf("Sending the file content to client....\n");
	write(sd2, buffer, strlen(buffer));
	printf("sent");
	close(sd2);
	exit(0);
}

int list(int sd) {
  DIR *p;
  struct dirent *pp;    
  char returnData[PATH_MAX] = ""; 
  p = opendir ("./");

  if (p != NULL)
  {
    while ((pp = readdir (p))!=NULL) {
      int length = strlen(pp->d_name);
        if (strncmp(pp->d_name + length - 4, ".txt", 4) == 0) {
            getname(pp->d_name);
            strcpy (returnData, pp->d_name);
            //char removed = remove(pp->d_name);
            puts (returnData);
        }
        (void) closedir (p);
     }
  }
  write(sd, &returnData, sizeof(returnData));
  return(0);
}

int getname(char *string) {
   char * token = strtok(string, ".");

   while( token != NULL ) {
	   if(token != "txt"){
		printf( " %s\n", token );
		token = strtok(NULL, ".");
	   }
   }
   return 0;
}

int countLines(int sd2, char *filename){
	char buf_send[1000];
	int ch=0;
    int lines=0;
	FILE * fp;

	if((fp = fopen(filename,"r"))==NULL)
	{
		sprintf(buf_send,"File could not be found.");
		fflush(stdout);
		exit(0);
	}
	else
	{
		printf("\nFile found.\n");
		while(!feof(fp))
    	{
			ch = fgetc(fp);
			if(ch == '\n')
			{
				lines++;
			}
		}
		fclose(fp);	
    }
	write(sd2, &lines, sizeof(lines));
	printf("Successfuly sending lines count output.");
	
	close(sd2);
	exit(0);
}

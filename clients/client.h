#define MAXLINE 4096
#define SERV_PORT 3000
#define MAXBUF 256  
#define BUFFSIZE 6

void printMenu();
int countLines(int sd);
void comm_service(int socket_fd);
void comm_service1(int socket_fd);
//int service_handle1(int sd);
int service_handle1(int sd, char *filename);
int useFile(int sd);
#ifndef SERVER_HEADER
#define SERVER_HEADER

// types

#define BUFF_SIZE 4
#define LIST_FUNC "LIST"
#define READ_FUNC "READ"

// functions
void* body(int *arg);
int connectToServer(int port);
void comm_service(int client_connection_fd);
//void do_service1(int sd2);
void do_service1(int sd2, char *filename);
int countLines(int sd2, char *filename);
int list(int sd);
int getname(char *string);
//int countLines(int sd2);

#endif
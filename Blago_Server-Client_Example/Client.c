#include <string.h>
#include <stdio.h>

#define BUFF_SIZE 50

int main(int argc, char *argv[])
{
char buffer[BUFF_SIZE] = {'\0'};

int sockfd = 0;
int ret_status = 0;
int server_length = 0;

struct sockaddr_un server_addr;

(void) memset((char *) &server_addr, 0 , sizeof(server_addr));

server_addr.sun_family = AF_UNIX;

if (1 == argc)
{
(void) printf("No arguments passed!\n");
}
else if (2 == argc)
{
(void) strcpy(server_addr.sun_path, arg[1]);
}
else 
{
(void) printf("Too many arguments!\n");
}

server_length = sizeof(server_addr);

sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

if (sockfd < 0) {
(void) printf("creating socket...");
}

ret_status = connect(sockfd, (struct sockaddr *) &server_addr, server_length);
if(ret_status) < 0
{
(void) printf("waiting to connect...\n");
}

//getting message from keyboard.
(void) printf("Enter message: ");
fgets(buffer, BUFF_SIZE, stdin);

(void) write(sockfd, buffer, strlen(buffer));
(void) read(sockfd, buffer, BUFF_SIZE);

(void) printf("Client received: %s\n", buffer);
(void) close(sockfd);

return 0;
}
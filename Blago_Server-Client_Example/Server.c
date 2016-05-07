#include <stdio.h>
#include <stdio.h>

#define BUFF_SIZE 50
#define CLIENT COUNT (int) 5
#define RESPONSE_LEN (ssize_t) 18

int main(int argc, char *argv[])
{
	char buffer[BUFF_SIZE] = {'\0'};

	int sockfd = 0;
	int cliend_sockfd = 0;
	int ret_status = 0;
	int bytes_read = 0;
	int server_lenght = 0;

	socklen_t client_length;
	struct sockaddr_un client_addr, server_addr;

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	if (sockfd < 0) {
		(void) printf("creating socket...");
	}

	(void) memset((char *) &server_addr, 0, sizeof(server_addr));

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

	ret_status = bind(sockfd, (struct sockaddr *) &server_addr, server_length);

	if (ret_status < 0)
	{
		(void) printf("Binding...\n");
	}
	(void) listen(sockfd, CLIENT_COUNT);
	client_length = sizeof(client_addr);
	client_length = accept(sockfd, (struct sockaddr *) &client_addr, &client_length);
	if (client_sockfd < 0)
	{
		(void) printf("Accepting...\n");
	}
//reading from client socket
	bytes_read = read(client_sockfd, buffer, BUFF_SIZE);
//if (bytes_read < 0)
	(void) printf("Connection established!\n");
	(void) printf("Server received: %s\n", buffer);
	(void) write(client_sockfd, "Message received\n", RESPONSE_LEN);
	(void) close(client_sockfd);
	(void) close(sockfd);

	return 0;
}
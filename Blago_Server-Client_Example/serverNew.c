#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

#define CLIENT_NUMBER (int) 10
#define BUFF_SIZE  50

int main(int argc , char *argv[])
{
	int sockfd = 0;
	int res_status = 0 ;
	int bytes_read = 0;
	int server_length = 0;
	char buffer[BUFF_SIZE] = {'\0'};
	int temp_sockfd = 0;
	
	socklen_t client_length;
	struct sockaddr_in client_addr, server_addr;
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	if(sockfd < 0)
		{
			printf("Creating socket : %d\n",sockfd);
		}

	(void) memset((char*)&server_addr , 0 , sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr =  INADDR_ANY;
	server_addr.sin_port = htons(9999);
	
	//(void)strcpy(server_addr.sin_path , argv[1]);
	
	res_status = bind(sockfd , (struct sockaddr*)&server_addr,sizeof(server_addr));
	if(res_status < 0 )
	{
		printf("Binding ... \n");
	}
	(void) listen(sockfd , CLIENT_NUMBER );

	client_length = sizeof(client_addr);
	
	temp_sockfd = accept(sockfd , (struct sockaddr*)&client_addr , &client_length);
	if(temp_sockfd < 0 ) 
	{
		printf("Accepting...\n");
	}
	bytes_read = read(temp_sockfd , buffer , BUFF_SIZE);
	
	(void) printf("Connection established...\n");
	(void) printf("%s\n",buffer);
	(void) write(sockfd , "Message received" , sizeof("Message received") );
	(void) close(temp_sockfd);
	(void) close(sockfd);

return 0;
}

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

#define BUFF_SIZE  50

int main(int argc , char *argv[])
{
	int sockfd = 0;
	int res_status = 0 ;
	int bytes_read = 0;
	int server_length = 0;
	char buffer[BUFF_SIZE] = {'\0'};
	
	struct sockaddr_in server_addr;

	(void) memset((char*)&server_addr , 0 , sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr =  INADDR_ANY;
	server_addr.sin_port = htons(9999);
	
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	if(sockfd < 0)
		{
			printf("Creating socket : %d\n",sockfd);
		}
	res_status = connect(sockfd , (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(res_status < 0 )
	{
		printf("Connecting... \n");
	}
	(void) printf("Enter a message :");
	fgets(buffer , BUFF_SIZE , stdin);
	(void) write(sockfd , buffer , strlen(buffer));
	bytes_read = read(sockfd , buffer ,BUFF_SIZE );
	(void) printf("%s\n",buffer);
	(void) close(sockfd);
	

return 0;
}
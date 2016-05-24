#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define ALL_LAUNDRIES 6

typedef enum { false, true } bool;

typedef struct Laudry {
  int id;
  int machine_id;
  int client_id;
  int status;
} Laundry;

int check(int laundry);

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
      
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   /* Accept actual connection from the client */
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
   if (newsockfd < 0) {
      perror("ERROR on accept");
      exit(1);
   }
   
   /* If connection is established then start communicating */
     int received_int;
     n = read(newsockfd, &received_int, sizeof(received_int));
     int laundry_id = ntohl(received_int);

  // bzero(buffer,256);
  // n = read( newsockfd,buffer,255 );
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   

   printf("Here is the id: %d\n", laundry_id);

   //printf("Here is the message: %s\n",buffer);
   
   /* Write a response to the client */

   int laundry_status = check(laundry_id);

   printf("Status %d\n", laundry_status);


   if(laundry_status == -1) {
     n = write(newsockfd,"I could not find your laundry", strlen("I could not find your laundry"));
   }

   if(laundry_status == 4) {
     n = write(newsockfd,"Your laundry is ready", strlen("Your laundry is ready"));
   }

   if(laundry_status == 1) {
     n = write(newsockfd,"Your laundry is waiting for a free washing machine", strlen("Your laundry is waiting for a free washing machine"));
   }

   if(laundry_status == 2) {
     n = write(newsockfd,"Your laundry is now in the wahsing machine", strlen("Your laundry is now in the wahsing machine"));
   }

   if(laundry_status == 3) {
     n = write(newsockfd,"Your laundry is now in the dryer", strlen("Your laundry is now in the dryer"));
   }
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
      
   return 0;
}

int check(int laundry_id) {
   if(laundry_id < 0) {
       return -2;
   }

  Laundry laundry0 = {1,1,1,4};
  Laundry laundry1 = {2,3,2,2};
  Laundry laundry2 = {3,3,6,4};
  Laundry laundry3 = {4,1,4,1};
  Laundry laundry4 = {5,2,5,3};
  Laundry laundry5 = {6,1,3,4};
 
  Laundry all[] = {laundry0, laundry1, laundry2, laundry3, laundry4, laundry5};
 
   int i = 0;
   for (i = 0; i < ALL_LAUNDRIES; i++ ) {
     if(laundry_id == all[i].id) {
       return all[i].status;
     }
   } 

   return -1;
}

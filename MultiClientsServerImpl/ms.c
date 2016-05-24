#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
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

void doprocessing (int sock);
void sendLaundryStatus(int sock, int status);
int check(int laundry_id);

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;
   
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
   
   /* Now start listening for the clients, here
      * process will go in sleep mode and will wait
      * for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   while (1) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      
      /* Create child process */
      pid = fork();
		
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         /* This is the client process */
         doprocessing(newsockfd);
         close(sockfd);
         exit(0);
      }
      else {
         close(newsockfd);
      }
		
   } /* end of while */
}

void doprocessing (int sock) {
   int n;
   int received_int;
   n = read(sock, &received_int, sizeof(received_int));
   int laundry_id = ntohl(received_int);

  // char buffer[256];
  // bzero(buffer,256);
  // n = read(sock,buffer,255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   
   printf("Here is the id: %d\n", laundry_id);
   
   int laundry_status = check(laundry_id);

   printf("Status %d\n", laundry_status);
   sendLaundryStatus(sock, laundry_status);
   

  // n = write(sock,"I got your message",18);
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }	
}

void sendLaundryStatus(int sock, int status) {

   int n;

   switch(status) {
      case 1: { n = write(sock,"Your laundry is waiting for a free washing machine", strlen("Your laundry is waiting for a free washing machine")); break; };
      case 2: { n = write(sock,"Your laundry is now in the wahsing machine", strlen("Your laundry is now in the wahsing machine")); break; };
      case 3: { n = write(sock,"Your laundry is now in the dryer", strlen("Your laundry is now in the dryer")); break; };
      case 4: { n = write(sock,"Your laundry is ready", strlen("Your laundry is ready")); break; };
      default: { n = write(sock,"I could not find your laundry", strlen("I could not find your laundry")); break; };
   }

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
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

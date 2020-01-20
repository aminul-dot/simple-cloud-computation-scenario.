/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
 
void error(const char *msg) //error function
{
    perror(msg);  //system error message
    exit(1);
}

int main(int argc, char *argv[]) 		
{
     int sockfd, newsockfd, portno; 		
     socklen_t clilen; 				
     char buffer[255];   			
     struct sockaddr_in serv_addr, cli_addr;  		
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n"); 
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);   
     if (sockfd < 0) 
        error("ERROR opening socket");

 	/* Initialize socket structure */

     bzero((char *) &serv_addr, sizeof(serv_addr)); 
     portno = atoi(argv[1]);                     
 						
						

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

	/* Binding */
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

     listen(sockfd,5);            
     clilen = sizeof(cli_addr);

     newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen); 
     if (newsockfd < 0) 
          error("ERROR on accept");
      printf("hello it is executed");

           //bzero(buffer,256);   
           n = read(newsockfd,buffer,255);
           if (n < 0) error("ERROR reading from socket");

       int i = 0;
	int sum = 0;
	int temp = 0;
	while(buffer[i]!='/')
	{
		if(buffer[i] !=',')
		{
			temp = temp*10;
			temp = temp + buffer[i]-'0';
		}
		else
		{
			sum = sum+temp;
			temp=0;
		}
		i++;
	}
	sum = sum + temp;
	bzero(buffer,255);
	sprintf(buffer,"%d",sum);

       n = write(newsockfd,buffer,strlen(buffer));
           if (n < 0) error("ERROR writing to socket");
           
     
     return 0; 
}

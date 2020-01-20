/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
 
void error(const char *msg) //error function
{
    perror(msg);  //system error message
    exit(1);
}

int main(int argc, char *argv[]) 		
{
     int sockfd, newsockfd, portno; 
     portno = 8001;		
     socklen_t clilen; 				
     char buffer[255];   			
     struct sockaddr_in serv_addr, cli_addr;  		
     int n,n3;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n"); 
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);   
     if (sockfd < 0) 
        error("ERROR opening socket");

 	/* Initialize socket structure */

     bzero((char *) &serv_addr, sizeof(serv_addr)); //
                          
 						
						

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
 

           bzero(buffer,256);   
           n = read(newsockfd,buffer,255);
           if (n < 0) {
          error("ERROR reading from socket");
            }


    /*DATA SERVER*/


    int d_sockfd, portno_d;
    portno_d = 8002;
    struct sockaddr_in d_serv_addr;
    struct hostent *d_server;
    char *ip = "127.0.0.1";
  
    
    
    d_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (d_sockfd < 0) 
        error("ERROR opening socket");
    d_server = gethostbyname(ip);
    if (d_server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &d_serv_addr, sizeof(d_serv_addr));
    d_serv_addr.sin_family = AF_INET;
    bcopy((char *)d_server->h_addr, 
         (char *)&d_serv_addr.sin_addr.s_addr,
         d_server->h_length);
    d_serv_addr.sin_port = htons(portno_d);
    if (connect(d_sockfd,(struct sockaddr *) &d_serv_addr,sizeof(d_serv_addr)) < 0) 
        error("ERROR connecting");

      n3 = write(d_sockfd,buffer,sizeof(buffer));
	if(n3<0)
	{
		perror("Error reading from socket");
	}
        n = read(d_sockfd,buffer,255);
        if (n < 0) 
             error("ERROR reading from socket");
        
/*computation SERVER*/
  int c_sockfd, portno_c, n2;
    struct sockaddr_in c_serv_addr;
    struct hostent *c_server;
    portno_c = 8003;
    c_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (c_sockfd < 0) 
        error("ERROR opening socket");
    c_server = gethostbyname(ip);
    if (c_server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &c_serv_addr, sizeof(c_serv_addr));
    c_serv_addr.sin_family = AF_INET;
    bcopy((char *)c_server->h_addr, 
         (char *)&c_serv_addr.sin_addr.s_addr,
         c_server->h_length);
    c_serv_addr.sin_port = htons(portno_c);
    if (connect(c_sockfd,(struct sockaddr *) &c_serv_addr,sizeof(c_serv_addr)) < 0) 
        error("ERROR connecting");

      n3 = write(c_sockfd,buffer,sizeof(buffer));
	if(n3<0)
	{
		perror("Error reading from socket");
	}
       
	bzero(buffer,255);
        n = read(c_sockfd,buffer,255);
        if (n < 0) 
             error("ERROR reading from socket");



     n3 = write(newsockfd,buffer,strlen(buffer));
     if (n3 < 0) error("ERROR writing to socket");

           
}

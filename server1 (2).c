#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{  // error method
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     
     //check all command line argumants
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     
     //creating a socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0); // creating socket
     
     if (sockfd < 0) 
        error("ERROR opening socket");
        
     bzero((char *) &serv_addr, sizeof(serv_addr)); //clearing the server
     
     // geting ready server addr.
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno); // covert in network format htons
     
     //binding all
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
     	error("ERROR on binding");
     	
     listen(sockfd,5); // 5 clinet i will be handling
     
     clilen = sizeof(cli_addr);
     
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     
     if (newsockfd < 0) 
     	error("ERROR on accept");
     	
     bzero(buffer,256); // clearing buffer
     
     int num1,num2,ans,choice;
     
S:	num1 = write(newsockfd,"Enter Number 1 : ",strlen("Enter Number 1")); // S->back to top

	
	read(newsockfd,&num1,sizeof(int));
	
	printf("Client Number 1 is : %d\n",num1);

	num2 = write(newsockfd,"Enter Number 2 : ",strlen("Enter Number 1")); // num2

        
        read(newsockfd,&num2,sizeof(int));
        
        printf("Client Number 2 is : %d\n",num2);

	choice = write(newsockfd,"Enter Your Choice\n1.Add\n2.Subtract\n3.Division\n4.Multiplication\n5.Exit",strlen("Enter Your Choice\n1.Add\n2.Subtract\n3.Division\n4.Multiplication\n5.Exit"));
	printf("Enter Your Choice\n1.Add\n2.Subtract\n3.Division\n4.Multiplication\n5.Exit");
	if(choice < 0){
		error("Error on Writing");
	}
	read(newsockfd,&choice,sizeof(int));
	printf("Client - Choice is : %d\n",choice);

	switch(choice){
		case 1:
			ans = num1 + num2;
			break;
		case 2:
		        ans = num1-num2;
			break;
		case 3:
		        ans = num1/num2;	
			break;
		case 4:
			ans = num1*num2;
			break;

		case 5 :
		       goto Q;
	               break;	       

	}

	write(newsockfd,&ans,sizeof(int)); 
	if(choice != 5){
		goto S;
	}

Q:	close(newsockfd);
	close(sockfd);
	return 0;
}

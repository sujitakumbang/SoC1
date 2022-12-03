#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

//error method
void error(char *msg)
{
    perror(msg);
    exit(0);
}

// argc -> count argv ->storing the value
int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256]; // it have all the values
    
    
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    
    
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    
    if (sockfd < 0) 
        error("ERROR opening socket");
        
        
    server = gethostbyname(argv[1]);
    
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
        
    int num1,num2,choice,ans;

	//Reading Server String 
S:      bzero(buffer,256);
	num1 = read(sockfd,buffer,256);
	if(num1 < 0){
		error("Error reading From Socket");
	}

	printf("Server - %s\n",buffer);
	scanf("%d",&num1);
	write(sockfd,&num1,sizeof(int));

	bzero(buffer,256);
        num2 = read(sockfd,buffer,256);
        if(num2 < 0){
                error("Error reading From Socket");
        }

        printf("Server - %s\n",buffer);
        scanf("%d",&num2);
        write(sockfd,&num2,sizeof(int));

	bzero(buffer,256);
        choice = read(sockfd,buffer,256);
        if(choice < 0){
                error("Error reading From Socket");
        }

        printf("Server - %s\n",buffer);
        scanf("%d",&choice);
        write(sockfd,&choice,sizeof(int));

	if(choice == 5){
		goto Q;
	}

	read(sockfd,&ans,sizeof(int));
	printf("Server : The answere is : %d\n",ans);

	if(choice != 5){
		goto S;
	}

Q:      printf("You Have Selected to exit\nExit Successfully");
	close(sockfd);
	return 0;

}

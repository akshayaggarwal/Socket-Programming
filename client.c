// creates a TCP client

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

/* function to manually convert String to integer
int toString(char a[]) {
  int c, sign, offset, n;
 
  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }
 
  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }
 
  n = 0;
 
  for (c = offset; a[c] != '\n'; c++) {
    n = n * 10 + a[c] - '0';
  }
 
  if (sign == -1) {
    n = -n;
  }
 
  return n;
}*/

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int fargc, char *func[])
{
    char *argv[3]={"./client","localhost","25034"};
    int argc = 3;
	int function, index;	
	int nn = 10;
	int a = 0,i;
	char str[nn];
	int num[1024];
												
	FILE *file = fopen("nums.csv", "r");						//opening nums.csv file	
	
			if(func[1][0] == 's' && func[1][1]=='u' && func[1][2]=='m')
				index = 1;
			else if(func[1][0]=='s'&&func[1][1]=='o'&&func[1][2]=='s')
				index = 2;
			else if(func[1][0]=='m'&&func[1][1]=='i'&&func[1][2]=='n')
				index = 3;
			else if(func[1][0]=='m'&&func[1][1]=='a'&&func[1][2]=='x')
				index = 4;
			else index = 5;
    int si = 0;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3){
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

// Block of statements for socket connection is taken from Beej's guide for socket programming and Sockets tutorial on linuxhowtos.org

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("\nClient is up and running\n");
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    bzero(buffer,256);

    i =2;
											
	while(fgets(str,nn,file)){							//reading nums.csv file
	
		a = a + 1;	
		int k;	
		sscanf(str, "%d", &k);
		num[i] = k;	
		si = si + 1;	
		i = i + 1;
		if (n < 0) 
				error("ERROR writing to socket");
	}
	fclose(file);
    num[0] = index;
    num[1] = si;

    n = write(sockfd,num,4096);								//sending integer array to aws server
    if(index == 1){
		printf("\nClient has sent the reduction type SUM to AWS\n");
	}  
    else if(index == 2){
		printf("\nClient has sent the reduction type SOS to AWS\n");
	}
    else if(index == 3){
		printf("\nClient has sent the reduction type MIN to AWS\n");
	}
    else if(index == 4){
		printf("\nClient has sent the reduction type MAX to AWS\n");
	}
    printf("Client has sent %d numbers to AWS",num[1]);
    bzero(buffer,256);
    n = read(sockfd,buffer,255);							//reading the final result from aws server 
    if (n < 0) 
         error("ERROR reading from socket");
    if(index == 1){
		printf("\nClient has received reduction SUM: ");
		printf("%s\n",buffer);
	} 
    else if(index == 2){
		printf("\nClient has sent the reduction SOS: ");
		printf("%s\n",buffer);
	}
    else if(index == 3){
		printf("\nClient has sent the reduction MIN: ");
		printf("%s\n",buffer);
	}
    else if(index == 4){
		printf("\nClient has sent the reduction MAX: ");
		printf("%s\n",buffer);
	}
    
    close(sockfd);
    return 0;
}

//creates a UDP server which runs forever

#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <limits.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

char *my_itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}

int main(int argc, char *argv[])
{
   int sock, length, n;
   int arr[1024],result[20];
   socklen_t fromlen;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[1024];

   if (argc < 2) {
      fprintf(stderr, "ERROR, no port provided\n");
      exit(0);
   }
   
   sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("Opening socket");
   printf("\nThe Server C is up and running using UDP on port 23034\n");
   signal(SIGCHLD, SIG_IGN);						// given to handle the problem of zombie processes
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(atoi(argv[1]));
   if (bind(sock,(struct sockaddr *)&server,length)<0) 
       error("binding");
   fromlen = sizeof(struct sockaddr_in);
   while (1) {
       n = recvfrom(sock,arr,4096,0,(struct sockaddr *)&from,&fromlen);
       if (n < 0) error("recvfrom");
	int index;	
	int i,sum[1];sum[0] =0;
	int max = INT_MIN;
	int min = INT_MAX;
	printf("\nServer C has received %d numbers\n",arr[0]);	
	if(arr[1] == 1)
	{
	for(i=2;i<arr[0]+2;i++){
		sum[0] = sum[0] + arr[i];
		}
	printf("\nThe Server C has successfully finished the reduction SUM: %d \n",sum[0]);
	}

	else if(arr[1] == 2)
	{
	for(i=0;i<arr[0];i++){
		sum[0] = sum[0] + (arr[i+2]*arr[i+2]);
		}
	printf("\nThe Server C has successfully finished the reduction SUM of Squares: %d \n",sum[0]);
	}

	else if(arr[1] == 3)
	{
	for(i=0;i<arr[0];i++){
		if (arr[i+2] < min)	
			min = arr[i+2];	
		sum[0] = min;
		}
	printf("\nThe Server C has successfully finished the reduction MIN %d \n",sum[0]);
	}

	if(arr[1] == 4)
	{
	for(i=0;i<arr[0];i++){
		if (arr[i+2] > max)	
			max = arr[i+2];	
		sum[0] = max;
		}
	printf("\nThe Server C has successfully finished the reduction MAX: %d \n",sum[0]);
	}

	//sending the result back to aws

        n = sendto(sock,&sum,4,
                  0,(struct sockaddr *)&from,fromlen);
       if (n  < 0) error("sendto");
   printf("\nThe Server C has successfully finished sending the reduction value to AWS server\n");
   }

   return 0;
 }


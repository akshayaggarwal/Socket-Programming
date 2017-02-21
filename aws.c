//creates a TCP server and UDP clients

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define UDPPORT 24034
#include <signal.h>
#include <sys/types.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
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

//function to create a connection to serverA

int udpsockA(int argc, char *argv[],int arr[1024],int index,int si)
{
   int sock, n;
   int result[1];
   unsigned int length;
   struct sockaddr_in server, my_addr, from;
   struct hostent *hp;
   char buffer[256];
   int i;
   char str[6];  
   int arr2[1024];
   bzero(arr2,1024);

   int sitemp = si/3;
   sitemp = sitemp + 2;
   for(i=2;i<sitemp;i++)	
		{arr2[i] = arr[i];
		}
   (arr2[1]) = index;
   arr2[0] = si/3;
   if (argc != 3) { printf("Usage: server port\n");
                    exit(1);
   }

// Block of statements for socket connection is taken from Beej's guide for socket programming and Sockets tutorial on linuxhowtos.org

   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("socket");

   my_addr.sin_family = AF_INET; 
   my_addr.sin_port = htons(UDPPORT); 
   my_addr.sin_addr.s_addr = INADDR_ANY; 
   bzero(&(my_addr.sin_zero), 8); 
   if (bind(sock, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1) 
   {
   perror("bind");
   exit(1);
   } 


   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   if (hp==0) error("Unknown host");

   bcopy((char *)hp->h_addr, 
        (char *)&server.sin_addr,
         hp->h_length);
   server.sin_port = htons(atoi(argv[2]));


   
   length=sizeof(struct sockaddr_in);
   bzero(buffer,256);
   n=sendto(sock,arr2,
            4096,0,(const struct sockaddr *)&server,length);
   if (n < 0) error("Sendto");
   n = recvfrom(sock,&result,4,0,(struct sockaddr *)&from, &length);
   if (n < 0) error("recvfrom");
   char snum[6];
   sprintf(snum, "%d", result[0]);
   write(1,"\n",1);
   close(sock);
   return result[0];
}

//function to create a connection to serverB

int udpsockB(int argc, char *argv[],int *arr,int index,int si)
{
   int sock, n;
   int result[1];
   unsigned int length;
   struct sockaddr_in server, my_addr, from;
   struct hostent *hp;
   char buffer[256];
   int i,j;
   char str[6];  
   int arr2[1024];
   bzero(arr2,1024);
   int sitemp = 2*(si/3);
   sitemp = sitemp + 2;
   for(i=(si/3)+2,j=2;i<sitemp;i++,j++)	
		{arr2[j] = arr[i];

		}
   (arr2[1]) = index;
   arr2[0] = si/3;
   if (argc != 3) { printf("Usage: server port\n");
                    exit(1);
   }

// Block of statements for socket connection is taken from Beej's guide for socket programming and Sockets tutorial on linuxhowtos.org

   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("socket");

   my_addr.sin_family = AF_INET; 
   my_addr.sin_port = htons(UDPPORT);
   my_addr.sin_addr.s_addr = INADDR_ANY; 
   bzero(&(my_addr.sin_zero), 8); 
   if (bind(sock, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1) 
   {
   perror("bind");
   exit(1);
   } 


   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   if (hp==0) error("Unknown host");

   bcopy((char *)hp->h_addr, 
        (char *)&server.sin_addr,
         hp->h_length);
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);
   bzero(buffer,256);
   n=sendto(sock,arr2,
            4096,0,(const struct sockaddr *)&server,length);
   if (n < 0) error("Sendto");
   n = recvfrom(sock,&result,4,0,(struct sockaddr *)&from, &length);
   if (n < 0) error("recvfrom");
   char snum[6];
   sprintf(snum, "%d", result[0]);
   write(1,"\n",1);
   close(sock);
   return result[0];
}


//function to create a connection to serverC

int udpsockC(int argc, char *argv[],int *arr,int index,int si)
{
   int sock, n;
   int result[1];
   unsigned int length;
   struct sockaddr_in server, my_addr, from;
   struct hostent *hp;
   char buffer[256];
   int i,j;
   char str[6];  
   int arr2[1024];
   bzero(arr2,1024);
   int sitemp = si;
   sitemp = sitemp + 2;
   for(i=(2*(si/3))+2,j=2;i<sitemp;i++,j++)	
		{arr2[j] = arr[i];

		}
   (arr2[1]) = index;
   arr2[0] = si/3;
   if (argc != 3) { printf("Usage: server port\n");
                    exit(1);
   }

// Block of statements for socket connection is taken from Beej's guide for socket programming and Sockets tutorial on linuxhowtos.org

   sock= socket(AF_INET, SOCK_DGRAM, 0);

   my_addr.sin_family = AF_INET; 
   my_addr.sin_port = htons(UDPPORT); 
   my_addr.sin_addr.s_addr = INADDR_ANY; 
   bzero(&(my_addr.sin_zero), 8); 
   if (bind(sock, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1) 
   {
    perror("bind");
   exit(1);
   }


   if (sock < 0) error("socket");

   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   if (hp==0) error("Unknown host");

   bcopy((char *)hp->h_addr, 
        (char *)&server.sin_addr,
         hp->h_length);
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);
   bzero(buffer,256);
   n=sendto(sock,arr2,
            4096,0,(const struct sockaddr *)&server,length);
   if (n < 0) error("Sendto");
   n = recvfrom(sock,&result,4,0,(struct sockaddr *)&from, &length);
   if (n < 0) error("recvfrom");
   char snum[6];
   sprintf(snum, "%d", result[0]);
   write(1,"\n",1);
   close(sock);
   return result[0];
}


int main(int argc, char *argv[])
{
     int g;
     int ptr[1024];
     bzero(ptr,1024);
     int sockfd, newsockfd, portno,i,sockfdudp;
     socklen_t clilen;
     char buffer[256];
     char arr[6];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	signal(SIGCHLD, SIG_IGN);     

// Block of statements for socket connection is taken from Beej's guide for socket programming and Sockets tutorial on linuxhowtos.org

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
     if (sockfd < 0) 
        error("ERROR opening socket");
     else
        printf("\nThe AWS is up and running\n");
     signal(SIGCHLD, SIG_IGN);
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     signal(SIGCHLD, SIG_IGN);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     
     
     n = read(newsockfd,ptr,4096);
     if (n < 0) error("ERROR reading from socket");
     char *str1[3]={"./combserver","localhost","21034"};
     char *str2[3]={"./combserver","localhost","22034"};
     char *str3[3]={"./combserver","localhost","23034"};
     int index = ptr[0];
	
	
     int si = ptr[1];
     printf("\nThe AWS has received %d numbers from client using TCP over port 25034\n",si);
     int subsize = si/3;
     printf("\nThe AWS sent %d numbers to Backend Server 1\n",subsize);
     printf("\nThe AWS sent %d numbers to Backend Server 2\n",subsize);
     printf("\nThe AWS sent %d numbers to Backend Server 3\n",subsize);
     
   
 
     int j1 = udpsockA(3,str1,ptr,index,si); //udp
     int j2 = udpsockB(3,str2,ptr,index,si);
     int j3 = udpsockC(3,str3,ptr,index,si);

     int jfinal;
	if(index == 1 || index == 2)
	{	
 		jfinal = j1 + j2 + j3;
		if(index == 1)     		
		{
		printf("\nThe AWS received reduction result of SUM from Backend­Server 1 using UDP over port 21034 and it is %d\n",j1);
		printf("\nThe AWS received reduction result of SUM from Backend­Server 2 using UDP over port 22034 and it is %d\n",j2);
		printf("\nThe AWS received reduction result of SUM from Backend­Server 3 using UDP over port 23034 and it is %d\n",j3);
		printf("\nThe AWS has successfully finished the reduction SUM: %d\n",jfinal);		
		}
		if(index == 2)     		
		{
		printf("\nThe AWS received reduction result of SOS from Backend­Server 1 using UDP over port 21034 and it is %d\n",j1);
		printf("\nThe AWS received reduction result of SOS from Backend­Server 2 using UDP over port 22034 and it is %d\n",j2);
		printf("\nThe AWS received reduction result of SOS from Backend­Server 3 using UDP over port 23034 and it is %d\n",j3);
		printf("\nThe AWS has successfully finished the reduction SOS: %d\n",jfinal);	
		}
	}
	else if(index == 3)
	{
		if(j1 < j2 && j1 < j3)
			jfinal = j1;
		else if(j2 < j1 && j2 < j3)
			jfinal = j2;
		else 
			jfinal = j3;
		printf("\nThe AWS received reduction result of MIN from Backend­Server 1 using UDP over port 21034 and it is %d\n",j1);
		printf("\nThe AWS received reduction result of MIN from Backend­Server 2 using UDP over port 22034 and it is %d\n",j2);
		printf("\nThe AWS received reduction result of MIN from Backend­Server 3 using UDP over port 23034 and it is %d\n",j3);
		printf("\nThe AWS has successfully finished the reduction MIN: %d\n",jfinal);	
		

	}
	else if(index == 4)
	{
		if(j1 > j2 && j1 > j3)
			jfinal = j1;
		else if(j2 > j1 && j2 > j3)
			jfinal = j2;
		else 
			jfinal = j3;
		printf("\nThe AWS received reduction result of MAX from Backend­Server 1 using UDP over port 21034 and it is %d\n",j1);
		printf("\nThe AWS received reduction result of MAX from Backend­Server 2 using UDP over port 22034 and it is %d\n",j2);
		printf("\nThe AWS received reduction result of MAX from Backend­Server 3 using UDP over port 23034 and it is %d\n",j3);
		printf("\nThe AWS has successfully finished the reduction MAX: %d\n",jfinal);	
		
	}

     char result[20];
     sprintf(result, "%d", jfinal);
     n = write(newsockfd,result,19);
     if (n < 0) error("ERROR writing to socket");
     else
	printf("\nThe AWS has successfully finished sending the reduction value to client\n");  
     close(newsockfd);
     close(sockfd);

    
   
     return 0; 
}

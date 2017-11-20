#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>

void set_ledOnOff();
int read_ledState();
int fd;

void sig_handler(int sig)
{
	if(sig!=SIGINT)
	{
		printf("Invalid signal received\n");
		exit(0);
	}
	printf("Received SIGINT closing fd\n");
	close(fd);
	exit(0);
}

#define HOST_ADDR "10.0.0.165"
int main()
{
	int sockfd,connectionfd;
	signal(SIGINT,sig_handler);
	char sendBuff[1024];
	char recvBuff[1024];
	int n;
	long counter = 0;
	struct sockaddr_in lclientaddr,lserveraddr;
	fd = open("/dev/LED", O_RDWR);
	if(fd < 0)
	{
		perror("File failed to open\n");
		return 0;
	}

	//Open a TCP Socket
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Error opening socket\n");
		return 0;
	}
	lserveraddr.sin_family = AF_INET;
	lserveraddr.sin_addr.s_addr = inet_addr(HOST_ADDR);
	lserveraddr.sin_port = htons(5000);

	bind(sockfd,(struct sockaddr*)&lserveraddr,sizeof(lserveraddr));

	listen(sockfd,10);

	connectionfd = accept(sockfd,(struct sockaddr*)NULL,NULL);
	n = read(connectionfd,recvBuff,1024);
	if(n<0)
	{
		perror("Receive error\n");
	}

	printf("What I received from client..:%s\n",recvBuff);

	if(!strncmp(recvBuff,"ON",2) || !strncmp(recvBuff,"OFF",3))
	{
		printf("Entered led off/on function\n");
		set_ledOnOff(recvBuff);
	}

	else if(!strncmp(recvBuff,"FREQ50",6))
		set_ledFreq(recvBuff);

	close(connectionfd);
	//n = write(sockfd,sendBuff,1024);
	/*while(1)
	{
		connectionfd = accept(sockfd,(struct sockaddr*)NULL,NULL);
		counter=1;
		sprintf(sendBuff,"%ld",counter);
		write(connectionfd,sendBuff,strlen(sendBuff));

		close(connectionfd);
		sleep(1);

	}*/

}


void set_ledOnOff(char option[])
{
	int ret = write(fd,option,strlen(option));
	//printf("Length of op:%d\n",strlen(option));
	if(ret < 0)
	{
		perror("Error performing write ON\n");

	}
	close(fd);
}

void set_ledFreq(char option[])
{
	int ret = write(fd,option,strlen(option));
		
	if(ret < 0)
	{
		perror("Error performing write frequencys\n");
	}
//	close(fd);
}

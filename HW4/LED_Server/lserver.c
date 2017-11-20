/*
* FileName        : lserver.c
* Description     :	Server end on BBG getting commands from user application on PC to perform
					ON,OFF,FREQ control and duty cycle control. Current LED State that such
					as ON/OFF, FREQ and DUty cycle can also be read
					Command Set:
					ON  -Turn ON LED
					OFF -Turn OFF LED
					FREQ:n - Set frequency to value n
					DUTY:n - Set duty cycle to value n
					REQALL - Request all state information ON/OFF,FREQ and DUTY
					REQFREQ - Request Frequency
					REQDUTY - Request Duty cycle

* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc,gdb
*/

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
	int sockfd,connectionfd,ret;
	signal(SIGINT,sig_handler);
	char sendBuff[1024];
	char recvBuff[1024];
	char buffer[1024];
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

	ret = write(fd,rcvBuff,strlen(rcvBuff));
	if(ret < 0)
	{
		perror("Error performing write ON\n");

	}
	if(!strncmp(recvBuff,"REQALL",6) || !strncmp(recvBuff,"REQFREQ",7) || !strncmp(recvBuff,"REQDUTY",7) || !strncmp(recvBuff,"REQONOFF",8))
	{
		ret = read(fd,buffer,1024);
		printf("Value read:%s\n",buffer);
	}
	close(fd);
	close(connectionfd);
	

}



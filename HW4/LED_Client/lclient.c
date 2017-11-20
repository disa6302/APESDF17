/*
* FileName        : lclient.c
* Description     :	Client end on PC sending commands to user application on BBG to perform
					ON,OFF,FREQ coontrol and duty cycle control. Current LED State that such
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

#define HOST_ADDR "10.0.0.165"
int main()
{
	int socketfd,n,fd;
	char recvbuff[1024] ="REQALL";

	struct sockaddr_in lclientaddr;

	if((socketfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Error opening socket\n");
		return 0;
	}
	lclientaddr.sin_family = AF_INET;
	lclientaddr.sin_addr.s_addr = inet_addr(HOST_ADDR);
	lclientaddr.sin_port = htons(5000);

	if(connect(socketfd,(struct sockaddr*)&lclientaddr,sizeof(lclientaddr))<0)
	{
		perror("Connection failed\n");
		return 0;
	}

	n = write(socketfd,recvbuff,strlen(recvbuff));

	if(n<0)
	{
		perror("writing into buffer\n");
	}
}
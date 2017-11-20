/*
* FileName        : led_app.c
* Description     :	Test application to test certain functionalitie
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
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define BUFFER_LENGTH 256
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



int main()
{
	int ret;
	signal(SIGINT,sig_handler);
	char op[BUFFER_LENGTH]="FREQ:1";
	char buffer[1024];
	printf("Initiating device driver testing...\n");
	fd = open("/dev/LED", O_RDWR | O_SYNC);
	if(fd < 0)
	{
		perror("Error opening file");
		return 0;
	}

	ret = write(fd,"DUTY:30",7);
	ret = write(fd,"REQFREQ",7);
	ret = read(fd,buffer,1024);
		
	printf("Value read:%s\n",buffer);
	printf("Length of op:%d\n",strlen(op));
	if(ret < 0)
	{
		perror("Error performing write ON\n");
		return 0;
	}
	return 0;
	
}

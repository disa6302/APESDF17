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
	//int count = 250000;
	char op[BUFFER_LENGTH]="FREQ:50";
	char buffer[1024];
	printf("Initiating device driver testing...\n");
	fd = open("/dev/LED", O_RDWR | O_SYNC);
	if(fd < 0)
	{
		perror("Error opening file");
		return 0;
	}
//	while(1)
//	{
	//	count--;
		ret = write(fd,op,strlen(op));
		ret = write(fd,"REQFREQ",7);
		ret = read(fd,buffer,1024);
		
		printf("Value read:%s\n",buffer);
		printf("Length of op:%d\n",strlen(op));
		if(ret < 0)
		{
			perror("Error performing write ON\n");
			return 0;
		}
//		usleep(500000);
		/*ret = write(fd,"ON",2);
		if(ret < 0)
		{
			perror("error performin write OFF\n");
		}
//		usleep(500000);
		*/

	//	if(!count)
	//		break;
//	}
//	close(fd);
	return 0;
	
}

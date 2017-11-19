#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_LENGTH 256

int main()
{
	int ret,fd;
	int count = 250000;
	char op[BUFFER_LENGTH]="ON";
	printf("Initiating device driver testing...\n");
	fd = open("/dev/LED", O_RDWR | O_SYNC);
	if(fd < 0)
	{
		perror("Error opening file");
		return 0;
	}
	while(1)
	{
		count--;
	ret = write(fd,op,strlen(op));
	printf("Length of op:%d\n",strlen(op));
	if(ret < 0)
	{
		perror("Error performing operation\n");
		return 0;
	}

	usleep(5000);
	ret = write(fd,"OFF",3);
	if(!count)
		break;
	}
	close(fd);
}

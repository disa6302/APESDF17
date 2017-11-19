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
	char op[BUFFER_LENGTH]="ON";
	printf("Initiating device driver testing...\n");
	fd = open("/dev/LED", O_RDWR);
	if(fd < 0)
	{
		perror("Error opening file");
		return 0;
	}
	ret = write(fd,op,strlen(op));
	if(ret < 0)
	{
		perror("Error performing operation\n");
		return 0;
	}
	
	close(fd);
}

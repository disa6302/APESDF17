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
	char recvbuff[1024] ="OFF";

	struct sockaddr_in lclientaddr;
	/*fd = open("/dev/LED", O_RDWR);
	if(fd < 0)
	{
		perror("File failed to open\n");
		return 0;
	}*/

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


	/*while((n=read(socketfd,recvbuff,sizeof(recvbuff)-1))>0)
	{
		recvbuff[n] = 0;
		if(fputs(recvbuff,stdout) == EOF)
		{
			perror("FPUTS ERROR!\n");
		}
	
	}

	if(n<0)
	{
		perror("Read Error\n");
	}*/
	//printf("recvbuff:%s\n",recvbuff);
	n = write(socketfd,recvbuff,strlen(recvbuff));

	if(n<0)
	{
		perror("writing into buffer\n");
	}
}
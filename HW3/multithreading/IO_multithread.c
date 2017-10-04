#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>


size_t file_size = 0;
struct statistics {
	size_t words;
	size_t line;
	size_t count;
	char **filename
};
struct statistics statistic;
volatile sig_atomic_t processing = 0;
volatile sig_atomic_t report = 0;

void handle(int signal)
{

    switch(signal)
    {
    	case SIGUSR1:
    			processing = 1;
    			break;
    	case SIGUSR2:
    			report = 1;
    			break;
    }
}
void* to_file(void* arg)
{
	//struct statistics statistic;
	char* buff = malloc(1024*sizeof(char));
    memset(buff,0,sizeof(buff));
    FILE* fp = NULL;
	statistic.filename = (char**)arg;
	fp = fopen(statistic.filename,"w+");
    printf("Enter your text:");
    fgets(buff, 1024*sizeof(char),stdin);
    file_size = fwrite(buff,1,strlen(buff)*sizeof(char),fp);
    printf("Number of characters written into file:%d\n",file_size);
    fclose(fp);

}

void* from_file(void* arg)
{
	while(1)
	{
	  if(processing)
      {
	    FILE* fp = NULL;
	//    struct statistics statistic;
	    statistic.words=0;
	    statistic.count=0;
	    statistic.line=0;
		statistic.filename = (char**)arg;
		fp = fopen(statistic.filename,"r+");
		char* buff = malloc(1024*sizeof(char));
	    memset(buff,0,sizeof(buff));
	    file_size = fread(buff,1,1024*sizeof(char),fp);
	    printf("Number of characters read from file:%d\n",file_size);
	    while(*buff!=NULL)
	    {
	    	if(*buff != ' ' || *buff !='\n') statistic.count ++;
	    	if(*buff == ' ' || *buff == '\n') statistic.words++;
	    	if(*buff == '\n') statistic.line++;

	    	buff++;

	    }
	    printf("Words:%d\nLines:%d\nCharacters:%d\n",statistic.words,statistic.line,(statistic.count)-1);
	    fclose(fp);
	    break;
	  }	
	}
	
}

void* reporting(void* arg)
{
//	struct statistics statistic;
	while(1)
	{
		if(report)
		{
			printf("Number of words:%d\n",statistic.words);
			printf("Number of line:%d\n",statistic.line);
			printf("Number of characters:%d\n",(statistic.count)-1);
			break;
		}
	}
}


int main(int argc, char** argv)
{
	printf("Current PID:%d\n",getpid());
	pthread_t write_to_file;
    pthread_t read_from_file;
    pthread_t report;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    struct sigaction signal_handler;
    signal_handler.sa_handler = &handle;
    sigfillset(&signal_handler.sa_mask);

    if(sigaction(SIGUSR1,&signal_handler,NULL) <0)
    {
  	  perror("Sigaction error for SIGUSR1\n");
    }
  
    if(sigaction(SIGUSR2,&signal_handler,NULL) <0)
    {
  	  perror("Sigaction error for SIGUSR2\n");
    }

 
   


    pthread_create(&write_to_file,&attr,&to_file,(void *)argv[1]);
    pthread_join(write_to_file,NULL);

    pthread_create(&read_from_file,&attr,&from_file,(void *)argv[1]);	
    pthread_kill(read_from_file,SIGUSR1);

    pthread_create(&report,&attr,&reporting,NULL);
    pthread_join(read_from_file,NULL);
    pthread_kill(report,SIGUSR2);

    pthread_exit(NULL);

}

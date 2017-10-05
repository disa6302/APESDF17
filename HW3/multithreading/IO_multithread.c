/*
* FileName        : IO_multithread.c
* Description     :	A software to implement 3 threads, one of which opens a file and writes
					data into it, a second thread to compute statistics of words, characters 
					and lines and a third thread to report the statistics. Second Thread 
					performs its action on receiving USR1 from Thread through pthread_kill.
					Similarly, Thread 3 reports the statistics on receiving a USR2 from 
					Thread 2. Atomic variables are use to track shared data structure between
					the threads. 

* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc,gdb
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>


size_t file_size = 0;
struct statistics {
	size_t words;
	size_t line;
	size_t count;
	char filename[1024]
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
	struct statistics *writeFile = (struct statistics *)arg;
	char* buff = malloc(1024*sizeof(char));
    memset(buff,0,sizeof(buff));
    FILE* fp = NULL;

	fp = fopen(writeFile->filename,"w+");
    printf("Enter your text:");
    fgets(buff, 1024*sizeof(char),stdin);
    file_size = fwrite(buff,1,strlen(buff)*sizeof(char),fp);
    printf("Number of characters written into file:%d\n",file_size);
    fclose(fp);
    pthread_exit(NULL);

}

void* from_file(void* arg)
{
	struct statistics *readFile = (struct statistics *)arg;
	while(1)
	{
	  if(processing)
      {
	    FILE* fp = NULL;

	    readFile->words=0;
	    readFile->count=0;
	    readFile->line=0;
	
		fp = fopen(readFile->filename,"r+");
		char* buff = malloc(1024*sizeof(char));
	    memset(buff,0,sizeof(buff));
	    file_size = fread(buff,1,1024*sizeof(char),fp);
	    printf("Number of characters read from file:%d\n",file_size);
	    while(*buff!=NULL)
	    {
	    	if((*buff != ' ') && (*buff != '\n')) readFile->count++;
	    	if((*buff == ' ') || (*buff == '\n')) readFile->words++;
	    	if(*buff == '\n') readFile->line++;

	    	buff++;

	    }
	    printf("Words:%d\nLines:%d\nCharacters:%d\n",(readFile->words),readFile->line,(readFile->count));
	    fclose(fp);
	    break;
	  }	
	}
	pthread_exit(NULL);
	
}

void* reporting(void* arg)
{
	struct statistics *reportFile = (struct statistics *)arg;
	while(1)
	{
		if(report)
		{
			printf("Number of words:%d\n",(reportFile->words));
			printf("Number of line:%d\n",reportFile->line);
			printf("Number of characters:%d\n",(reportFile->count));
			break;
		}
	}
	pthread_exit(NULL);
}


int main(int argc, char** argv)
{
	printf("Current PID:%d\n",getpid());
	struct statistics statistic;
	statistic.words = 0;
	statistic.count = 0;
	statistic.line = 0;

	strcpy(statistic.filename,argv[1]);
	printf("Filename:%s\n",statistic.filename);

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

 
   


    pthread_create(&write_to_file,&attr,&to_file,&statistic);
    

    pthread_create(&read_from_file,&attr,&from_file,&statistic);
    pthread_join(write_to_file,NULL);	
    pthread_kill(read_from_file,SIGUSR1);

    pthread_create(&report,&attr,&reporting,&statistic);
    pthread_join(read_from_file,NULL);
    pthread_kill(report,SIGUSR2);

    pthread_exit(NULL);

}

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

int set_end = 0;

//Flag for USR1
volatile sig_atomic_t processing = 0;

//Flag for USR2
volatile sig_atomic_t report = 0;

//To ensure nothing happens when USR2 is sent before USR1s
int flag = 0;

pthread_mutex_t val_mutex;
pthread_cond_t val_cond;

void handle(int signal)
{

    switch(signal)
    {
    	case SIGUSR1:
    			if(set_end)
    			{
					processing = 1;
    				flag = 1;
    			}
    			break;

    	case SIGUSR2:
    			if(flag)
    				report = 1;
    			else printf("\nUSR1 not called..Call it first before you can report\n");
    			break;
    }
}
void* to_file(void* arg)
{
	struct statistics *writeFile = (struct statistics *)arg;
	char ch;int i;
    FILE* fp = NULL;

	fp = fopen(writeFile->filename,"w+");
    printf("Enter your text(Enter '~' to terminate character entry):");
    while((ch=fgetc(stdin))!='~')
    {
    	ch=fgetc(stdin);
    	fputc(ch,fp);

    }
    set_end = 1;
    printf("Send a USR1 to see statistics...\n");
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

	    while(*buff!=NULL)
	    {
	    	if((*buff != ' ') && (*buff != '\n')) readFile->count++;
	    	if((*buff == ' ') || (*buff == '\n')) readFile->words++;
	    	if(*buff == '\n') readFile->line++;

	    	buff++;

	    }

	    printf("\nWords:%d\nLines:%d\nCharacters:%d\n",(readFile->words),readFile->line,(readFile->count));
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

    pthread_create(&report,&attr,&reporting,&statistic);
    
    pthread_join(write_to_file,NULL);	
    pthread_join(read_from_file,NULL);
    pthread_join(report,NULL);

    pthread_exit(NULL);

}

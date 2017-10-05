/*
* FileName        : threads.c
* Description     :	A software to show different pthread functions. This simply increments a global variable till
					a threshold is reached. A conditional signal is set that allows adding of 300 to the global 
					variable when this variable reaches a threshold. Implemented using:create(), join(), exit(), 
					self(), getattr(), getattr_default(), setattr(), mutex_init(), mutex_destroy(), mutex_lock(), 
					mutex_trylock(), mutex_unlock(), cond_init(), cond_signal(), cond_wait(), cond_destroy()

* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc,gdb
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#define NUM_THREADS 3
#define THRESHOLD 50


int global_val = 0;
pthread_mutex_t val_mutex;
pthread_cond_t val_cond;


void* global_count(void* arg)
{

	printf("Process ID: %d 	Thread ID:%u\n",getpid(),pthread_self());

	long thread_id = (long)(arg);
	printf("Global value at thread %d:%d \n",thread_id,global_val);
	for(int i=0;i<THRESHOLD;i++)
	{
		pthread_mutex_lock(&val_mutex);
		global_val++;	
		if(global_val == THRESHOLD)
		{
			printf("Count reached threshold with thread ID %d\n",thread_id);
			printf("Unblocking all the threads blocked on global_val=THRESHOLD!\n");
			pthread_cond_signal(&val_cond);

		}
		pthread_mutex_unlock(&val_mutex);
		sleep(1);
	}
	

    pthread_exit(NULL);
}

void* global_track(void* arg)
{
	printf("Process ID: %d 	Thread ID:%d\n",getpid(),pthread_self());
	long thread_id = (long)(arg);
	while(global_val < THRESHOLD)
	{
		if(pthread_mutex_trylock(&val_mutex)==0)
		{

			printf("Waiting on global_val=THRESHOLD....\n");
			pthread_cond_wait(&val_cond,&val_mutex);
			printf("Conditional signal received...updating the global value..\n");
		}
		
	}
	global_val += 300;
	printf("final global value=%d\n",global_val);
	printf("Unlocking the mutex..\n");
	pthread_mutex_unlock(&val_mutex);
	pthread_exit(NULL);
}




int main(int argc, char **argv)
{
    pthread_t threads[NUM_THREADS];

    int s;
    pthread_attr_t attr;
    s = pthread_getattr_default_np(&attr);
    if(s!=0)
    {
    	printf("Error in getattr_default()\n");
    }

    pthread_mutex_init(&val_mutex,NULL);
    pthread_cond_init(&val_cond,NULL);

    long i;
    
  	pthread_create(&threads[0],&attr,global_track,(void*)(i+1));
    for(i=1;i<NUM_THREADS;i++)
    {
    	pthread_create(&threads[i],&attr,global_count,(void*)i);
    }
    for(i=0;i<NUM_THREADS;i++)
    {
    	s = pthread_getattr_np(threads[i],&attr);
    	if(s!=0)
    	{
    		printf("Error in getattr()\n");
    	}
    }


    for(i=0;i<NUM_THREADS;i++)
    {
    	pthread_join(threads[i],NULL);
    }
    pthread_mutex_destroy(&val_mutex);
    pthread_cond_destroy(&val_cond);
    pthread_exit(NULL);
}

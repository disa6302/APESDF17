/*
* FileName        : profile_p_fork.c
* Description     :	A software to time pthread creation and fork_execv() using clock()

* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc,gdb
*Reference        : http://elixir.free-electrons.com/linux/v4.7/source/include/linux/jiffies.h
					https://www.youtube.com/watch?v=l64ySYHmMmY
*/

#include <linux/sched.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <sys/times.h>
#include <time.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>


void* do_something(void* arg)
{

	pthread_exit(NULL);
}

void pthread_profile()
{
	pthread_t tid;
	clock_t start_pthread, end_pthread;
	long t_pthread;
	
	pthread_attr_t attr;


	if(pthread_attr_init(&attr)) 
		printf("Error creating attribute for thread\n");

	start_pthread = clock();

	if(pthread_create(&tid,NULL,do_something,NULL)) 
	{
		printf("Error creating thread, cannnot be profiled\n");
		exit (-1);
	}
	end_pthread = clock();
	t_pthread = (end_pthread - start_pthread);
	printf("Time to create a pthread in CPU Clocks:%d clocks\n",t_pthread);

}

void fork_profile()
{
	clock_t start_fork,end_fork;
	long t_fork;
	start_fork = clock();

	pid_t pid = fork();
	if(pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	else if(pid == 0)
	{
		char* args[] = {"./run_test","0",NULL};
		execv(args[0],args);
	}
	wait(NULL);
	end_fork = clock();
	t_fork = (end_fork - start_fork);
	printf("Time to create a pthread in CPU Clocks:%d clocks\n",t_fork);
}


int main(int argc, char **argv)
{
	pthread_profile();
	fork_profile();
	pthread_exit(NULL);
	return 0;

    
}

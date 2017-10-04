#include <linux/sched.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <sys/times.h>
#include <time.h>
#include <pthread.h>

void* do_something(void* arg)
{
	printf("did something\n");
}

int main(int argc, char **argv)
{
    pthread_t tid;
	clock_t start_pthread, end_pthread;
	clock_t sart_fork, end_fork;
	double t_pthread, t_fork;
	
	start_pthread = clock();
	pthread_create(&tid,NULL,do_something,NULL);
	end_pthread = clock();
	t_pthread = ((double)(end_pthread - start_pthread))/CLOCKS_PER_SEC;
	printf("Time to create a pthread:%f secs\n",t_pthread);	
	
}
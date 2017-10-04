/*man7.org/linux/man-pages/man2/times.2.html*/

#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/pthread.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("KERNEL_PROFLE");
MODULE_AUTHOR("DIVYA");


void* do_something(void* arg)
{
	printf("did something\n");
}

static int __init profile_init(void)
{
    pthread_t tid;
	clock_t start_pthread, end_pthread,start_kthread,end_kthread;
	clock_t sart_fork, end_fork;
	double t_pthread, t_kthread, t_fork;
	
	start_pthread = clock();
	pthread_create(&tid,NULL,do_something,NULL);
	end_pthread = clock();
	t_pthread = ((double)(end_pthread - start_pthread))/CLOCKS_PER_SEC;
	printf("Time to create a pthread:%f secs\n",t_pthread);	
	
}

static void __exit profile_exit(void)
{
    printk(KERN_ALERT "Exiting the module");   
}
 
module_init(profile_init);
module_exit(profile_exit);



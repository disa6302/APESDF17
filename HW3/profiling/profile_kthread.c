/*
* FileName        : profile_kthread.c
* Description     :	A software to time kernel thread creation using get_jiffies_64()

* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc,gdb
*/

#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include <linux/kthread.h>
#include <linux/timer.h>
#include <linux/time.h> /*to use jiffies*/

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("KERNEL_PROFLE");
MODULE_AUTHOR("DIVYA");

struct timer_list mytimer;
static struct task_struct *thread;

int do_something(void* arg)
{
	long start_time = (long)arg;
	long end_time, final;
	printk(KERN_INFO "Testing kernel thread functionality\n");
	end_time = get_jiffies_64();
	final = end_time - start_time;
	printk(KERN_ALERT "Time value:%lu jiffies",final);
	return 0;
}

static int __init profile_init(void)
{
    char thread_name[15] = "ProfileKThread";
    long s;
	printk(KERN_INFO "Entered init module\n");
	s = get_jiffies_64();
	thread = kthread_create(do_something,(void *)s,thread_name);
	if((thread))
	{
		wake_up_process(thread);
	}
	return 0;
}

static void __exit profile_exit(void)
{
    printk(KERN_ALERT "Exiting the module");   
}
 
module_init(profile_init);
module_exit(profile_exit);



/*
* FileName        : 	kernel_timer_module.c
* Description     :	This module comprises its own init and exit
			modules and prints to kernel buffer the exit
			and entry status. It also prints out the count
			of number of times the kernel timer wakes up
* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc,gdb
* Reference	  :	Class Lecture Slides 
*/

#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include <linux/timer.h>


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("KERNEL_TIMER");
MODULE_AUTHOR("DIVYA");

/*interval	:	Kernel wake up every 500ms*/
int interval = 500;

/*timer_list_mytimer:	Structure instance to utilize the timer.h structure*/
struct timer_list mytimer;

/*count 	:	Count of number of kernel wake ups from insmod to rmmod*/
static int count = 0;

/*je,js: Start and end time of counter-time displayed in jiffies*/
unsigned long je, js;


/*Timer Call back function to restart the timer every 500msec*/
void timerFunction(unsigned long data)
{
    /*Restarting the timer*/
    mod_timer( &mytimer, jiffies + msecs_to_jiffies(interval));
    count ++;
    printk(KERN_INFO "Timer Handler called:%d\n",count);
}

/*timer init function to initialize the timer*/
static int __init timer_init(void)
{
    printk(KERN_INFO "My module inserted into kernel!!!.\n");
    js = jiffies;
    /*Starting the timer*/
    setup_timer(&mytimer, timerFunction, 0);

    mod_timer( &mytimer, jiffies + msecs_to_jiffies(interval));
 
    return 0;
}
 
/*timer exit fumction to exit the timer*/
static void __exit timer_exit(void)
{
    del_timer(&mytimer);
    je = jiffies;
    printk(KERN_INFO "Total time of operation:%lu jiffies",(je-js));
    printk(KERN_INFO "My module exited from kernel!!!\n");
}
 
module_init(timer_init);
module_exit(timer_exit);

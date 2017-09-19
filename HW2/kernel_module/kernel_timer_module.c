#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include <linux/timer.h>


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("KERNEL_TIMER");
MODULE_AUTHOR("DIVYA");

int interval = 500;
struct timer_list mytimer;
static int count = 0;
unsigned long je, js;

void timerFunction(unsigned long data)
{
    /*Restarting the timer...*/
    mod_timer( &mytimer, jiffies + msecs_to_jiffies(interval));
    count ++;
    printk(KERN_INFO "Timer Handler called:%d\n",count);
}
 
static int __init timer_init(void)
{
    printk(KERN_INFO "My module inserted into kernel!!!.\n");
    js = jiffies;
    /*Starting the timer.*/
    setup_timer(&mytimer, timerFunction, 0);
    mod_timer( &mytimer, jiffies + msecs_to_jiffies(interval));
 
    return 0;
}
 
static void __exit timer_exit(void)
{
    del_timer(&mytimer);
    je = jiffies;
    printk(KERN_INFO "Total time of operation:%lu jiffies",(je-js));
    printk(KERN_INFO "My module exited from kernel!!!\n");
}
 
module_init(timer_init);
module_exit(timer_exit);

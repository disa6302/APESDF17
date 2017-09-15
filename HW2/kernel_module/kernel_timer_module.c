#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include <linux/timer.h>
 
int g_time_interval = 500;
struct timer_list mytimer;
static int count = 0;
 
void timerFunction(unsigned long data)
{
    /*Restarting the timer...*/
    mod_timer( &mytimer, jiffies + msecs_to_jiffies(g_time_interval));
    count ++;
    printk(KERN_INFO "Timer Handler called:%d\n",count);
}
 
static int __init timer_init(void)
{
    printk(KERN_INFO "My module inserted into kernel!!!.\n");
 
    /*Starting the timer.*/
    setup_timer(&mytimer, timerFunction, 0);
    mod_timer( &mytimer, jiffies + msecs_to_jiffies(g_time_interval));
 
    return 0;
}
 
static void __exit timer_exit(void)
{
    del_timer(&mytimer);
    printk(KERN_INFO "My module exited from kernel!!!\n");
}
 
module_init(timer_init);
module_exit(timer_exit);

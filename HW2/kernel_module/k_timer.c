#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include <linux/timer.h>
 
int g_time_interval = 10000;
struct timer_list mytimer;
 
void _TimerHandler(unsigned long data)
{
    /*Restarting the timer...*/
    mod_timer( &mytimer, jiffies + msecs_to_jiffies(g_time_interval));
 
    printk(KERN_INFO "Timer Handler called.\n");
}
 
static int __init my_init(void)
{
    printk(KERN_INFO "My module inserted into kernel!!!.\n");
 
    /*Starting the timer.*/
    setup_timer(&mytimer, _TimerHandler, 0);
    mod_timer( &mytimer, jiffies + msecs_to_jiffies(g_time_interval));
 
    return 0;
}
 
static void __exit my_exit(void)
{
    del_timer(&mytimer);
    printk(KERN_INFO "My module exited from kernel!!!\n");
}
 
module_init(my_init);
module_exit(my_exit);

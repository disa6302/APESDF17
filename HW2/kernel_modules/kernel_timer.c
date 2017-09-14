#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>


struct timer_list* my_timer;

int load_init(void)
{
	printk(KERN_ALERT "Timer module Loaded");
	return 0;
}


void init_timer(struct timer_list* timer)
{
	
}

void setup_timer(struct timer_list* timer, void (*function)(unsigned long), unsigned long data))
{

}

void add_timer(struct timer_list* timer)
{

}

void mod_timer(struct timer_list* timer, unsigned long expires)
{

}

int del_timer(struct timer_list* timer)
{

}

void load_exit(void)
{
	printk(KERN_ALERT "Timer module unloaded");
}



module_init(load_init);
module_exit(load_exit);



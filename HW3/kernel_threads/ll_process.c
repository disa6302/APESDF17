/*
* FileName        : ll_process.c
* Description     :	This module provides information of the children, parent and siblings
			for the current PID by traversing the Linked List in the backward direction
* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc,gdb
* Reference	      :	Class Lecture Slides 
*/

#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/list.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Find the parents and children of current process");
MODULE_AUTHOR("DIVYA");

static int __init ll_init(void)
{
	
	struct task_struct *my_parent = current->parent;
    printk(KERN_ALERT "My Process ID:%d\n",current->pid);
    printk(KERN_ALERT "My Process State:%ld\n",current->state);
    printk(KERN_ALERT "I belong to %d thread group\n",current->tgid);
    printk(KERN_ALERT "My Parent's Process ID:%d\n",my_parent->pid);
    printk(KERN_ALERT "My Parent's Process State:%ld\n",my_parent->state);
    printk(KERN_ALERT "My parent belongs to %d thread group\n",my_parent->tgid);
 
    for_each_process(my_parent)
    {
    	printk(KERN_ALERT "Process %s with ID:%d is in state %ld\n",my_parent->comm,my_parent->pid,my_parent->state);
    }
    return 0;
}
 
/*timer exit fumction to exit the timer*/
static void __exit ll_exit(void)
{
    printk(KERN_ALERT "Exiting the module");   
}
 
module_init(ll_init);
module_exit(ll_exit);





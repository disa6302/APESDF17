/*
* FileName          : ll_process.c
* Description       : This module provides information of the children, parent and siblings
		              for the current PID by traversing the Linked List in the backward direction
* File Author Name  : Divya Sampath Kumar
* Tools used        : gcc,gdb
* Reference         : Class Lecture Slides 
*/


#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO  */
#include <linux/init.h>   /* Needed for the macros */
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

    struct task_struct *task;
    struct list_head *list;
    int number_of_threads,number_of_children;
    number_of_children = 0;
    for(task = current; task!=&init_task;task=task->parent)
	{
		  list_for_each(list,&task->children) {number_of_children++;}
		  printk(KERN_ALERT "Process %s with ID:%d is in state %ld with %d threads and %d children\n",task->comm,task->pid,task->state,number_of_children);	
	}
    return 0;
}
 
/*timer exit fumction to exit the timer*/
static void ll_exit(void)
{
    printk(KERN_ALERT "Exiting the module");   
}
 
module_init(ll_init);
module_exit(ll_exit);





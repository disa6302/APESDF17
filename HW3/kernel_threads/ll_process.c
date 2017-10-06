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
MODULE_DESCRIPTION("To find the parents and children of current process");
MODULE_AUTHOR("DIVYA");

static int __init ll_init(void)
{
    struct task_struct *task;
    //to find number of children
    struct list_head *list;
    int number_of_children = 0;
    printk(KERN_ALERT "Entered Kernel Module!");

    //traversing from current task to init_task
    for(task = current; task!=&init_task;task=task->parent)
	{
        //Listing number of children for each traversed process
	   list_for_each(list,&task->children) {number_of_children++;}
	   printk(KERN_ALERT "Process %s with ID:%d is in state %ld with %d children\n",task->comm,task->pid,task->state,number_of_children);
       number_of_children = 0;	
	}
    return 0;
}
 

static void __exit ll_exit(void)
{
    printk(KERN_INFO "My module exited from kernel!!!\n");
}
 
module_init(ll_init);
module_exit(ll_exit);





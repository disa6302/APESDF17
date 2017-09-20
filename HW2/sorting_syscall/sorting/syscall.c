/*
* FileName        : 	syscall.c
* Description     :	A system call to perform a simple sort
			on an input buffer. Care is taken to 
			notify the user if size is not >=256
			or the input and output buffer are of
			invalid value. The case of invalid copy
			to or from user space and kernel space
			is handled through appropriate Error ENUMS

* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc
* Reference	  :	Class Lectures, Kernel Development TextBook
*/

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <uapi/asm-generic/errno-base.h>
#include <linux/gfp.h>
#include <linux/slab.h>


/* Function to perform simple sort of incoming buffer */

void sorting_buffer(int32_t* in_buffer, int32_t size, int32_t* sort_buffer)
{
    int32_t i,j;
    int32_t temp;
    
    
    for(i=0;i<size;i++)
    {
	for(j=i+1;j<size;j++)
	{
	    if(*(in_buffer+i) < *(in_buffer+j))
	    {
		temp  = *(in_buffer+i);
		*(in_buffer+i) = *(in_buffer+j);
		*(in_buffer+j) = temp;
	    }
	}
    }
}


/*SYSCALL Definition for sort systemcall */
SYSCALL_DEFINE3(sort,int32_t*, in_buffer, int32_t, size, int32_t*, sort_buffer)
{
    
    /* ALlocating Kernel space buffer*/
    int32_t *k_input_buffer = kmalloc(sizeof(int32_t)*size, GFP_KERNEL);

    /*Variables to check success of copy_to_user() and copy_from_user()*/
    unsigned long check_copy_from_user = 0;
    unsigned long check_copy_to_user = 0;


    printk(KERN_ALERT "Entered the Sort System Call (333)...");
    printk(KERN_ALERT "Size of buffer:%i",size);
	
    if(size <256)
    {
	printk(KERN_ALERT "Buffer size must be a minimum of 256");
	printk(KERN_ALERT "Sort Syscall exit with return status %d",EINVAL);
	return EINVAL;
    }
    if(in_buffer==NULL || sort_buffer == NULL)
    {
	printk(KERN_ALERT "Invalid Memory Access for input buffer or output buffer...");
	printk(KERN_ALERT "Sort Syscall exit with return status %d",EFAULT);
        return EFAULT;
    }
    if(k_input_buffer==NULL)
    {
	printk(KERN_ALERT "Invalid Memory Access for kernel buffer...");
	printk(KERN_ALERT "Sort Syscall exit with return status %d",EFAULT);
        return EFAULT;
    }
    
    /*If check_copy_from_user() returns a 0, memcpy is successful.*/    
    check_copy_from_user = copy_from_user(k_input_buffer,in_buffer,sizeof(int32_t)*size);


    if(!(check_copy_from_user)) 
	printk(KERN_ALERT "Copy from user space to kernel space successful!\n");
    else 
    {	
	printk(KERN_ALERT "Unsuccessful copy from user space to kernel space.\n");
	return EFAULT;
    }

    sorting_buffer(k_input_buffer,size,sort_buffer);

     /*If check_copy_to_user() returns a 0, memcpy is successful.*/  
    check_copy_to_user = copy_to_user(sort_buffer,k_input_buffer,sizeof(int32_t)*size);
   
    if(!(check_copy_to_user)) 
    	printk(KERN_ALERT "Copy to user space from kernel space successful!\n");
    else 
    {
	printk(KERN_ALERT "Unsuccessful copy to user space from kernel space.\n");
	return EFAULT;
    }
  
    printk(KERN_ALERT "Array Sorted Successfully!\n");
    printk(KERN_ALERT "End of Sort System Call (333)...");
    kfree(k_input_buffer);
    return 0;
}

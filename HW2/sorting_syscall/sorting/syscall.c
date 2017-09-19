#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <uapi/asm-generic/errno-base.h>
#include <linux/gfp.h>
#include <linux/slab.h>

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
SYSCALL_DEFINE3(sort,int32_t*, in_buffer, int32_t, size, int32_t*, sort_buffer)
{
    int32_t *k_input_buffer = kmalloc(sizeof(int32_t)*size, GFP_KERNEL);
    unsigned long check_copy_from_user = 0;
    unsigned long check_copy_to_user = 0;
    printk(KERN_ALERT "Entered the Sort System Call (333)...");
    printk(KERN_ALERT "Size of buffer:%i",size);

    if(!(size) || size < 0)
    {
	printk(KERN_ALERT "Buffer size less than or equal to 0");
	printk(KERN_ALERT "Sort Syscall exit with return status %d",EINVAL);
	return EINVAL;
    }
    if(in_buffer==NULL)
    {
	printk(KERN_ALERT "Invalid Memory Access for input buffer...");
	printk(KERN_ALERT "Sort Syscall exit with return status %d",EFAULT);
        return EFAULT;
    }
    if(sort_buffer==NULL)
    {
	printk(KERN_ALERT "Invalid Memory Access for output sort buffer...");
	printk(KERN_ALERT "Sort Syscall exit with return status %d",EFAULT);
        return EFAULT;
    }
    
    
    
    check_copy_from_user = copy_from_user(in_buffer,k_input_buffer,sizeof(int32_t)*size);
    if(!(check_copy_from_user)) 
	printk(KERN_ALERT "Copy from user space to kernel space successful!\n");
    else 
	printk(KERN_ALERT "Unsuccessful copy from user space to kernel space.\n");

    sorting_buffer(k_input_buffer,size,sort_buffer);

    check_copy_to_user = copy_to_user(sort_buffer,k_input_buffer,sizeof(int32_t)*size);
    if(!(check_copy_to_user)) 
    	printk(KERN_ALERT "Copy to user space from kernel space successful!\n");
    else 
	printk(KERN_ALERT "Unsuccessful copy to user space from kernel space.\n");

    printk(KERN_ALERT "Array Sorted Successfully!\n");
    printk(KERN_ALERT "End of Sort System Call (333)...");
    return 0;
}

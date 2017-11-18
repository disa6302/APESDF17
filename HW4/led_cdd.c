#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LED character device drivers");
MODULE_AUTHOR("DIVYA");


int led_open (struct inode *node, struct file *fp)
{
	printk(KERN_ALERT "Entering %s module",__FUNCTION__);
	/*Implement file open-user gives file path and passes file descriptor-this routine must deal with error handling*/
	return 0;
}
ssize_t led_read (struct file *fp, char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "Entering %s module",__FUNCTION__);
	/*Include functionalities to read current state-Period, Duty Cycle, ON/OFF or read particular state*/
	return 0;
}
ssize_t led_write (struct file *fp, const char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "Entering %s module",__FUNCTION__);
	/*Include functionalities to write state-Frequency, Duty Cycle, ON/OFF*/
	
	//fwrite("0",sizeof(char),1, LED);
	//fclose(LED);
	return length;
}
int led_close (struct inode *node, struct file *fp)
{
	printk(KERN_ALERT "Entering %s module",__FUNCTION__);
	/*Implement file close and error handling*/
	return 0;
}

struct file_operations led_op = {
	.owner = THIS_MODULE,
	.open = led_open,
	.read = led_read,
	.write = led_write,
	.release = led_close,
};

int led_init(void)
{
	printk(KERN_ALERT "Initializing %s module",__FUNCTION__);
	//To register LED as a character device
	register_chrdev(240,
					"led_drv",
					&led_op);
	return 0;

}

void led_exit(void)
{
	printk(KERN_ALERT "Exiting %s module",__FUNCTION__);	
	unregister_chrdev(240,
					"led_drv");
}

module_init(led_init);
module_exit(led_exit);
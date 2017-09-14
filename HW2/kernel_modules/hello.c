#include <linux/init.h>
#include <linux/module.h>

int hello_init(void)
{
	printk(KERN_ALERT "Entering my first kernel module");
	return 0;
}

void hello_exit(void)
{
	printk(KERN_ALERT "Exiting my first kernel module");
}

module_init(hello_init);
module_exit(hello_exit);



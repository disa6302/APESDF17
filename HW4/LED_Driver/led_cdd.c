#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gfp.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/timer.h>

#define CLASSNAME "BBG_LED"
#define DEVICENAME "LED"
#define LED_ON 1
#define LED_OFF 0
#define FREQ_VAL ':'

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LED character device drivers");
MODULE_AUTHOR("DIVYA");

static int gpioUSRLED3 = 56;
//static int ledState = LED_OFF;
static int majornumber = 0;
static int duty=50;

static struct class* ledDriverClass = NULL;
static struct device* ledDriverDevice = NULL;
static struct timer_list timer_on;

static bool ledstate;
static int f_int;


static int led_open (struct inode *node, struct file *fp)
{
	printk(KERN_ALERT "Entering %s module",__FUNCTION__);

	/*Implement file open-user gives file path and passes file descriptor-this routine must deal with error handling*/
	return 0;
}

ssize_t led_read (struct file *fp, char __user *buffer, size_t length, loff_t *offset)
{
	
	printk(KERN_ALERT "Entering %s module",__FUNCTION__);
	if(ledstate)
		printk(KERN_INFO "LED in on state");
	else
		printk(KERN_INFO "LED in off state");
	return 0;
}


void blink(unsigned long data)
{
	int ret;
        printk(KERN_ALERT "Entered module\nth ledstate:%d",ledstate);
        ledstate=!ledstate;	
	printk(KERN_ALERT "New ledstate:%d",ledstate);
	gpio_set_value(gpioUSRLED3,ledstate);
	ret = mod_timer(&timer_on,jiffies+msecs_to_jiffies((int)(f_int-(duty/(f_int*100)))*1000));
	//gpio_set_value(gpioUSRLED3,ledstate);
}

void set_frequency_led(char *freq)
{
	sscanf(freq,"%d",&f_int);
	printk(KERN_ALERT "Value:%d\n",f_int);
	//ontime= (int)(duty/(f_int*100));
	//printk(KERN_ALERT "Ontime:%d\n",ontime);
	//printk(KERN_ALERT "Offtime:%d\n",offtime);
	//offtime =(int)(f_int - ontime);
	ledstate = LED_ON;

	gpio_set_value(gpioUSRLED3,ledstate);
	mod_timer(&timer_on,jiffies+msecs_to_jiffies((int)(duty/(100*f_int))*1000));
        //gpio_set_value(gpioUSRLED3,ledstate);

	
	

	//printk(KERN_ALERT "Timer value:%d\n",f_int);
	//mdelay(f_int*1000);
	//gpio_set_value(gpioUSRLED3,LED_OFF);
	//mdelay(f_int*1000);

	
}

ssize_t led_write (struct file *fp, const char *buffer, size_t length, loff_t *offset)
{

	char *kbuf,*strfreq,*strnum,*strdummy;
	unsigned long status = 0;
	
	if(length<=0)
	{
		printk(KERN_ERR "Invalid length\n");
		return -EINVAL;
	}

	kbuf = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	strfreq = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	strnum = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	strdummy = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	if(!kbuf || !strfreq || !strnum || !strdummy) 
	{
		printk(KERN_ERR "Error allocating\n");
		return -EINVAL;
	}

	status = copy_from_user(kbuf,buffer,(sizeof(char)*length));
	strncpy(strdummy,kbuf,strlen(kbuf));
        strfreq = strsep(&strdummy,":");
	strnum = strsep(&strdummy,":");
	printk(KERN_ALERT "%s %s",strfreq,strnum);
	if(status !=0)
	{
		printk(KERN_ERR "Error copying from user space with status %ld\n",status);
		return -EINVAL;
	}

	printk(KERN_ALERT "Entering %s module with option %s\n",__FUNCTION__,kbuf);
	
	if(!strncmp(kbuf,"ON",2))
	{
		gpio_set_value(gpioUSRLED3,LED_ON);
		printk(KERN_ALERT "Setting LED On");
	}

	else if(!strncmp(kbuf,"OFF",3))
	{

		gpio_set_value(gpioUSRLED3,LED_OFF);
		printk(KERN_ALERT "Setting LED Off");
	}
	else if(!strncmp(strfreq,"FREQ",4))
	{
		printk(KERN_ALERT "Setting frequency for led\n");
		set_frequency_led(strnum);
	}
	else
		printk(KERN_INFO "Invalid request from user\n");

	
	return 0;
}

static int led_close (struct inode *node, struct file *fp)
{
	printk(KERN_ALERT "Entering %s module,closed driver",__FUNCTION__);
	return 0;
}


struct file_operations led_op = {
	.owner = THIS_MODULE,
	.open = led_open,
	.read = led_read,
	.write = led_write,
	.release = led_close,
};

static int __init led_init(void)
{
	
	int status=1;
	setup_timer(&timer_on,blink,0);
	printk(KERN_ALERT "Initializing %s module",__FUNCTION__);
	//To register LED as a character device
	if(!gpio_is_valid(gpioUSRLED3))
	{
		printk(KERN_ERR "Invalid GPIO Selection");
		return -ENODEV;
	}


	//Allocate a GPIO
	gpio_request(gpioUSRLED3, "sysfs");

	//Set GPIO Direction to output-returns 0 on success
	status = gpio_direction_output(gpioUSRLED3,LED_OFF);
        


	//Add GPIO_24 to /sys/class/gpio to make it available to sysfs interface
	gpio_export(gpioUSRLED3,false); 

	//Verify LED is in ON State as set by gpio_direction_output
	printk(KERN_INFO "GPIO TESTING: The LED state is : %d\n" ,gpio_get_value(gpioUSRLED3));

	//Set Major Number field in register_chrdev to 0 to allow dynamic allocation of major number
	majornumber = register_chrdev(0,
					DEVICENAME,
					&led_op);

	if(majornumber<0)
	{
		printk(KERN_ERR "Error registering character device driver\n");
		return 0;
	}

	
	ledDriverClass = class_create(THIS_MODULE,CLASSNAME);
	if(IS_ERR(ledDriverClass))
	{
		unregister_chrdev(majornumber,DEVICENAME);
		printk(KERN_ERR "Failed to register device class\n");
		return -EINVAL;
	}


	ledDriverDevice = device_create(ledDriverClass,NULL,MKDEV(majornumber,0),NULL,DEVICENAME);
	if(IS_ERR(ledDriverDevice))
	{
		unregister_chrdev(majornumber,DEVICENAME);
		printk(KERN_ERR "Failed to register device class\n");
		return -EINVAL;
	}	

	return 0;

}

static void __exit led_exit(void)
{
	printk(KERN_ALERT "Exiting %s module",__FUNCTION__);	

	gpio_set_value(gpioUSRLED3,LED_OFF);
	gpio_unexport(gpioUSRLED3);
	gpio_free(gpioUSRLED3);

	device_destroy(ledDriverClass,MKDEV(majornumber,0));
	class_unregister(ledDriverClass);
	class_destroy(ledDriverClass);
	unregister_chrdev(majornumber,
			DEVICENAME);
	del_timer(&timer_on);
}

module_init(led_init);
module_exit(led_exit);

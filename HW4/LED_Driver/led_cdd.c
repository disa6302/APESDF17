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
static int duty_val = 0;
static int req_onoff = 0;
static int req_freq = 0;
static int req_all = 0;
static int freq_set = 0;
static int req_duty = 0;

static struct class* ledDriverClass = NULL;
static struct device* ledDriverDevice = NULL;
static struct timer_list timer_on;

static bool ledstate;
static int f_int;


static int led_open (struct inode *node, struct file *fp)
{
	printk(KERN_ALERT "Entering %s module",__FUNCTION__);

	return 0;
}

ssize_t led_read (struct file *fp, char __user *buffer, size_t length, loff_t *offset)
{
	
	printk(KERN_ALERT "Entering %s module",__FUNCTION__);
	char *kbuf;
        int ret;
	kbuf = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	
	if(!kbuf)
	{
		printk(KERN_ERR "Error allocating memory\n");
		return -EINVAL;
	}
	if(req_all)
	{
		sprintf(kbuf,"%d %d %d",ledstate,f_int,duty_val);
		req_all = 0;
	}
	else if(req_onoff)
	{
		sprintf(kbuf,"%d",ledstate);
		req_onoff = 0;
	}
	else if(req_freq)
	{
		sprintf(kbuf,"%d",f_int);
		req_freq = 0;
	}
	else if(req_duty)
	{
		sprintf(kbuf,"%d",duty_val);
		req_duty = 0;
	}

	printk(KERN_ALERT "Value state:%s\n",kbuf);
	
	ret = copy_to_user(buffer,kbuf,strlen(kbuf)*sizeof(char));
	if(ret) 
	{
		printk(KERN_ERR "Failed copy\n");
		return -EINVAL;
	}
	return 0;
}


void blink(unsigned long data)
{
	int ret;
    printk(KERN_ALERT "Entered module with the ledstate:%d",ledstate);
    ledstate=!ledstate;	
	printk(KERN_ALERT "New ledstate:%d",ledstate);
	gpio_set_value(gpioUSRLED3,ledstate);
	ret = mod_timer(&timer_on,jiffies+msecs_to_jiffies((int)(f_int-(duty_val/(f_int*100)))*1000));
}

void set_frequency_led(char *freq,int duty)
{
	printk(KERN_ALERT "Freqeuncy set to:%s",freq);
	sscanf(freq,"%d",&f_int);
	duty_val = duty;
	printk(KERN_ALERT "Value:%d %d\n",f_int,duty_val);
	ledstate = LED_ON;

	gpio_set_value(gpioUSRLED3,ledstate);
	mod_timer(&timer_on,jiffies+msecs_to_jiffies((int)(duty_val/(100*f_int))*1000));
      
}

ssize_t led_write (struct file *fp, const char *buffer, size_t length, loff_t *offset)
{

	char *kbuf,*strfreq,*strnumf,*strfd,*strdd,*strduty,*strnumd;
	unsigned long status = 0;
	
	if(length<=0)
	{
		printk(KERN_ERR "Invalid length\n");
		return -EINVAL;
	}

	kbuf = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	strfreq = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	strnumf = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	strduty = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	strnumd = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	strfd = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	strdd = (char*)kmalloc(sizeof(char)*length,GFP_KERNEL);
	if(!kbuf || !strfreq || !strfd || !strdd || !strduty || !strnumd || !strnumf) 
	{
		printk(KERN_ERR "Error allocating\n");
		return -EINVAL;
	}

	status = copy_from_user(kbuf,buffer,(sizeof(char)*length));
	strncpy(strfd,kbuf,strlen(kbuf));
    strfreq = strsep(&strfd,":");
	strnumf = strsep(&strfd,":");

	strncpy(strdd,kbuf,strlen(kbuf));
    strduty = strsep(&strdd,":");
	strnumd = strsep(&strdd,":");

	if(status !=0)
	{
		printk(KERN_ERR "Error copying from user space with status %ld\n",status);
		return -EINVAL;
	}

	printk(KERN_ALERT "Entering %s module with option %s\n",__FUNCTION__,kbuf);
	
	if(!strncmp(kbuf,"ON",2))
	{
		ledstate = LED_ON;
		gpio_set_value(gpioUSRLED3,ledstate);
		printk(KERN_ALERT "Setting LED On");
	}

	else if(!strncmp(kbuf,"OFF",3))
	{
		ledstate = LED_OFF;

		gpio_set_value(gpioUSRLED3,ledstate);
		printk(KERN_ALERT "Setting LED Off");
	}
	else if(!strncmp(strfreq,"FREQ",4))
	{
		freq_set = 1;
		printk(KERN_ALERT "Setting frequency for led\n");
		set_frequency_led(strnumf,duty);
	}

	else if(!strncmp(strduty,"DUTY",4))
	{
		printk(KERN_ALERT "Setting duty cycle for led:%s\n",strnumd);
		sscanf(strnumd,"%d",&duty_val);
		if(!freq_set)
		{
			set_frequency_led("10",duty_val);
			freq_set = 0;
		}
		else set_frequency_led(strnumf,duty_val);
	}

	else if(!strncmp(kbuf,"REQONOFF",6))
	{
		printk(KERN_INFO "Requested LED State\n");
		req_onoff = 1;
	}
	else if(!strncmp(kbuf,"REQFREQ",7))
	{
		printk(KERN_INFO "Requested Frequency\n");
		req_freq = 1;
	}
	else if(!strncmp(kbuf,"REQALL",6))
	{
		printk(KERN_INFO "Requested All variables\n");
		req_all = 1;
	}
	else if(!strncmp(kbuf,"REQDUTY",7))
	{
		printk(KERN_INFO "Requested Duty Cycle\n");
		req_duty = 1;
	}
	else printk(KERN_INFO "Invalid option\n");

	
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

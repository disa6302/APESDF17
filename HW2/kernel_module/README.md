STEPS TO CREATE AND EXECUTE THE TIMER KERNEL MODULE:


1.  Go to ~/APESDF17/HW2/kernel_module

2.  Create the module: kernel_timer_module.c

3.  Create a Makefile to generate the .ko file

4.  Run make command

5.  Run: sudo insmod ./kernel_timer_module.ko

6.  In another terminal run: tail -f /var/log/syslog to monitor the kernel module wake up every 500msec.

7.  Perform: lsmod | grep kernel_timer_module to verify the loading of the module

8.  Run: sudo rmmod kernel_timer_module to exit the module

9.  To make the module accessible from any directory:
    cp -r kernel_module /lib/modules/4.12.10/kernel/driver 
    
10. Run: sudo depmod -a to create a makefile type dependency file

11. Run modinfo kernel_timer_module from any directory to get the module details

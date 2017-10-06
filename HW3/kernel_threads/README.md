STEPS TO CREATE AND EXECUTE Linked List Traverse module:


1.  Go to ~/APESDF17/HW3/kernel_threads

2.  Create the module: ll_process.c

3.  Create a Makefile to generate the .ko file

4.  Run make command

5.  Run: sudo insmod ./ll_process.ko

6.  In another terminal run: tail -f /var/log/syslog and check process tree for current process getting displayed.

7.  Run: sudo rmmod ll_process to exit the module


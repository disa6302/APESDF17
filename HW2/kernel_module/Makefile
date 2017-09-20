/*
# FileName        : 	Makefile
# Description     :	To build and clean the kernel module
# File Author Name:	Divya Sampath Kumar
# Reference	  :	Class Lecture Slides 


obj-m := kernel_timer_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

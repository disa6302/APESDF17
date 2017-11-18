# FileName        : 	Makefile
# Description     :	To build and clean the kernel module
# File Author Name:	Divya Sampath Kumar
# Reference	  :	Class Lecture Slides 


obj-m := led_cdd.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# FileName        : 	Makefile
# Description     :	To build and clean the kernel module
# File Author Name:	Divya Sampath Kumar
# Reference	  :	Class Lecture Slides 


obj-m := chase.o
#KERNELDIR ?= ../linux
all:
	make  -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
#	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

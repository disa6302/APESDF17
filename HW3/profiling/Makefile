

# FileName        : 	Makefile
# Description     :	Generates executable profile in ~/APESDF17/HW3/profiling

# File Author Name:	Divya Sampath Kumar
# Reference	  :	http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/example-1/Makefile 




# FileName        : 	Makefile
# Description     :	To build and clean the kernel module
# File Author Name:	Divya Sampath Kumar
# Reference	  :	Class Lecture Slides 


obj-m := profile_kthread.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

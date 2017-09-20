# APESDF17
Advanced Practical Embedded Software Design

Execution Steps followed for Syscall Problem #2

1.  Go to /usr/src/linux-4.12.10/arch/x86/entry/syscalls/syscall_64.tbl

2.  Add the following line at the end: 
    333     common     sort     sys_sort
   
3.  Create sorting directory in /usr/src/linux-4.12.10/

4.  Create syscall.c file and equivalent makefile

5.  Add this directory in /usr/src/linux-4.12.10/Makefile as:
    core-y := sorting/
   
6.  Create a user space sort_test.c application in ~/APESDF17/HW2/sorting_syscall

7.  Run: sudo make -j4

8.  Run sudo make install

9.  reboot

10. Go to ~/APESDF17/HW2/sorting_syscall and compile to generate sort_test executable

11. Check the syscall log using : 
    tail -f /var/log/syslog







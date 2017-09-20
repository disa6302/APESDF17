# APESDF17
Advanced Practical Embedded Software Design

Execution Steps followed for Syscall Problem #2

1. Entry into the Syscall Table: cd /usr/src/linux-4.12.10/arch/x86/entry/syscalls/syscall_64.tbl
   Add the following line before the X32 Specific Section: 333	common	sort sys_sort

2. Create the directory: sorting in /usr/src/linux-4.12.10 

3. Within this directory: Create syscall.c file







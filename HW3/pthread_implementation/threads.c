#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUMTHREADS 4
/*To implement: create(), join(), exit(), self(), getattr(), getattr_default(),
  setattr(), mutex_init(), mutex_destroy(), mutex_lock(), mutex_trylock(), 
  mutex_unlock(), cond_init(), cond_signal(), cond_wait(), cond_destroy()*/

long product = 1;
void* fact(void* arg)
{
    long fval = (long *)arg;
    while(fval!=0)
    {
	product *= fval;
	fval--;
    }
    pthread_exit(0);
}
/*main function caling the factorial*/

int main(int argc, char **argv)
{
    pthread_t 
}

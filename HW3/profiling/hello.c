#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char argv[])
{
	clock_t start_time = argv[1]-'0';
	printf("start_time%d",start_time);
	clock_t end_time = (long)(argv[2]);

	double final_time;
	start_time = clock();
	printf("Hello world! Testing fork and exec!\n");
	end_time = clock();
	final_time = (double)(end_time-start_time);
	printf("Final Time%f\n",final_time);
	return 0;
}

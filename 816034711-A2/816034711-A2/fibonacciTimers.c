#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <linux/types.h>
#include <stdlib.h>
#include <sys/types.h>


int wall_time = 0;
int cpu_time = 0;
int user_time = 0;
int kernel_time = 0;

struct itimerval realTime;
struct itimerval virtTime;
struct itimerval profTime;

void initItimer()
{
	realTime.it_interval.tv_sec = 1;
	realTime.it_interval.tv_usec = 0;
	realTime.it_value.tv_sec = 1;
	realTime.it_value.tv_usec = 0;
	
	virtTime.it_interval.tv_sec = 1;
	virtTime.it_interval.tv_usec = 0;
	virtTime.it_value.tv_sec = 1;
	virtTime.it_value.tv_usec = 0;
	
	profTime.it_interval.tv_sec = 1;
	profTime.it_interval.tv_usec = 0;
	profTime.it_value.tv_sec = 1;
	profTime.it_value.tv_usec = 0;
	
	setitimer(ITIMER_REAL, &realTime, NULL);
	setitimer(ITIMER_VIRTUAL, &virtTime, NULL);
	setitimer(ITIMER_PROF, &profTime, NULL);
}

void myHandler(int signal)
{
	if(signal == 14)
		wall_time++;
	
	if(signal == 26)
		cpu_time++;
		
	if(signal == 27)
		user_time++;
}

int fib(int num)
{
	if(num < 3)
		return 1;
		
	else 
		return fib(num-1) + fib(num-2);
}


int main(int argc, char *argv[])
{	
	initItimer();
	
	int seq1, seq2, seq3;
	seq1 = atoi(argv[2]);
	seq2 = atoi(argv[3]);
	seq3 = atoi(argv[1]);
	
	pid_t pid1,pid2;
	
	signal(SIGALRM, myHandler);
	signal(SIGVTALRM, myHandler);
	signal(SIGPROF, myHandler);
	
	/*setitimer(ITIMER_REAL, &v, NULL);
	setitimer(ITIMER_VIRTUAL, &v, NULL);
	setitimer(ITIMER_PROF, &v, NULL);*/ // for parent timer since parent should be running upon execution
	
	pid1 = fork();
	
	if(pid1 == 0)
	{
		initItimer();
		printf("--[Child 1] fibonacci (%d) = %d\n", seq1, fib(seq1));
		
		getitimer(ITIMER_REAL, &realTime);
		printf("Wall Time: %d seconds, %ld microseconds\n", wall_time, 1000000-realTime.it_value.tv_usec);
		
		getitimer(ITIMER_PROF ,&profTime);
		printf("CPU Time: %d seconds, %ld microseconds\n", cpu_time, 1000000-profTime.it_value.tv_usec);
		
		long temp = 1000000-profTime.it_value.tv_usec;
		
		getitimer(ITIMER_VIRTUAL, &virtTime);
		printf("User Time: %d seconds, %ld microseconds\n", user_time, 1000000-virtTime.it_value.tv_usec);
		
		kernel_time = cpu_time - user_time;
		long kernel_micro = (temp - (1000000-virtTime.it_value.tv_usec));
		
		printf("Kernel Time: %d seconds, %ld\n", kernel_time, kernel_micro);
		
		wall_time = 0;
		cpu_time = 0;
		user_time = 0;
		
		exit(0);
	}
	
	pid2 = fork();
	
	if(pid2 == 0)
	{
		initItimer();
		
		printf("--[Child 2] fibonacci (%d) = %d\n", seq2, fib(seq2));
		
		getitimer(ITIMER_REAL, &realTime);
		printf("Wall Time: %d seconds, %ld microseconds\n", wall_time, 1000000-realTime.it_value.tv_usec);
		
		getitimer(ITIMER_PROF ,&profTime);
		printf("CPU Time: %d seconds, %ld microseconds\n", cpu_time, 1000000-profTime.it_value.tv_usec);
		
		long temp = 1000000-profTime.it_value.tv_usec;
		
		getitimer(ITIMER_VIRTUAL, &virtTime);
		printf("User Time: %d seconds, %ld microseconds\n", user_time, 1000000-virtTime.it_value.tv_usec);
		
		kernel_time = cpu_time - user_time;
		long kernel_micro = (temp - (1000000-virtTime.it_value.tv_usec));
		
		printf("Kernel Time: %d seconds, %ld\n", kernel_time, kernel_micro);
		
		wall_time = 0;
		cpu_time = 0;
		user_time = 0;
		
		exit(0);
	}
	
	int status1, status2;
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	
	printf("--[Parent] fibonacci (%d) = %d\n", seq3, fib(seq3));
	
	getitimer(ITIMER_REAL, &realTime);
	printf("Wall Time: %d seconds, %ld microseconds\n", wall_time, 1000000-realTime.it_value.tv_usec);
	
	getitimer(ITIMER_PROF ,&profTime);
	printf("CPU Time: %d seconds, %ld microseconds\n", cpu_time, 1000000-profTime.it_value.tv_usec);
	
	long temp = 1000000-profTime.it_value.tv_usec;
	
	getitimer(ITIMER_VIRTUAL, &virtTime);
	printf("User Time: %d seconds, %ld microseconds\n", user_time, 1000000-virtTime.it_value.tv_usec);
	
	kernel_time = cpu_time - user_time;
	long kernel_micro = (temp - (1000000-virtTime.it_value.tv_usec));
	
	printf("Kernel Time: %d seconds, %ld\n", kernel_time, kernel_micro);
	
	wall_time = 0;
	cpu_time = 0;
	user_time = 0;
		
		exit(0);
	return 0;
}//meep



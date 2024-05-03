#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM 3

int factorial = 1;
int square;
int half;
int checkHalf;

void *makeFactorial(void *param)
{
	int lim = atoi(param);
	
	for(int i=1; i<=lim; i++)
		factorial *= i;
		
	pthread_exit(0);
}

void *makeSquare(void *param)
{
	int num = atoi(param);
	square = num*num;
	
	pthread_exit(0);
}	

void *makeHalf(void *param)
{
	int num = atoi(param);
	if(num % 2 == 0)
	{
		half = num/2;
		checkHalf = 1;
	}
		
	else 
		checkHalf = -1;
		
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	pthread_t tid[NUM];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	pthread_create(&tid[0], &attr, makeFactorial, argv[1]);
	pthread_create(&tid[1], &attr, makeSquare, argv[2]);
	pthread_create(&tid[2], &attr, makeHalf, argv[3]);
	
	pthread_join(tid[0], NULL);
	printf("Factorial value of %d is: %d\n", atoi(argv[1]), factorial); 
	
	pthread_join(tid[1], NULL);
	printf("The square value of %d is: %d\n", atoi(argv[2]), square);
	
	pthread_join(tid[2], NULL);
	
	if(checkHalf == 1)
		printf("The half value of %d is: %d\n", atoi(argv[3]), half);
	
	if(checkHalf == -1)
		printf("VALUE ODD RAH\n");
		
	return 0;
}

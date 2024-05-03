#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM 3

int last;
int ballsLeft;
int evenBallsRemoved[3] = {0};
int oddBallsRemoved[3] = {0};
pthread_mutex_t lock;

void *removeBall(void *param)
{
	int ID = *(int*)param;
	printf("Current thread is: %d\n", ID+1);
	
	pthread_mutex_lock (&lock);
	
	if(ballsLeft <= 0)
	{
		pthread_mutex_unlock(&lock);
		pthread_exit(0);
	}
	
	ballsLeft -= 1;
	
	if(ballsLeft % 2 ==0)
		evenBallsRemoved[ID]++;
		
	else 
		oddBallsRemoved[ID]++;
		
	if(ballsLeft == 0);
		last = ID+1;
		
	pthread_mutex_unlock (&lock);
	
	pthread_exit(0);
}


int main(int argc, char *argv[])
{
	if(atoi(argv[1]) % 2 != 0)
	{
		printf("ODD NUMBER OF BALLS\n");
		exit(1);
	}
	
	else
	{
		ballsLeft = atoi(argv[1]); // assign balls left to val from command line
		
		pthread_t tID[3];
		pthread_mutex_init(&lock, NULL);
		
		int particID[3];
		
		for(int x=0; x<3; x++)
			particID[x] = x;
			
		pthread_attr_t attr;
		pthread_attr_init (&attr);
		
		while(ballsLeft > 0)
		{
			for(int i=0; i<NUM; i++)
				pthread_create(&tID[i], &attr, removeBall, (void*) &particID[i]);
				
			for(int j=0; j<NUM; j++)
				pthread_join (tID[j], NULL);
		}
		
		printf("Thread 1 removed: %d even balls and %d odd balls.\n", evenBallsRemoved[0], oddBallsRemoved[0]);
		printf("Thread 2 removed: %d even balls and %d odd balls.\n", evenBallsRemoved[1], oddBallsRemoved[1]);
		printf("Thread 3 removed: %d even balls and %d odd balls.\n", evenBallsRemoved[2], oddBallsRemoved[2]);
		printf("Last ball removed by %d\n", last);
		
		pthread_mutex_destroy(&lock);
	}
}

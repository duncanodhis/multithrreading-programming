#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include<time.h>
#include<stdlib.h>
#include <semaphore.h>
#define threads 2

struct myParams { pthread_t id; int start; int end;};


pthread_mutex_t mutex;
struct myParams params[threads];

void *sumofnum(void *value) 
{
struct myParams *myParam = (struct myParams *)value;
int up=9,low=0,r;
int j,myArray[1000000];//myArray was small that brought the segment fault signal
int  sum = 0;//the global variable sum
	srand(time(0));
for (int i=myParam->start;i<myParam->end;i++)
{

    
	for( j=0;j<1000000;j++)
	{
	pthread_mutex_lock(&mutex);	//locks A Thread
	
	
     r=(rand()%(up-(low+1))+low);//random number generator
    
    myArray[j]=r;
    sem_t mySem;//name of the semaphore 
    sem_init(&mySem, 0,0);//creates/initializes a semaphore with global variable
    sum+=myArray[j];
    
    sem_post(&mySem);//increment the semaphore
    sem_wait(&mySem);//semaphore lock
    sem_destroy(&mySem);//destroys the semaphore

   pthread_mutex_unlock(&mutex);//unlock A Thread
   
	} 
	

}
printf("%d\n",sum);
return NULL;
}

int main (int argc, char **argv) 
{
pthread_mutex_init(&mutex,NULL);
for (int i=0;i<threads;i++) 
{
params[i].start = 2*i;
params[i].end = 2*(i+1);
pthread_create(&params[i].id, NULL,sumofnum, &params[i]);//creates our threads
sleep(3);
}
sleep(3);

return 0;
}


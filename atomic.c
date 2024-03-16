#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

// atomic int
_Atomic int atomic_count = 0;
// have data races
int count = 0;
// mutex int
int mutexcount = 0;
pthread_mutex_t mutex; 
// the function which will run in the thread
void* runner()
{
    for(int i = 0; i < 10000; i++) {
        //increase normal int
        count++;
        //increase atomic int
        atomic_count++;
        //with mutex
        pthread_mutex_lock(&mutex);
        mutexcount++;
        pthread_mutex_unlock(&mutex);
        
    }
    return 0;
}

int main()
{
    // threads
    pthread_t threadIDs[8];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //init mutex
    pthread_mutex_init(&mutex, NULL);

    // making 5 threads
    for(int i = 0; i < 8; i++)
        pthread_create(&threadIDs[i], &attr, runner, NULL);
    
    // waiting for all threads to finish
    for(int i = 0; i < 8; i++)
        pthread_join(threadIDs[i], NULL);

    // printing the variables
    printf("The non-atomic counter is %u\n", count);
    printf("The atomic counter is %u\n", atomic_count);
    printf("The mutex counter is %u\n", mutexcount);
}
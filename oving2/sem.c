

#include "bbuffer.h"
#include "sem.h"
//#define MAX_QUEUE_SIZE=10;
#include <stddef.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


//static jmp_buf s_jumpBuffer;
typedef struct SEM {
    volatile int permits;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} SEM;


SEM *sem_init(int initVal) {
    /*if (initVal < 1) {
        return NULL;
    }*/
    SEM* sem =(SEM*) malloc(sizeof(struct SEM));
    if (sem == NULL) {
        perror("Failed to allocate memory to semaphore!");
        return NULL;
    }
    sem->permits = initVal;
    int mut_status = pthread_mutex_init(&sem->mutex, NULL);
    int cond_status = pthread_cond_init(&sem->cond, NULL);
    if (mut_status || cond_status)
    {
        perror("Failed to initialize mutex\n");
        sem_del(sem);
        return NULL;
    };
    /*pthread_mutex_t temp_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t temp_cond = PTHREAD_COND_INITIALIZER;
    sem->mutex = temp_mutex;
    sem->cond = temp_cond;*/
    /*if (setjmp(s_jumpBuffer)) {
    // The longjmp was executed and returned control here
    return NULL;    
    } else {
    // Normal code execution starts here
        return (SEM)sem;
    }*/
    return sem;
}
 /* Destroys a semaphore and frees all associated resources.
 *
 * Parameters:
 *
 * sem           handle of the semaphore to destroy
 *
 * Returns:
 *
 * 0 on success, negative value on error. 
 *
 * In case of an error, not all resources may have been freed, but 
 * nevertheless the semaphore handle must not be used any more.
 */
int sem_del(SEM *sem) {
    int value;
    int response_mut = pthread_mutex_destroy(&sem->mutex);
    int response_cond = pthread_cond_destroy(&sem->cond);
    if (response_mut || response_cond)
    {
        perror("Failed to destroy mutex\n");
        value = -1;
    };

    free(sem);
    return value;
}
/* P (wait) operation.
 * 
 * Attempts to decrement the semaphore value by 1. If the semaphore value 
 * is 0, the operation blocks until a V operation increments the value and 
 * the P operation succeeds.
 *
 * Parameters:
 *
 * sem           handle of the semaphore to decrement
 */
void P(SEM *sem) {
    // lock the semaphore
    pthread_mutex_lock(&sem->mutex);
    if (sem->permits < 1) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    printf("\nPermits in P: %d\n", sem->permits);
    
    sem->permits--;
    pthread_mutex_unlock(&sem->mutex);
    //unlock the semaphore
}   
/* V (signal) operation.
 *
 * Increments the semaphore value by 1 and notifies P operations that are 
 * blocked on the semaphore of the change.
 *
 * Parameters:
 *
 * sem           handle of the semaphore to increment
 */
void V(SEM *sem) {
    //lock the semaphore
    pthread_mutex_lock(&sem->mutex);
    sem->permits++;
    printf("\nPermits in V: %d\n", sem->permits);
    pthread_mutex_unlock(&sem->mutex);
    pthread_cond_signal(&sem->cond);

    
    //unlock the semaphore
}   

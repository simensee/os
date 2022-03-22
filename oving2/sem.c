#include "sem.h"
//#define MAX_QUEUE_SIZE=10;
#include <stddef.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



//static jmp_buf s_jumpBuffer;

struct SEM {
    int permits;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

};



SEM *sem_init(int initVal) {
    if (initVal < 1) {
        return NULL;
    }
    SEM* sem = malloc(sizeof(struct SEM));
    if (sem == NULL) {
        return NULL;
    }
    sem->permits = initVal;
    pthread_mutex_t temp_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t temp_cond = PTHREAD_COND_INITIALIZER;
    /*if (temp_mutex == NULL || temp_cond == NULL) {
        return NULL;
    }*/
    sem->mutex = temp_mutex;
    sem->cond = temp_cond;
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
    free(sem);
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
    if (sem->permits > 0) {
        sem->permits--;
        pthread_mutex_unlock(&sem->mutex);
    }
    else {
        while (sem->permits < 1) {
            pthread_cond_wait(&sem->cond, &sem->mutex);
            // fjerne en permit
        }
    }

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
    sem->permits = sem->permits + 1;
    pthread_mutex_unlock(&sem->mutex);
    pthread_cond_signal(&sem->cond);
    //unlock the semaphore
}   



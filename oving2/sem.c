#include "sem.h"
//#define MAX_QUEUE_SIZE=10;
#include <stddef.h>


//static jmp_buf s_jumpBuffer;

struct SEM {
    int permits;
    
};



SEM *sem_init(int initVal) {
    struct SEM *sem;
    sem->permits = initVal;
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
    while 
    if (sem->permits > 0) {
        sem->permits--;
    }
    else {

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
    sem->permits = sem->permits + 1;
    //unlock the semaphore
}

int main() {
    return 0;
}
#include "bbuffer.h"
#include "sem.c"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h> //brukes denne?

//denne skjønte jeg ikke bare copypaste
#define QUEUE_EMPTY INT_MIN

/* struct BBUFFER {
    int permits;

    
}; */

struct BNDBUF{
    //pekere og arrays i C er basically det samme, 
    //denne skal være arrayet fordi vi skal allokere det på heapen. 
    //Slik kan vi endre str på runtime
    int *values;
    //head og tail forteller posisjonen i arrayet frammerst og bakerst i listen.
    //num_entries sier hvor mange elementer det er i køen
    //siez er str på arrayet og er greit så vi ikke overflyter arrayet.
    int head, tail, num_entries, size;
    SEM* empty_buffer;
    SEM* full_buffer; 
};

//denne var ikke med i videoen, men lar den være
BNDBUF *bb_init(unsigned int size) {
    struct BNDBUF *bb = malloc(sizeof(BNDBUF));
    bb->head = size;
    bb->values = malloc(sizeof(size)); 
    bb->num_entries=0; 
    bb->head = 0;
    bb->tail = 0;
    bb->empty_buffer = sem_init(size);
    bb->full_buffer = sem_init(0);
    return bb;
}

/*void bb_init(BNDBUF *bb, int max_size) {
    bb->head = max_size;
    bb->values = malloc(sizeof(int) * bb->size);
    bb->num_entries=0; 
    bb->head = 0;
    bb->tail = 0;
}*/

bool bb_empty(BNDBUF* bb) {
    return (bb->num_entries == 0);
}

bool bb_full(BNDBUF* bb) {
    return (bb->num_entries == bb->size);
}



/* Destroys a Bounded Buffer. 
 *
 * All resources associated with the bounded buffer are released.
 *
 * Parameters:
 *
 * bb       Handle of the bounded buffer that shall be freed.
 */

void bb_del(BNDBUF *bb) {
    free(bb->buffer);
    sem_del(free(bb->empty_buffer));
    sem_del(free(bb->full_buffer));
    
}

/* Retrieve an element from the bounded buffer.
 *
 * This function removes an element from the bounded buffer. If the bounded 
 * buffer is empty, the function blocks until an element is added to the 
 * buffer.
 *
 * Parameters:
 *
 * bb         Handle of the bounded buffer.
 *
 * Returns:
 *
 * the int element
 */

int bb_get(BNDBUF *bb) {
    int result;

    P(bb->full_buffer);
    result = bb->values[bb->head];
    bb->head = (bb->head + 1) % bb->size;
    bb->num_entries--;
    V(bb->empty_buffer);
    /*if (!bb_empty(bb)) {
        P(bb->sem);
        result = bb->values[bb->head];
        bb->head = (bb->head + 1) % bb->size;
        bb->num_entries--;
        V(bb->sem);
    } else {
        while (bb_empty(bb));

        P(bb->sem);
        result = bb->values[bb->head];
        bb->head = (bb->head + 1) % bb->size;
        bb->num_entries--;
        V(bb->sem);
    }*/
       
    return result;
}

/* Add an element to the bounded buffer. 
 *
 * This function adds an element to the bounded buffer. If the bounded 
 * buffer is full, the function blocks until an element is removed from 
 * the buffer.
 *
 * Parameters:
 *
 * bb     Handle of the bounded buffer.
 * fd     Value that shall be added to the buffer.
 *
 * Returns:
 *
 * the int element
 */

void bb_add(BNDBUF *bb, int fd) {
    //adder et element til køen/bufferen i tailen

    P(bb->empty_buffer);
    bb->values[bb->tail] = fd;
    bb->num_entries++;
    bb->tail = (bb->tail + 1) % bb->size;
    V(bb->full_buffer);

    return fd;
    // Tidligere kode:
    /*P(bb->sem);
    if (bb_full(bb) == false) {
        bb->values[bb->tail] = fd;
        bb->num_entries++;
        bb->tail = (bb->tail + 1) % bb->size;
        V(bb->sem);
    } else {
        while (bb_full(bb)) {
            // Vente på at det legges til et element
        }
        V(bb->sem);
    }*/
    //feilmelding av noe slag? idk
}






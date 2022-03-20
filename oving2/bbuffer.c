#include "bbuffer.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h> //brukes denne?

//denne skjønte jeg ikke bare copypaste
#define QUEUE_EMPTY INT_MIN

/* struct BBUFFER {
    int permits;

    
}; */

typedef struct {
    //pekere og arrays i C er basically det samme, 
    //denne skal være arrayet fordi vi skal allokere det på heapen. 
    //Slik kan vi endre str på runtime
    int *values;
    //head og tail forteller posisjonen i arrayet frammerst og bakerst i listen.
    //num_entries sier hvor mange elementer det er i køen
    //siez er str på arrayet og er greit så vi ikke overflyter arrayet.
    int head, tail, num_entries, size;
} BNDBUF;

//denne var ikke med i videoen, men lar den være
BNDBUF *bb_init(unsigned int size);

void bb_initt(BNDBUF *bb, int max_size) {
    bb->head = max_size;
    bb->values = malloc(sizeof(int) * bb->size);
    bb->num_entries=0; 
    bb->head = 0;
    bb->tail = 0;
}

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
    free(bb->values);
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

int  bb_get(BNDBUF *bb) {
    int result;

    if (bb_empty(bb)) {
        return QUEUE_EMPTY;
    }

    result = bb->values[bb->head];
    bb->head = (bb->head + 1) % bb->size;
    bb->num_entries--;

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

    if (bb_full(bb) == false) {
        bb->values[bb->tail] = fd;
        bb->num_entries++;
        bb->tail = (bb->tail + 1) % bb->size;
    }
    //feilmelding av noe slag? idk
}


int main()
{
    return 0;
}



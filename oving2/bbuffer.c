

#include <stdio.h>
#include "bbuffer.h"
#include "sem.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h> 


typedef struct BNDBUF{
    int *values;
    int num_entries;
    int size;
    int *head, *tail;
    SEM* empty_buffer;
    SEM* full_buffer; 
}BNDBUF;



BNDBUF *bb_init(unsigned int size) {
    BNDBUF *bb = malloc(sizeof(BNDBUF));
    if (bb == NULL)
    {
        printf("Failed to allocate bndbuf\n");
        free(bb);
    }
    bb->size = size;
    bb->values = (int *)malloc(sizeof(int) * size); 
    bb->num_entries=0; 
    bb->head = bb->values;
    bb->tail = bb->values;
    bb->empty_buffer = sem_init(size);
    bb->full_buffer = sem_init(0);
    return bb;
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
    
    sem_del(bb->empty_buffer);
    sem_del(bb->full_buffer);
    free(bb->values);
    free(bb);
    
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
    result = *bb->head;
    bb->head++;
    if (bb->head == bb->values + bb->size)
        bb->head = bb->values;
    
    V(bb->empty_buffer);
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
    
    P(bb->empty_buffer);
    *bb->tail = fd;
    bb->tail++;
    bb->num_entries++;
    if (bb->tail == bb->values + bb->size)
        bb->tail = bb->values;
    V(bb->full_buffer);
    
}

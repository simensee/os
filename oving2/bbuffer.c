#include "bbuffer.h"

#include <stddef.h>

struct BBUFFER {
    int permits;
    
};

BNDBUF *bb_init(unsigned int size);

/* Destroys a Bounded Buffer. 
 *
 * All resources associated with the bounded buffer are released.
 *
 * Parameters:
 *
 * bb       Handle of the bounded buffer that shall be freed.
 */

void bb_del(BNDBUF *bb);

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

int  bb_get(BNDBUF *bb);

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

void bb_add(BNDBUF *bb, int fd);

int main()
{
    return 0;
}



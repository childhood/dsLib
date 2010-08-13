/* queue.h - header information for queue operations */

/*
Modification History
--------------------
08aug10,gnm written 
 
*/

#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#define QUEUE_DEPTH(Q)  ((Q)->cur_size)
#define QUEUE_SIZE(Q)   ((Q)->max_size)

typedef enum {
   Q_ERR_ERROR_HIGH = -512, /* fencepost */
   Q_ERR_MALLOC_FAIL,
   Q_ERR_ERR = -1, /* generic operational error */
   Q_ERR_OK = 0, /* routine returned without any errors */
   Q_ERR_OVERFLOW,
   Q_ERR_UNDERFLOW
} QUEUE_ERR_E;

typedef struct {
   SLL_T* q;
   unsigned long max_size;
   unsigned long cur_size;
} QUEUE_T;

#endif

/* sll.h - header information for single linked list operations */

/*
* Modification History
* 07jul08,gnm written 
* 
*/

#ifndef DS_SLL_H
#define DS_SLL_H

#include <ds_types.h>

typedef struct _sllnode
    {
    struct _sllnode* next;
#define FIDATA   item.idata
#define FUIDATA  item.uidata
#define FCDATA   item.cdata    
#define FUCDATA  item.ucdata    
#define FVPDATA  item.vpdata
#define FFPDATA  item.fpdata 
    NODE_DATA_TYPE_E type;
    NODE_DATA_T item;       
    }SLL_NODE;

typedef int (*SLL_ITER_FUNC)(SLL_NODE*);

typedef struct _sllnodehead {
   struct _sllnode* lhead;
   struct _sllnode* ltail;
   int total_elements;
   NODE_DATA_TYPE_E data_type;
   SLL_ITER_FUNC iterator;
   FUNCPTR2_T preiterator;
   FUNCPTR2_T postiterator;
} SLL_T;
    

typedef struct _dllnode
    {
    struct _dllnode* next;
    struct _dllnode* prev;
    int item;
    }DLL_NODE;

typedef enum {
   SLL_ERR_ERROR_HIGH = -512, /* fencepost */
   SLL_ERR_MALLOC_FAIL,
   SLL_ERR_ERR = -1, /* generic operational error */
   SLL_ERR_OK = 0 /* routine returned without any errors */
} SLL_ERR_E;


/* Public API */
/* insert an element into the SLL */
SLL_ERR_E       sll_insert (SLL_T* head, ...);
/* insert N element into the SLL, all of the same types */
SLL_ERR_E       sll_ninsert (SLL_T* head, unsigned int num, ...);
/* delete an element from the SLL */
SLL_ERR_E       sll_delete (SLL_T* sll, ...);
/* create a new SLL */
SLL_T*          sll_new (NODE_DATA_TYPE_E data_type, SLL_ITER_FUNC iterator,
                         FUNCPTR2_T pre, FUNCPTR2_T post);
/* iterate over all the elements of the SLL */
void            sll_iter (SLL_T* head);
/* find the SLL node object next to the given one */
SLL_NODE*       sll_next_get (SLL_T* sll, SLL_NODE* to);
/* find the SLL node object previous to the given one */
SLL_NODE*       sll_prev_get (SLL_T* sll, SLL_NODE* to);
/* get the first node in the SLL */
SLL_NODE*       sll_first_get (SLL_T* sll);
/* get the last node in the SLL */
SLL_NODE*       sll_last_get (SLL_T* sll);
/* remove the first element in the SLL */
SLL_NODE*       sll_remove_first (SLL_T* sll);
#endif /* !defined DS_SLL_H */

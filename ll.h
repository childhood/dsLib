/*  Copyright 2010 Gaurav Mathur

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DS_SLL_H
#define DS_SLL_H

#include <ds_types.h>

#define DEFAULT_MAX_LEVEL       (16)
#define DEFAULT_P               (0.5)

/* single linked list node */
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

/* Single linked list meta node */
typedef struct _sllnodehead {
   struct _sllnode* lhead;
   struct _sllnode* ltail;
   int total_elements;
   NODE_DATA_TYPE_E data_type;
   SLL_ITER_FUNC iterator;
   FUNCPTR2_T preiterator;
   FUNCPTR2_T postiterator;
   unsigned char max_level;
} SLL_T;

/* Skip list node type */
typedef struct _sklnode {
   /* array of level N next nodes */
   struct _sklnode** nexts;
#define FIDATA   item.idata
#define FUIDATA  item.uidata
#define FCDATA   item.cdata    
#define FUCDATA  item.ucdata    
#define FVPDATA  item.vpdata
#define FFPDATA  item.fpdata 
   NODE_DATA_TYPE_E type;
   NODE_DATA_T item;       
}SKL_NODE;

/* Skip list meta node */
typedef struct _skpnodehead {
   struct _sklnode** heads;
   int total_elements;
   NODE_DATA_TYPE_E data_type;
   SLL_ITER_FUNC iterator;
   FUNCPTR2_T preiterator;
   FUNCPTR2_T postiterator;
   unsigned char max_level;
} SKL_T; 

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

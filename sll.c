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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> /* va_* */

#include <sll.h>

#define SLL_TEST


/*******************************************************************************
* sll_first_get - return the first node in the list
*
* This routine returns the first node object in the list <sll>
*
* ARGUMENTS:
*  <sll> - linked list to operate on
*            
* RETURNS: Valid SLL_NODE* or NULL
*/

SLL_T* sll_duplicate
(
SLL_T* sll
)
{
   SLL_NODE* node = sll->lhead;
   SLL_T* dup_list;
   
   if (NULL == (dup_list = sll_new (sll->data_type, sll->iterator,
                                    sll->preiterator, sll->postiterator)))
   {
      return NULL;
   }
   
   while (node)
   {
      switch (sll->data_type)
      {
         case IDATA:
         case CDATA:          
            sll_insert (dup_list, node->FIDATA);
            break;
         case UIDATA:
         case UCDATA:
            sll_insert (dup_list, node->FUIDATA);
            break;
         case VPDATA:
            sll_insert (dup_list, node->FVPDATA);
            break;
         case FPDATA:
            sll_insert (dup_list, node->FFPDATA);
            break;
         case LDATA:
         case LLDATA:
         case ULDATA:
         case ULLDATA:
            /* todo */
            break;
      }
      node = node->next;
   }
   return SLL_ERR_OK;
}

/*******************************************************************************
* sll_first_get - return the first node in the list
*
* This routine returns the first node object in the list <sll>
*
* ARGUMENTS:
*  <sll> - linked list to operate on
*            
* RETURNS: Valid SLL_NODE* or NULL
*/

SLL_NODE* sll_first_get
    (
    SLL_T* sll  /* linked list to operate on */
    )
    {
    return sll->lhead;
    }

/*******************************************************************************
* sll_last_get - return the last node in the list
*
* This routine returns the last node object in the list <sll>
*
* ARGUMENTS:
*  <sll> - linked list to operate on
*            
* RETURNS: Valid SLL_NODE* or NULL
*/

SLL_NODE* sll_last_get
    (
    SLL_T* sll  /* linked list to operate on */
    )
    {
    return sll->ltail;
    }

/*******************************************************************************
* sll_next_get - return the node next to the one whose object id is given
*
* This routine returns the node next to the node <to>. If <to> is NULL, the
* routine returns the first node in the list. This routine is different from
* the 
*
* ARGUMENTS:
*  <sll> - linked list to operate on
*  <to> - find the node next to this node
*            
* RETURNS: Valid SLL_NODE* or NULL
*/

SLL_NODE* sll_next_get
    (
    SLL_T* sll,         /* linked list to operate on */
    SLL_NODE* to        /* find the node next to this node */
    )
    {
    SLL_NODE* node;
    
    if (NULL == sll)    /* no list, nothing to do */
        return NULL;
    
    if (NULL == to)
        return sll->lhead; /* head of list */
    
    node = sll->lhead;
    while (node && node != to)
        node = node->next;
    
    return node->next;
    }

/*******************************************************************************
* sll_prev_get - return the node previous to the one whose object id is given
*
* This routine returns the node previou to the node <to>. The routine NULL to
* signify "no node" if <to> is either NULL, or the first node in the list.
*
* ARGUMENTS:
*  <sll> - linked list to operate on
*  <to> - find the node previous to this node
*            
* RETURNS: Valid SLL_NODE* or NULL
*/

SLL_NODE* sll_prev_get
    (
    SLL_T* sll,         /* linked list to operate on */
    SLL_NODE* to        /* find the node previous to this node */
    )
    {
    SLL_NODE* node;
    SLL_NODE* prev = NULL;

    if (NULL == sll)    /* no list, nothing to do */
        return NULL;
    if (NULL == to)
        return NULL;    /* head of list */

    node = sll->lhead;
    while (node && node != to)
        {
        prev = node;
        node = node->next;
        }
    return prev;
    }

/*******************************************************************************
 * sll_concat - insert an element into the SLL 
 *
 * RETURNS:  error code
 */

SLL_T* sll_concat (SLL_T* first, SLL_T* second)
    {
    /* to-do */
    /*
    SLL_NODE* node;
    SLL_T* new = malloc (sizeof (SLL_T));
    
    */
    return NULL;
    }

/*******************************************************************************
 * sll_union - 
 *
 * This list copies the contents of list <second> into the list specified by
 * <first>, exapnding the list <first>.
 *
 * RETURNS: SLL_ERR_ERR if error, SLL_ERR_OK if successful
 */

SLL_ERR_E sll_union (SLL_T* first, SLL_T* second)
    {
    SLL_NODE* node;

    node = second->lhead;
    if (first->data_type != second->data_type)
        return SLL_ERR_ERR;
    while (node)
        {
        switch (first->data_type)
            {
            case IDATA:
            case CDATA:          
                sll_insert (first, node->FIDATA);
                break;
            case UIDATA:
            case UCDATA:
                sll_insert (first, node->FUIDATA);
                break;
            case VPDATA:
                sll_insert (first, node->FVPDATA);
                break;
            case FPDATA:
                sll_insert (first, node->FFPDATA);
                break;
            case LDATA:
            case LLDATA:
            case ULDATA:
            case ULLDATA:
                /* todo */
                break;
            }
        node = node->next;
        }
    return SLL_ERR_OK;
    }

/*******************************************************************************
 * sll_expand - expand a list
 *
 * This list copies the contents of list <second> into the list specified by
 * <first>, exapnding the list <first>.
 *
 * RETURNS: SLL_ERR_ERR if error, SLL_ERR_OK if successful
 */

SLL_ERR_E sll_expand (SLL_T* first, SLL_T* second)
    {
    SLL_NODE* node;

    node = second->lhead;
    if (first->data_type != second->data_type)
        return SLL_ERR_ERR;
    while (node)
        {
        switch (first->data_type)
            {
            case IDATA:
            case CDATA:          
                sll_insert (first, node->FIDATA);
                break;
            case UIDATA:
            case UCDATA:
                sll_insert (first, node->FUIDATA);
                break;
            case VPDATA:
                sll_insert (first, node->FVPDATA);
                break;
            case FPDATA:
                sll_insert (first, node->FFPDATA);
                break;
            case LDATA:
            case LLDATA:
            case ULDATA:
            case ULLDATA:
                /* todo */
                break;
            }
        node = node->next;
        }
    return SLL_ERR_OK;
    }

/*******************************************************************************
* sll_insert - insert an element into the SLL 
*
* RETURNS: SLL_ERR_OK if successful
*/

SLL_ERR_E sll_insert (SLL_T* head, ...)
    {
    SLL_NODE* newNode;
    va_list ap;
    newNode = (SLL_NODE*)malloc (sizeof (SLL_NODE));
    if (NULL == newNode)
        return SLL_ERR_MALLOC_FAIL;    
    newNode->next = NULL;

    va_start (ap, head);
    switch (head->data_type)
    {
       case IDATA:
       case CDATA:          
          newNode->FIDATA = va_arg (ap, int);
          break;
       case UIDATA:
       case UCDATA:
          newNode->FUIDATA = va_arg (ap, unsigned int);
          break;
       case VPDATA:
          newNode->FVPDATA = va_arg (ap, void*);
          break;
       case FPDATA:
          newNode->FFPDATA = va_arg (ap, FUNCPTR2_T);
          break;                
    case LDATA:
    case LLDATA:
    case ULDATA:
    case ULLDATA:
        /* todo */
        break;
    }

    if (head->lhead == NULL)
        head->lhead = newNode;
    if (head->ltail != NULL)
        head->ltail->next = newNode;
    head->ltail = newNode;
    va_end (ap);
    return SLL_ERR_OK;
    }

/*******************************************************************************
 * sll_find - find a SLL node with element 
 *
 *
 * ARGUMENTS: 
 *            
 * RETURNS: 
 */

SLL_NODE* sll_find (SLL_T* sll, ...)
    {
    SLL_NODE* node;
    SLL_NODE* prev;
    va_list ap;
    
    if (NULL == sll)
        return NULL;
    node = sll->lhead;
    prev = NULL;
    
    va_start (ap, sll);
    while (node)
        {
        switch (sll->data_type)
            {
            case IDATA:
            case CDATA:            
                if (node->FIDATA == va_arg (ap, int))
                    return node;
                break;
            case UIDATA:
            case UCDATA:            
                if (node->FUIDATA == va_arg (ap, unsigned int))
                    return node;
                break;
            case VPDATA:
                if (node->FVPDATA == va_arg (ap, void*))
                    return node;
                break;
            case FPDATA:
                if (node->FFPDATA == va_arg (ap, FUNCPTR2_T))
                    return node;
                break;
            case LDATA:
            case LLDATA:
            case ULDATA:
            case ULLDATA:
                /* todo */
                break;
            }
        prev = node;
        node = node->next;
        }
    va_end (ap);
    return NULL;
    }

/*******************************************************************************
 * sll_find_prev - find the node previous to the one given
 *
 *
 * ARGUMENTS: 
 *            
 * RETURNS: 
 */

SLL_NODE* sll_find_prev (SLL_T* sll, ...)
    {
    SLL_NODE* node;
    SLL_NODE* prev;
    va_list ap;
    
    if (NULL == sll)
        return NULL;
    node = sll->lhead;
    prev = NULL;
    
    va_start (ap, sll);
    while (node)
        {
        switch (sll->data_type)
            {
            case IDATA:
                if (node->FIDATA == va_arg (ap, int))
                    return prev;
                break;
            case UIDATA:
                if (node->FUIDATA == va_arg (ap, unsigned int))
                    return prev;
                break;
            case CDATA:
                if (node->FCDATA == (char)va_arg (ap, int))
                    return prev;
                break;
            case UCDATA:
                if (node->FUCDATA == (unsigned char)va_arg (ap, unsigned int))
                    return prev;
                break;
            case VPDATA:
                if (node->FVPDATA == va_arg (ap, void*))
                    return prev;
                break;
            case FPDATA:
                if (node->FFPDATA == va_arg (ap, FUNCPTR2_T))
                    return prev;
                break;
            case LDATA:
            case LLDATA:
            case ULDATA:
            case ULLDATA:
                /* todo */
                break;
                
            }
        prev = node;
        node = node->next;
        }
    va_end (ap);
    return NULL;
    }
                    
/*******************************************************************************
 * sll_delete - remove an element from the SLL
 *
 * This routine removes an element from the SLL and returns the element node
 *
 * ARGUMENTS: head - head of the SLL
 *              item - element to be removed
 * RETURNS: 
 */

SLL_ERR_E sll_delete (SLL_T* sll, ...)
    {
    SLL_NODE* node;
    SLL_NODE* prev;
    va_list ap;
    int found = 0;
    NODE_DATA_T data;
    
    if (NULL == sll)
        return SLL_ERR_MALLOC_FAIL;
    node = sll->lhead;
    prev = NULL;
    
    va_start (ap, sll);
    switch (sll->data_type)
        {
        case IDATA:
        case CDATA:         
            data.idata = va_arg (ap, int);
            break;
        case UIDATA:
        case UCDATA:
            data.uidata = va_arg (ap, unsigned int);
            break;
        case VPDATA:
            data.vpdata = va_arg (ap, void*);
            break;
        case FPDATA:
            data.fpdata = va_arg (ap, FUNCPTR2_T);
            break;
        case LDATA:
        case LLDATA:
        case ULDATA:
        case ULLDATA:
            /* todo */
            break;
        }
   
    while (node)
        {
        switch (sll->data_type)
            {
            case IDATA:
            case CDATA:
                if (data.idata == node->FIDATA)
                    found = 1;
                break;
            case UIDATA:
            case UCDATA:            
                if (data.uidata == node->FUIDATA)
                    found = 1;
                break;
            case VPDATA:
                if (data.vpdata == node->FVPDATA)
                    found = 1;
                break;
            case FPDATA:
                if (data.fpdata == node->FFPDATA)
                    found = 1;
                break;
            case LDATA:
            case LLDATA:
            case ULDATA:
            case ULLDATA:
                /* todo */
                break;
            }
        
        if (found)
            {
            if (NULL != prev)
                prev->next = node->next;
            if (sll->lhead == node)
                sll->lhead = node->next;
            if (sll->ltail == node)
                sll->ltail = prev;            
            free (node);
            return SLL_ERR_OK;
            }
        prev = node;
        node = node->next;
        }
    va_end (ap);
    return SLL_ERR_OK;   
    }


/*******************************************************************************
* sll_remove_first - remove an element from the SLL
*
* This routine removes an element from the SLL and returns the element node
*
* ARGUMENTS: head - head of the SLL
*              item - element to be removed
* RETURNS: 
*/

SLL_NODE* sll_remove_first (SLL_T* sll)
    {

    SLL_NODE* node;

    node = sll->lhead;
    if (node)
       sll->lhead = sll->lhead->next;
    return node;
    }

/*******************************************************************************
 * sll_iter - 
 *
 * RETURNS: SLL_T* if ok; NULL if error
 */

void sll_iter (SLL_T* head)
    {
    SLL_NODE* node = head->lhead;

    if (NULL == head->iterator)
       return; /* there's nothing to do */
    
    if (head->iterator)
       head->preiterator (0,0,0);
    
    while (node != NULL)
    {
       head->iterator (node);
       node = node->next;
    }
    if (head->postiterator)
       head->postiterator (0,0,0);
    }


/*******************************************************************************
 * sll_new - create a new SSL
 *
 * RETURNS: SLL_T* if ok; NULL if error
 */

SLL_NODE* sll_find_nth_from_last (SLL_NODE* head, int nth)
    {
    SLL_NODE* nthnode = head;
    int idx = 1;
    
    while (head != NULL)
        {
        head = head->next;
        if (idx <= nth)
            idx++;
        else 
            nthnode = nthnode->next;
        }
    return nthnode;
    }

/*******************************************************************************
 * sll_new - create a new SSL
 *
 * RETURNS: SLL_T* if ok; NULL if error
 */

SLL_T* sll_new (NODE_DATA_TYPE_E data_type, SLL_ITER_FUNC iterator,
                FUNCPTR2_T pre, FUNCPTR2_T post)
    {
    SLL_T* sll;

    sll = (SLL_T*)malloc (sizeof (SLL_T));
    if (NULL == sll)
        return NULL;
    sll->lhead = NULL;
    sll->ltail = NULL;
    sll->total_elements = 0;
    sll->data_type = data_type;
    if (iterator)
       sll->iterator = iterator;
    if (post)
       sll->postiterator = post;
    if (pre)
    sll->preiterator = pre;
    return sll;
    }


#ifdef SLL_TEST
/*******************************************************************************
 * sll_new - create a new SSL
 *
 * RETURNS: SLL_T* if ok; NULL if error
 */

int post_iterator (int ignore1, int ignore2, int ignore3)
{
   printf ("\n[END]\n");
   return 0;
}

/*******************************************************************************
 * sll_new - create a new SSL
 *
 * RETURNS: SLL_T* if ok; NULL if error
 */

int pre_iterator (int ignore1, int ignore2, int ignore3)
{
   printf ("[==]\n");
   return 0;
}

/*******************************************************************************
 * sll_new - create a new SSL
 *
 * RETURNS: SLL_T* if ok; NULL if error
 */

static int iter_cb_int (SLL_NODE* node)
{
   printf ("%ld ", node->FIDATA);
   return 0;
}

/*******************************************************************************
* test_case_int_1 - test core linked list operations
*
* RETURNS: void
*/

static void test_case_int_1 (void)
{
    SLL_T* head;
    int i;

    fprintf (stderr, "test case int#1\n");
    head = sll_new (IDATA, iter_cb_int, pre_iterator, post_iterator);

    for (i = 10; i < 20; i++)
       sll_insert (head, i);
    sll_iter (head);
    
    fprintf (stderr, "deleting 10\n");
    sll_delete (head, 10);
    fprintf (stderr, "deleting 15\n");
    sll_delete (head, 15);
    fprintf (stderr, "deleting 19\n");
    sll_delete (head, 19);
    sll_iter (head);
    fprintf (stderr, "inserting 19\n");    
    sll_insert (head, 19);
    fprintf (stderr, "inserting 10\n");    
    sll_insert (head, 10);
    sll_iter (head);
}

/*******************************************************************************
* test_case_int_2 - test routines to expand a linked list
*
* RETURNS: void
*/

static void test_case_int_2 (void)
{
    SLL_T* first;
    SLL_T* second;
    int i;

    fprintf (stderr, "test case int#2\n");
    first = sll_new (IDATA, iter_cb_int, pre_iterator, post_iterator);
    second = sll_new (IDATA, iter_cb_int, pre_iterator, post_iterator);

    for (i = 10; i <= 20; i++)
       sll_insert (first, i);
    for (i = 20; i < 30; i++)
       sll_insert (second, i);

    sll_iter (first);
    sll_iter (second);
    fprintf (stderr, "expanding...\n");
    sll_expand (first, second);
    sll_iter (first);
}

/*******************************************************************************
 * test_case_int_3 - test routines sll_next_get and sll_prev_get
 *
 * RETURNS: n.a.
 */

static void test_case_int_3 (void)
    {
    SLL_T* sll;
    SLL_NODE* node = NULL;
    int i;

    fprintf (stderr, "test case int#3\n");
    sll = sll_new (IDATA, iter_cb_int, pre_iterator, post_iterator);

    fprintf (stderr, "inserting elements from 10 - 20 in the list\n");
    for (i = 10; i <= 20; i++)
        sll_insert (sll, i);

    while (NULL != (node = sll_next_get (sll, node)))
        {
        fprintf (stderr, "%ld ", node->FIDATA);        
        }
    fprintf (stderr, "\n");
    
    node = sll_last_get(sll);
    while (NULL != (node = sll_prev_get (sll, node)))
        {
        fprintf (stderr, "%ld ", node->FIDATA);        
        }
    
    fprintf (stderr, "\n");
    }

/*******************************************************************************
 * sll_new - create a new SSL
 *
 * RETURNS: SLL_T* if ok; NULL if error
 */

static int iter_cb_char (SLL_NODE* node)
{
   printf ("%c ", node->FCDATA);
   return 0;
}

/*******************************************************************************
 * sll_new - create a new SSL
 *
 * RETURNS: SLL_T* if ok; NULL if error
 */

static void test_case_char (void)
{
    SLL_T* head;
    int i;
    
    head = sll_new (CDATA, iter_cb_char, pre_iterator, post_iterator);

    for (i = 'a'; i <= 'z'; i++)
       sll_insert (head, i);
    sll_iter (head);
    printf ("\n");
    fprintf (stderr, "deleting a\n");
    sll_delete (head, 'a');
    fprintf (stderr, "deleting f\n");
    sll_delete (head, 'f');
    fprintf (stderr, "deleting z\n");
    sll_delete (head, 'z');
    sll_iter (head);
    fprintf (stderr, "inserting a \n");    
    sll_insert (head, 'a');
    fprintf (stderr, "inserting z\n");    
    sll_insert (head, 'z');
    fprintf (stderr, "inserting z\n");    
    sll_insert (head, 'z');
    sll_iter (head);
    fprintf (stderr, "deleting z\n");
    sll_delete (head, 'z');
    sll_iter (head);
}

/*******************************************************************************
 * sll_new - create a new SSL
 *
 * RETURNS: SLL_T* if ok; NULL if error
 */

int sll_main (int argc, char** argv)
    {
       test_case_int_1 ();
       test_case_char ();
       test_case_int_2 ();
       test_case_int_3 ();
       return 0;
    }
#endif /* defined TEST */

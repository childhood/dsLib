/**
 * linked list data structure
 * Copyright (c) 2010, Gaurav Mathur <narainmg@gmail.com>
 *   
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *   
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See README and COPYING for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> /* va_* */

#include <ll.h>
#include <utils.h>

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
   return LL_ERR_OK;
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
 * RETURNS: LL_ERR_ERR if error, LL_ERR_OK if successful
 */

LL_ERR_E sll_union (SLL_T* first, SLL_T* second)
    {
    SLL_NODE* node;

    node = second->lhead;
    if (first->data_type != second->data_type)
        return LL_ERR_ERR;
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
    return LL_ERR_OK;
    }

/*******************************************************************************
 * sll_expand - expand a list
 *
 * This list copies the contents of list <second> into the list specified by
 * <first>, exapnding the list <first>.
 *
 * RETURNS: LL_ERR_ERR if error, LL_ERR_OK if successful
 */

LL_ERR_E sll_expand (SLL_T* first, SLL_T* second)
    {
    SLL_NODE* node;

    node = second->lhead;
    if (first->data_type != second->data_type)
        return LL_ERR_ERR;
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
    return LL_ERR_OK;
    }

/*******************************************************************************
* sll_insert - insert an element into the SLL 
*
* RETURNS: LL_ERR_OK if successful
*/

LL_ERR_E sll_insert (SLL_T* head, ...)
    {
    SLL_NODE* newNode;
    va_list ap;

    newNode = (SLL_NODE*)malloc (sizeof (SLL_NODE));
    if (NULL == newNode)
        return LL_ERR_MALLOC_FAIL;    
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
    return LL_ERR_OK;
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


/**
 * @brief remove an element from the single linked list and return the element
 * node 
 * 
 * @param[in] head head of the sll
 * @param[in] item item to be deleted
 * @return LL_ERR_E
 */
LL_ERR_E sll_delete (SLL_T* sll, ...)
    {
    SLL_NODE* node;
    SLL_NODE* prev;
    va_list ap;
    int found = 0;
    NODE_DATA_T data;
    
    if (NULL == sll)
        return LL_ERR_MALLOC_FAIL;
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
            return LL_ERR_OK;
            }
        prev = node;
        node = node->next;
        }
    va_end (ap);
    return LL_ERR_OK;   
    }


/**
 * @brief remove the first element from the list and return it
 */
SLL_NODE* sll_remove_first (SLL_T* sll)
    {

    SLL_NODE* node;

    node = sll->lhead;
    if (node)
       sll->lhead = sll->lhead->next;
    return node;
    }

/**
 * @brief single linked list iterator
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


/**
 * @brief 
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

/**
 * @brief create a new singly linked list
 * 
 * @param[in] data_type the type of data stored in the linked list
 * @param[in] iterator the linked list iterator function
 * @param[in] pre the linked list pre-iterator routine. This routine will be
 * called before the iterator callback
 * @param[in] post the linked list post-iterator callback. This routine will
 * be called after the iterator callback is done.
 * @return A new linked list (SLL_T*)
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

/**
 * @brief 
 * 
 * @return LL_ERR_E
 */
void skl_iter (SKL_T* skl)   
{
   SKL_NODE* node = skl->head->nexts[0];
   while (NULL != node)
   {
      node = node->nexts[0];
      fprintf (stdout, "%ld ", node->FIDATA);
   }
}

/**
 * @brief return a random level for a new skip list node
 * 
 * @return LL_ERR_E
 */
static inline unsigned int skl_random_level (unsigned char max_level)
{
   unsigned int level = 0;
   
   while (dslib_random(1) < DEFAULT_SKL_P && level < max_level)
      level = level + 1;
   return level;
}

/**
 * @brief create a new skip list element
 * 
 */
static inline SKL_NODE* skl_new_node (unsigned char level)
{
   SKL_NODE* node;
   int idx;
   
   node = malloc (sizeof (SKL_NODE));
   if (NULL == node)
      return NULL;
   node->nexts = malloc (level * sizeof (SKL_NODE*));
   for (idx = 0; idx < level; idx++)
      node->nexts[idx] = NULL;
   
   return node;
}

/**
 * @brief delete an element from the skip list
 *
 * William Pugh's algorithm
 * --
 * Delete(list, searchKey)
 *     local update[1..MaxLevel]
 *     x := list->header
 *     for i := list->level downto 1 do
 *        while x->forward[i]�key < searchKey do
 *           x := x->forward[i]
 *        update[i] := x
 *     x := x->forward[1]
 *     if x->key = searchKey then
 *        for i := 1 to list->level do
 *           if update[i]->forward[i] != x then break
 *           update[i]->forward[i] := x->forward[i]
 *        free(x)
 *        while list->level > 1 and
 *           list->header->forward[list->level] = NIL do
 *           list->level := list->level -1 
 *
 * @param[in] head list to insert item into 
 * @param[in] item the item to insert
 * @return LL_ERR_E
 */
LL_ERR_E skl_delete_idata (SKL_T* skl, int item)
{
   SKL_NODE* temp;
   SKL_NODE* update[DEFAULT_SKL_MAX_LEVEL] = {0};
   unsigned char cur_level_idx = skl->cur_level-1;
   unsigned int idx;
   
   temp = skl->head;
   for (idx = cur_level_idx; idx >= 0; idx--)
   {
      while (temp->nexts[idx] != NULL && temp->nexts[idx]->FIDATA < item)
         temp = temp->nexts[idx];         
      update[idx] = temp;      
   }
      
   if (temp->FIDATA != item)
      return LL_ERR_ELE_NOT_FOUND;

   for (idx = 0; idx < (skl->cur_level-1); idx--)
   {
      if (update[idx]->nexts[idx] != temp)
         break;
      update[idx]->nexts[idx] = temp->nexts[idx];
   }

   for (idx = 0; idx < temp->level-1; idx++)
      free (temp->nexts[idx]);
   free (temp);

   while (skl->cur_level > 1 && skl->head->nexts[skl->cur_level] == NULL)
      skl->cur_level = skl->cur_level - 1;
   
   return LL_ERR_OK;
}

/**
 * @brief insert an element into the skip list
 *
 * William Pugh's algorithm
 * --
 * Insert(list, searchKey, newValue)
 *    local update[1..MaxLevel]   {
 *    x := list->header
 *    for i := list->level downto 1 do
 *       while x->forward[i]->key < searchKey do
 *          x := x->forward[i]
 *       update[i] := x
 * x := x->forward[1]
 * if x->key = searchKey then x->value := newValue
 * else
 *    lvl := randomLevel()
 *    if lvl > list->level then
 *       for i := list->level + 1 to lvl do
 *          update[i] := list->header
 *       list->level := lvl
 *    x := makeNode(lvl, searchKey, value)
 *    for i := 1 to level do
 *       x->forward[i] := update[i]->forward[i]
 *       update[i]->forward[i] := x
 *
 * @param[in] head list to insert item into 
 * @param[in] item the item to insert
 * @return LL_ERR_E
 */
LL_ERR_E skl_insert_idata (SKL_T* skl, int item)
{
   SKL_NODE* new_node;
   SKL_NODE* temp;
   SKL_NODE* update[DEFAULT_SKL_MAX_LEVEL] = {0};
   unsigned char cur_level_idx = skl->cur_level-1;
   unsigned char level;
   unsigned int idx;
   
   temp = skl->head;
   for (idx = cur_level_idx; idx >= 0; idx--)
   {
      while (temp->nexts[idx] != NULL && temp->nexts[idx]->FIDATA < item)
         temp = temp->nexts[idx];         
      update[idx] = temp;      
   }
      
   level = skl_random_level(skl->max_level);
   new_node = skl_new_node (level);
   new_node->FIDATA = item;
   new_node->level = level;
   
   if (level > skl->cur_level)
   {
      for (idx = ((skl->cur_level-1)+1); idx <= (level-1); idx++)
         update[idx] = skl->head;
      skl->cur_level = level;
   }
   
   for (idx = 0; idx < (level-1); idx++)
   {
      new_node->nexts[idx] = update[idx]->nexts[idx];
      update[idx]->nexts[idx] = new_node;
   }

   return LL_ERR_OK;
}

/**
 * @brief create a new skip list
 * 
 * @param[in] data_type the type of data stored in the linked list
 * @param[in] iterator the linked list iterator function
 * @param[in] pre the linked list pre-iterator routine. This routine will be
 * called before the iterator callback
 * @param[in] post the linked list post-iterator callback. This routine will
 * be called after the iterator callback is done.
 * @return A new linked list (SLL_T*)
 */
SKL_T* skl_new (NODE_DATA_TYPE_E data_type, unsigned char max_level,
                SKL_ITER_FUNC iterator, FUNCPTR2_T pre, FUNCPTR2_T post)
{
   SKL_T* skl;
   unsigned char idx;

   if (max_level == 0)
      return NULL;
   
   skl = (SKL_T*)malloc (sizeof (SKL_T));
   if (NULL == skl)
      return NULL;
   
   skl->total_elements = 0;
   skl->cur_level = DEFAULT_SKL_START_LEVEL;
   skl->max_level = max_level;

   skl->head = skl_new_node (DEFAULT_SKL_MAX_LEVEL);
   
   skl->data_type = data_type;
   
   if (iterator)
      skl->iterator = iterator;
   if (post)
      skl->postiterator = post;
   if (pre)
      skl->preiterator = pre;
   return skl;
}

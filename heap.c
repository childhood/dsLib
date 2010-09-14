/** @file heap.c
 * 
 * heap data structure and operations
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

#include <heap.h>

/**
 * @brief graphviz description plugin for heap ds.
 *
 * @param[in] h The heap to operate in
 * @param[in] filename The file to write the graphviz description to.
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_graphviz_description
(
HEAP_T* h,
char* filename
)
{
   FILE* fp;
   unsigned long idx = 0;
   unsigned long weight;
   if (NULL == filename)
   {
      //return GPH_ERR_ERR;
      fp = stderr;
   }
   else
   {
      fp = fopen (filename, "w");
      fprintf (stderr, "%p", fp);
      if (NULL == fp)
         return HEAP_ERR_ERR;
   }
   
   fprintf (fp, "graph G {\n");
   fprintf (fp, "node [shape = circle, style=filled];\n");
   fprintf (fp, "size=\"12,8\"\n");

   weight = h->heap_size;
   if (HEAP_LEFT(idx) < h->heap_size)
      fprintf (fp, "\t%lu -- %lu [weight=%lu];\n ", HEAP_KEY(h, idx),
               HEAP_KEY(h, HEAP_LEFT(idx)), weight);
   if (HEAP_RIGHT(idx) < h->heap_size)
      fprintf (fp, "\t%lu -- %lu [weight=%lu];\n", HEAP_KEY(h, idx),
               HEAP_KEY(h, HEAP_RIGHT(idx)), weight);
   
   for (idx = 1; idx < h->heap_size; idx++)
   {
      if (HEAP_LEFT(idx) < h->heap_size)
         fprintf (fp, "\t%lu -- %lu;\n ", HEAP_KEY(h, idx),
                  HEAP_KEY(h, HEAP_LEFT(idx)));
      if (HEAP_RIGHT(idx) < h->heap_size)
         fprintf (fp, "\t%lu -- %lu;\n", HEAP_KEY(h, idx),
                  HEAP_KEY(h, HEAP_RIGHT(idx)));
   }
   
   fprintf (fp, "}\n");

   if (NULL != filename)
      fclose (fp);
   
   return HEAP_ERR_OK;
}


/**
 * @brief dump heap keys
 */
void heap_dump (HEAP_T* h)
{
   unsigned long idx;

   fprintf (stdout, "[Dumping heap (heap_size=%lu)]\n", h->heap_size);
   for (idx = 0; idx < h->heap_size; idx++)
   {
      fprintf (stdout, "i=%lu -> key=%lu\n", *h->nodes[idx]->i, h->nodes[idx]->key);
   }
}

/**
 * @brief CSLR MIN-HEAPIFY
 *
 * This routine creates a min-heap for the subtree rooted at index i. The
 * index is 0 based.
 *
 * @param[in] h The heap to operate on
 * @param[in] i The (0-based) subtree index
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_min_heapify (HEAP_T* h, unsigned long i)
{
   unsigned long l = HEAP_LEFT(i);
   unsigned long r = HEAP_RIGHT(i);
   unsigned long smallest;
   unsigned long tmp_key;
   unsigned long* tmp_i;
   void* tmp_data;

   if (h->type == DS_HEAP_MAX)
      return HEAP_ERR_WRONG_TYPE;
   
   if (l < h->heap_size && (HEAP_KEY(h, l) < HEAP_KEY(h, i)))
      smallest = l;
       else
      smallest = i;
   
   if (r < h->heap_size && (HEAP_KEY(h, r) < HEAP_KEY(h, smallest)))
      smallest = r;

   if (smallest != i)
   {
      tmp_key = HEAP_KEY(h, smallest);
      tmp_data = HEAP_DATA(h, smallest);
      tmp_i = HEAP_I(h, smallest);
      HEAP_KEY(h, smallest) = HEAP_KEY(h, i);
      HEAP_DATA(h, smallest) = HEAP_DATA(h, i);
      HEAP_I(h, smallest) = HEAP_I(h, i);
      HEAP_KEY(h, i) = tmp_key;
      HEAP_DATA(h, i) = tmp_data;
      HEAP_I(h, i) = tmp_i;

      heap_min_heapify (h, smallest);
   }
   return HEAP_ERR_OK;
}

/**
 * @brief CSLR MAX-HEAPIFY
 *
 * This routine creates a max-heap for the subtree rooted at index i. The
 * index is 0 based.
 *
 * @param[in] h The heap to operate on
 * @param[in] i The (0-based) subtree index
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_max_heapify (HEAP_T* h, unsigned long i)
{
   unsigned long l = HEAP_LEFT(i);
   unsigned long r = HEAP_RIGHT(i);
   unsigned long largest;
   unsigned long tmp_key;
   unsigned long* tmp_i;
   void* tmp_data;

   //fprintf (stdout, "i=%lu; l=%lu; r=%lu\n", i, l, r);
   if (h->type == DS_HEAP_MIN)
      return HEAP_ERR_WRONG_TYPE;
   
   if (l < h->heap_size && (HEAP_KEY(h, l) > HEAP_KEY(h, i)))
      largest = l;
   else
      largest = i;
   
   if (r < h->heap_size && (HEAP_KEY(h, r) > HEAP_KEY(h, largest)))
      largest = r;

   if (largest != i)
   {
      tmp_key = h->nodes[largest]->key;
      tmp_data = h->nodes[largest]->data;
      tmp_i = h->nodes[largest]->i;
      h->nodes[largest]->key = h->nodes[i]->key;
      h->nodes[largest]->data = h->nodes[i]->data;
      h->nodes[largest]->i = h->nodes[i]->i;
      h->nodes[i]->key = tmp_key;
      h->nodes[i]->data = tmp_data;
      h->nodes[i]->i = tmp_i;

      heap_max_heapify (h, largest);
   }
   return HEAP_ERR_OK;
}


/**
 * @brief extract the maximum element from the heap
 *
 * @param[in] g The heap to operate on
 * @param[out] data The application object attached with the key
 * @param[out] key The application object key
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_extract_max (HEAP_T* h, void** data, unsigned long* key)
{
   if (h->type != DS_HEAP_MAX)
      return HEAP_ERR_WRONG_TYPE;

   if (h->heap_size < 1)
   {
      *data = NULL;
      return HEAP_ERR_UNDERFLOW;
   }
   *data = h->nodes[0]->data;
   *key =  h->nodes[0]->key;
   h->nodes[0]->data = h->nodes[h->heap_size-1]->data;
   h->nodes[0]->key = h->nodes[h->heap_size-1]->key;
   h->heap_size--;
   heap_max_heapify (h, 0);
   
   return HEAP_ERR_OK;
}

/**
 * @brief extract the maximum element from the heap
 *
 * @param[in] g The heap to operate on
 * @param[out] data The application object attached with the key
 * @param[out] key The application object key
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_extract_min (HEAP_T* h, void** data, unsigned long* key)
{
   if (h->type != DS_HEAP_MIN)
      return HEAP_ERR_WRONG_TYPE;

   if (h->heap_size < 1)
   {
      *data = NULL;
      return HEAP_ERR_UNDERFLOW;
   }
   *data = h->nodes[0]->data;
   *key =  h->nodes[0]->key;
   h->nodes[0]->data = h->nodes[h->heap_size-1]->data;
   h->nodes[0]->key = h->nodes[h->heap_size-1]->key;
   h->heap_size--;
   heap_min_heapify (h, 0);

   return HEAP_ERR_OK;
}


/**
 * @brief extract the maximum element from the heap
 *
 * @param[in] g The heap to operate on
 * @param[out] data The application object attached with the key
 * @param[out] key The application object key
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_minimum (HEAP_T* h, void** data, unsigned long* key)
{
   if (h->type != DS_HEAP_MIN)
      return HEAP_ERR_WRONG_TYPE;

   if (h->heap_size < 1)
   {
      *data = NULL;
      return HEAP_ERR_UNDERFLOW;
   }
   *data = h->nodes[0]->data;
   *key =  h->nodes[0]->key;
   return HEAP_ERR_OK;
}

/**
 * @brief extract the maximum element from the heap
 *
 * @param[in] g The heap to operate on
 * @param[out] data The application object attached with the key
 * @param[out] key The application object key
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_maximum (HEAP_T* h, void** data, unsigned long* key)
{
   if (h->type != DS_HEAP_MAX)
      return HEAP_ERR_WRONG_TYPE;

   if (h->heap_size < 1)
   {
      *data = NULL;
      return HEAP_ERR_UNDERFLOW;
   }
   *data = h->nodes[0]->data;
   *key =  h->nodes[0]->key;
   return HEAP_ERR_OK;
}

/**
 * @brief decrease the key value of a heap element
 *
 * @param[in] g The heap to operate on
 * @param[in] data The application object attached with the key
 * @param[in] key The application object key
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_decrease_key (HEAP_T* h, unsigned long i, unsigned long key)
{
   void* tmp_data;
   unsigned long tmp_key;
   unsigned long* tmp_i;
   
   if (DS_HEAP_MIN != h->type)
      return HEAP_ERR_WRONG_TYPE;

   if (key == HEAP_NIL_KEY)
      return HEAP_ERR_INVALID_KEY;

   if (HEAP_KEY(h, i) != HEAP_NIL_KEY && key > HEAP_KEY(h, i))
      return HEAP_ERR_LARGER_KEY;

   HEAP_KEY(h, i) = key;
   while (i > 0 && (HEAP_KEY(h, HEAP_PARENT(i)) > HEAP_KEY(h, i)))
   {
      tmp_key = h->nodes[i]->key;
      tmp_data = h->nodes[i]->data;
      tmp_i = h->nodes[i]->i;
      h->nodes[i]->key = h->nodes[HEAP_PARENT(i)]->key;
      h->nodes[i]->data = h->nodes[HEAP_PARENT(i)]->data;
      h->nodes[i]->i = h->nodes[HEAP_PARENT(i)]->i;
      h->nodes[HEAP_PARENT(i)]->key = tmp_key;
      h->nodes[HEAP_PARENT(i)]->data = tmp_data;
      h->nodes[HEAP_PARENT(i)]->i = tmp_i;
      i = HEAP_PARENT(i);
   }
   
   return HEAP_ERR_OK;
}

/**
 * @brief increase the key value of a heap element
 *
 * HEAP-INCREASE-KEY(A, i, key)
 * 1 if key < A[i]
 * 2   then error "new key is smaller than current key"
 * 3 A[i] <- key
 * 4 while i > 1 and A[PARENT(i)] < A[i]
 * 5     do exchange A[i] <-> A[PARENT(i)]
 * 6         i <- PARENT(i)
 * 
 * @param[in] g The heap to operate on
 * @param[in] data The application object attached with the key
 * @param[in] key The application object key
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_increase_key (HEAP_T* h, unsigned long i, unsigned long key)
{
   void* tmp_data;
   unsigned long tmp_key;

   if (DS_HEAP_MAX != h->type)
      return HEAP_ERR_WRONG_TYPE;

   if (key == HEAP_NIL_KEY)
      return HEAP_ERR_INVALID_KEY;
   
   if (HEAP_KEY(h, i) != HEAP_NIL_KEY && key < HEAP_KEY(h, i))
      return HEAP_ERR_SMALLER_KEY;
   
   HEAP_KEY(h, i) = key;
   while (i > 0 && (HEAP_KEY(h, HEAP_PARENT(i)) < HEAP_KEY(h, i)))
   {
      /*
        XXX: to-do: just swap the pointer instead
        void* tmp;

        tmp = h->nodes[i];
        h->nodes[i] = h->nodes[HEAP_PARENT(i)];
        h->nodes[HEAP_PARENT(i)] = tmp;
      */
      tmp_key = h->nodes[i]->key;
      tmp_data = h->nodes[i]->data;
      h->nodes[i]->key = h->nodes[HEAP_PARENT(i)]->key;
      h->nodes[i]->data = h->nodes[HEAP_PARENT(i)]->data;
      h->nodes[HEAP_PARENT(i)]->key = tmp_key;
      h->nodes[HEAP_PARENT(i)]->data = tmp_data;
      i = HEAP_PARENT(i);
   }
   
   return HEAP_ERR_OK;
}

/**
 * @brief add an element to the heap
 *
 * This routine adds a {key, data} pair to the heap. This routine is simply to
 * add the elements to the heap, it does heapify the heap h.
 *
 * @param[in] h The heap to build
 * @param[in] data Array of data elements
 * @param[in] num Number of array elements
 */
static HEAP_ERR_E heap_add (HEAP_T* h, unsigned long key, void* data, unsigned long* i)
{
   DS_HEAP_NODE_T* node;
   
   node = malloc (sizeof (DS_HEAP_NODE_T));
   if (NULL == node)
      return HEAP_ERR_ERR;
   
   node->data = data;
   node->key = key;
   *i = h->heap_size;
   node->i = i;
   h->nodes[h->heap_size] = node;
   h->heap_size++;

   return HEAP_ERR_OK;
}

/**
 * @brief insert an element in a max heap
 *
 * This routine inserts an element in the heap. The element is a {key,data}
 * pair.
 *
 * @param[in] h The heap to operate on
 * @param[in] key The element key component
 * @param[in] data The element data component
 * @param[out] i The updated heap index for the {key, data} will be stored here.
 * @return HEAP_ERR_E
 */
HEAP_ERR_E heap_max_insert (HEAP_T* h, unsigned long key, void* data, unsigned long* i)
{
   if (h->type != DS_HEAP_MAX)
      return HEAP_ERR_WRONG_TYPE;

   heap_add (h, HEAP_NIL_KEY, data, i);
   heap_increase_key (h, h->heap_size-1, key);
   return HEAP_ERR_OK;
}

/**
 *
 */
HEAP_ERR_E heap_min_insert (HEAP_T* h, unsigned long key, void* data, unsigned long* i)
{
   if (h->type != DS_HEAP_MIN)
      return HEAP_ERR_WRONG_TYPE;

   heap_add (h, HEAP_NIL_KEY, data, i);
   heap_decrease_key (h, h->heap_size-1, key);
   return HEAP_ERR_OK;
}

/**
 * @brief heapify heap data elements  
 *
 * This routine heapifies the heap elements in the heap h.
 *
 * @param[in] h The heap to build
 * @param[in] data Array of data elements
 * @param[in] num Number of array elements
 */
HEAP_ERR_E heap_build (HEAP_T* h)
{
   unsigned long i;
   HEAP_ERR_E err;
   
   for (i = h->heap_size/2; i >= 1; i--)
   {
      if (h->type == DS_HEAP_MAX)
      {
         if (HEAP_ERR_ERR == (err = heap_max_heapify (h, i-1)))
            return HEAP_ERR_ERR;
      }
      else
      {
         if (HEAP_ERR_ERR == (err = heap_min_heapify (h, i-1)))
            return HEAP_ERR_ERR;
      }
   }

   return HEAP_ERR_OK;
}
/**
 * @brief create and initialize a new heap
 *
 * This routine creates a new heap.
 *
 * @param[in] type The type of heap
 * @param[in] length The heap length.
 */
HEAP_T* heap_create (DS_HEAP_TYPE_E type, unsigned long length)
{
   HEAP_T* heap = malloc (sizeof (HEAP_T));

   if (NULL == heap)
      return NULL;
   heap->length = length;
   heap->heap_size = 0;
   heap->type = type;
   heap->nodes = malloc (length * sizeof (DS_HEAP_NODE_T*));
   if (NULL == heap->nodes)
   {
      free (heap);
      return NULL;
   }
   return heap;
}

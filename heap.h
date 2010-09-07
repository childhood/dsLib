/** @file heap.h
 * 
 * heap data structure and operations headers
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

typedef enum {DS_HEAP_MAX=1, DS_HEAP_MIN=2} DS_HEAP_TYPE_E;

typedef struct ds_heap_node {
   unsigned long key;
   void* data;
} DS_HEAP_NODE_T;

typedef struct ds_heap_t {
   unsigned long length;
   unsigned long heap_size;
   DS_HEAP_NODE_T** nodes;
   DS_HEAP_TYPE_E type;
} HEAP_T;

/* heap operation result code  */
typedef enum {
   HEAP_ERR_ERROR_HIGH = -512,   /* fencepost */
   HEAP_ERR_MALLOC_FAIL,
   HEAP_ERR_WRONG_TYPE,
   HEAP_ERR_UNDERFLOW,
   HEAP_ERR_ERR = -1,
   HEAP_ERR_OK = 0
} HEAP_ERR_E;

#define HEAP_PARENT(I)  ((I)/2)
#define HEAP_LEFT(I)    (2*(I) + 1)
#define HEAP_RIGHT(I)   (2*(I) + 2)

#define HEAP_KEY(H, I)     ((H)->nodes[I]->key)
#define HEAP_DATA(H, I)     ((H)->nodes[I]->data)

#define HEAP_NIL_KEY    ULONG_MAX
HEAP_T* heap_create (DS_HEAP_TYPE_E type, unsigned long length);
HEAP_ERR_E heap_build (HEAP_T* h);
HEAP_ERR_E heap_add (HEAP_T* h, unsigned long key, void* data);
HEAP_ERR_E heap_max_heapify (HEAP_T* h, unsigned long i);
HEAP_ERR_E heap_min_heapify (HEAP_T* h, unsigned long i);
void heap_dump (HEAP_T* h);

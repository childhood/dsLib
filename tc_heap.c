#include <stdio.h>
#include <heap.h>


/**
 * @brief test heap API
 *
 */
tc_heap_main (void)
{
//  int A[] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
//   int A[] = {1,2,3};
   int A[] = {12,11,10,9,6,7,8,5,1,4,14};
//   int A[] = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
  // int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8 ,7};
   HEAP_T* h;
   unsigned int length;
   unsigned int idx;
   unsigned long i;
   
   h = heap_create (DS_HEAP_MAX, 14);
   length = sizeof (A)/sizeof (int);
   for (idx = 0; idx < length; idx++)
   {
      if (HEAP_ERR_ERR == heap_max_insert (h, A[idx], NULL))
         fprintf (stderr, "error adding heap element\n");
   }
   //heap_build (h);
   heap_dump (h);
   heap_graphviz_description (h, "heap-max-heap-i.lst");

   heap_increase_key (h, 5, 16);
   heap_dump (h);
   heap_graphviz_description (h, "heap-max-heap-ii.lst");

   h = heap_create (DS_HEAP_MIN, 14);
   length = sizeof (A)/sizeof (int);
   for (idx = 0; idx < length; idx++)
   {
      if (HEAP_ERR_ERR == heap_min_insert (h, A[idx], NULL))
         fprintf (stderr, "error adding heap element\n");
   }
   //heap_build (h);
   heap_dump (h);
   heap_graphviz_description (h, "heap-min-heap.lst");


}

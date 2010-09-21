#include <stdio.h>
#include <heap.h>

typedef struct
   {
      unsigned long num;
      unsigned long idx;
} TC_HEAP_DATA_SET;

/**
 * @brief test heap API
 *
 */
tc_heap_max_main (void)
{
//  int A[] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
//   int A[] = {1,2,3};
   /*
   TC_HEAP_DATA_SET A[] = {{12,0},
                           {11,0},
                           {10,0},
                           {9,0},
                           {6,0},
                           {7,0},
                           {8,0},
                           {5,0},
                           {1,0},
                           {4,0},
                           {14,0}};
   */                           
   TC_HEAP_DATA_SET A[] = {{16, 0},
                            {4, 0},
                            {10, 0},
                            {14, 0},
                            {7, 0},
                            {9, 0},
                            {3, 0},
                            {2, 0},
                            {8, 0},
                            {1, 0}};
  // int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8 ,7};
   HEAP_T* h;
   unsigned int length;
   unsigned int idx;
   unsigned long i;
   
   h = heap_create (DS_HEAP_MAX, 14);
   length = sizeof (A)/sizeof (TC_HEAP_DATA_SET);
   for (idx = 0; idx < length; idx++)
   {
      if (HEAP_ERR_ERR == heap_max_insert (h, A[idx].num, NULL, &A[idx].idx))
         fprintf (stderr, "error adding heap element\n");
      //heap_dump(h);
   }
   //heap_build (h);
   heap_dump (h);
   heap_graphviz_description (h, "heap-max-heap-i.lst");
   for (idx = 0; idx < length; idx++)
   {
      fprintf (stderr, "FINAL -- A[idx].num = %lu A[idx].idx=%lu\n", A[idx].num, A[idx].idx);
   }
   
   heap_increase_key (h, 5, 16);
   heap_dump (h);
   heap_graphviz_description (h, "heap-max-heap-ii.lst");

   h = heap_create (DS_HEAP_MIN, 14);
   length = sizeof (A)/sizeof (TC_HEAP_DATA_SET);
   for (idx = 0; idx < length; idx++)
   {
      if (HEAP_ERR_ERR == heap_min_insert (h, A[idx].num, NULL, &A[idx].idx))
         fprintf (stderr, "error adding heap element\n");
   }
   //heap_build (h);
   heap_dump (h);
   heap_graphviz_description (h, "heap-min-heap.lst");


}


/**
 * @brief test heap API
 *
 */
tc_heap_min_main (void)
{
//  int A[] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
//   int A[] = {1,2,3};
   /*
   TC_HEAP_DATA_SET A[] = {{12,0},
                           {11,0},
                           {10,0},
                           {9,0},
                           {6,0},
                           {7,0},
                           {8,0},
                           {5,0},
                           {1,0},
                           {4,0},
                           {14,0}};
   */                           
   TC_HEAP_DATA_SET A[] = {{16, 0},
                            {4, 0},
                            {10, 0},
                            {14, 0},
                            {7, 0},
                            {9, 0},
                            {3, 0},
                            {2, 0},
                            {8, 0},
                            {1, 0}};
  // int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8 ,7};
   HEAP_T* h;
   unsigned int length;
   unsigned int idx;
   unsigned long i;
   
   h = heap_create (DS_HEAP_MIN, 14);
   length = sizeof (A)/sizeof (TC_HEAP_DATA_SET);
   for (idx = 0; idx < length; idx++)
   {
      if (HEAP_ERR_ERR == heap_min_insert (h, A[idx].num, NULL, &A[idx].idx))
         fprintf (stderr, "error adding heap element\n");
   }
   //heap_build (h);
   heap_dump (h);
   heap_graphviz_description (h, "heap-min-heap-i.lst");

   for (idx = 0; idx < length; idx++)
   {
      fprintf (stderr, "FINAL -- A[idx].num = %lu A[idx].idx=%lu\n", A[idx].num, A[idx].idx);
   }
   return;
   heap_decrease_key (h, 5, 16);
   heap_dump (h);
   heap_graphviz_description (h, "heap-min-heap-ii.lst");

   h = heap_create (DS_HEAP_MIN, 14);
   length = sizeof (A)/sizeof (TC_HEAP_DATA_SET);
   for (idx = 0; idx < length; idx++)
   {
      if (HEAP_ERR_ERR == heap_min_insert (h, A[idx].num, NULL, &A[idx].idx))
         fprintf (stderr, "error adding heap element\n");
   }
   //heap_build (h);
   heap_dump (h);
   heap_graphviz_description (h, "heap-min-heap.lst");

   for (idx = 0; idx < length; idx++)
   {
      fprintf (stderr, "FINAL -- A[idx].num = %lu A[idx].idx=%lu\n", A[idx].num, A[idx].idx);
   }

}


/**
 * @brief test heap API
 *
 */
tc_heap_min_ii_main (void)
{
//  int A[] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
//   int A[] = {1,2,3};
   /*
   TC_HEAP_DATA_SET A[] = {{12,0},
                           {11,0},
                           {10,0},
                           {9,0},
                           {6,0},
                           {7,0},
                           {8,0},
                           {5,0},
                           {1,0},
                           {4,0},
                           {14,0}};
   */                           
   TC_HEAP_DATA_SET A[] = {{16, 0},
                            {4, 0},
                            {10, 0},
                            {14, 0},
                            {7, 0},
                            {9, 0},
                            {3, 0},
                            {2, 0},
                            {8, 0},
                            {1, 0}};
  // int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8 ,7};
   HEAP_T* h;
   unsigned int length;
   unsigned int idx;
   unsigned long i;
   void* p;
   unsigned long key;
   char filename[128];

   h = heap_create (DS_HEAP_MIN, 14);
   length = sizeof (A)/sizeof (TC_HEAP_DATA_SET);
   for (idx = 0; idx < length; idx++)
   {
      if (HEAP_ERR_ERR == heap_min_insert (h, A[idx].num, NULL, &A[idx].idx))
         fprintf (stderr, "error adding heap element\n");
   }
   //heap_build (h);
   heap_dump (h);
   heap_graphviz_description (h, "heap-min-heap-i.lst");

   for (idx = 0; idx < length; idx++)
   {
      fprintf (stderr, "FINAL -- A[idx].num = %lu A[idx].idx=%lu\n", A[idx].num, A[idx].idx);
   }

   idx=0;
   while (HEAP_SIZE(h))
   {
      heap_extract_min (h, &p, &key);
      snprintf (filename, 128, "heap-min-heap-%d.lst", idx);
      heap_graphviz_description (h, filename);
      fprintf (stderr, "FINAL == %lu\n", key);
      idx++;
   }

}

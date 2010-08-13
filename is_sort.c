/* DESCRIPTION

*/

#include <stdio.h>

/*******************************************************************************
 *
 */
int iSort_c (void)
{

}

/*******************************************************************************
 *
 */
int iSort_s (void)
{

}

/*******************************************************************************
 *
 */
int iSort_i
(
int* arr,       /* array of integers to be sorted (R/W) */
size_t num     /* number of elements in the array */
)
{
   size_t i, j;
   int key;
   int ele;

   for (j = 0; j < num; j++)
   {
      key = *(arr+j);
      i = j - 1;
      ele = *(arr+i);
      while ((i > 0) && (key < ele))
         {
            *(arr+i+1) = ele;
            i--;
            ele = *(arr+i);
         }
      *(arr+i+1) = key;
   }
   return 0;
}

/*******************************************************************************
 *
 */
int is_sort_main (int argc, char** argv)
{
#define TEST_ISORT_BOUND   (1024*20)
   int arr[TEST_ISORT_BOUND];
   int idx;
   int val = 1;

   for (idx = TEST_ISORT_BOUND; idx >= 0; idx--)
   {
      arr[idx] = val;
      val++;
   }
   
   iSort_i (arr, TEST_ISORT_BOUND);

   for (idx = 0; idx < TEST_ISORT_BOUND; idx++)
   {
      fprintf (stdout, "%d\n", arr[idx]);
   }

}


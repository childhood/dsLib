/**
 * insertion sort
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

/**
 * @brief insertion sort
 *
 * This routine implements the insertion sort algorithm
 *
 * @param[in] arr array of integers to be sorted (R/W)
 * @param[in] num number of elements in the array
 * @return int 0 always
 */
int iSort_i (int* arr, size_t num)
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

/**
 * @brief insertion sort driver
 *
 * This routine implements a test driver for insertion sort
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
   return 0;
}


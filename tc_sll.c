/**
 * linked list data structure test cases
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

int tc_sll_main (int argc, char** argv)
{
   test_case_int_1 ();
   test_case_char ();
   test_case_int_2 ();
   test_case_int_3 ();
   return 0;
}

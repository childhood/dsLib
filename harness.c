
#include <stdio.h>
#include <ds_types.h>
#include <graph.h>
#include <graph_ops.h>

#define GRAPH_OPS_TEST
#ifdef GRAPH_OPS_TEST

/*******************************************************************************
* graph_main -
*
*       1---2  /3--/4 
*       |   | / | / |
*       |   |/  |/  |
*       5   6---7---8
*/

GPH_ERR_E matrix_main (void)
{
   void* vtx;
   char* saveptr = NULL;
   GRAPH_T* g;
   EDGE_T* e;
   unsigned long no;
   char* ctx = NULL;
   
   g = matrix_create (4, 4);
   graph_edge_print (g);
   graph_vertex_print (g);

   vtx = graph_vertex_find_i (g, 17);
   if (NULL == vtx)
   {
      fprintf (stderr, "vertext not found\n");
      return GPH_ERR_ERR;
   }
   no = 0;
   while (no < ((VTX_UD_T*)vtx)->no)
   {
      e = vertex_next_edge_get (g, vtx, &ctx);
      DEBUG_EDGE_PRINT_I(g,e);
      no++;
   }
   return GPH_ERR_OK;
}
#endif

int main (int argc, char** argv)
    {
       //graph_main();
       //sll_main ();
       //is_sort_main ();
       //queue_main ();
       matrix_main();
    }
    

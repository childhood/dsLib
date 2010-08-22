
#include <stdio.h>
#include <time.h>

#include <ds_types.h>
#include <graph.h>
#include <graph_ops.h>

#define GRAPH_OPS_TEST
#ifdef GRAPH_OPS_TEST

int bfs_vertex_func (void* vtx)
{
   fprintf (stdout, "vertex id=%lu\n", ((VTX_UD_T*)vtx)->id.iid);
}

static void vertex_print_2 (GRAPH_T* g)
{
   VTX_UD_T* vtx;
   VTX_EDGE* ve;
   
   vtx = graph_vertex_find_i (g, 7);
   ve = vtx->ELst;
   while (ve)
   {
      printf ("%s\n", (char*)ve->edge->aux);
      ve = ve->next;
   }
}

void bfs_main (void)
{
   GRAPH_T* g;
   void* vtx;
   EDGE_T* e;
   char* ctx = NULL;
   unsigned long no = 0;
   
   fprintf (stderr, "graph test #1\n");
   g = graph_new (GRAPH_UNDIRECTED_T, GRAPH_INT_T);
   fprintf (stderr, "* inserting e1(1,2)\n");
   graph_add_i (g, "e1", 1, NULL, 2, NULL, 1, DS_TRUE);
   fprintf (stderr, "* inserting e2(1,5)\n");   
   graph_add_i (g, "e2", 1, NULL, 5, NULL, 1, DS_TRUE);
   fprintf (stderr, "* inserting e3(2,6)\n");      
   graph_add_i (g, "e3", 2, NULL, 6, NULL, 1, DS_TRUE);
   fprintf (stderr, "* inserting e4(6,7)\n");         
   graph_add_i (g, "e4", 6, NULL, 7, NULL, 1, DS_TRUE);
   fprintf (stderr, "* inserting e5(3,7)\n");            
   graph_add_i (g, "e5", 3, NULL, 7, NULL, 1, DS_TRUE);
   fprintf (stderr, "* inserting e6(3,4)\n");            
   graph_add_i (g, "e6", 3, NULL, 4, NULL, 1, DS_TRUE);
   fprintf (stderr, "* inserting e7(7,8)\n");            
   graph_add_i (g, "e7", 7, NULL, 8, NULL, 1, DS_TRUE);
   fprintf (stderr, "* inserting e8(4,8)\n");            
   graph_add_i (g, "e8", 4, NULL, 8, NULL, 1, DS_TRUE);
   fprintf (stderr, "* inserting e9(6,3)\n");               
   graph_add_i (g, "e9", 6, NULL, 3, NULL, 1, DS_TRUE);
   fprintf (stderr, "* inserting e10(7,4)\n");               
   graph_add_i (g, "e10", 7, NULL, 4, NULL, 1, DS_TRUE);
   if (GPH_ERR_EDGE_EXISTS == graph_add_i (g, "e10", 4, NULL, 7, NULL, 1, DS_TRUE))
      fprintf (stderr, "edge exists\n");
   fprintf (stderr, "Done inserting edges\n");
   graph_edge_print (g);
   graph_vertex_print (g);

   vertex_print_2 (g);


   vtx = graph_vertex_find_i (g, 7);
   while (no < ((VTX_UD_T*)vtx)->no)
   {
      e = vertex_next_edge_get (g, vtx, &ctx);
      DEBUG_EDGE_PRINT_I(g,e);
      no++;
   }

   fprintf (stderr, "Starting BFS\n");
   bfs (g, 2, bfs_vertex_func);

   fprintf (stderr, "Starting DFS\n");
   dfs (g, 2, bfs_vertex_func);   
}
   
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
   
   g = matrix_create (100, 100);
   graph_edge_print (g);
   graph_vertex_print (g);

   vtx = graph_vertex_find_i (g, 1);
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
   fprintf (stderr, "Starting BFS\n");
   bfs (g, 100, bfs_vertex_func);

   //fprintf (stderr, "Starting DFS\n");
   //dfs (g, 2, bfs_vertex_func);
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
       //bfs_main ();
    }
    

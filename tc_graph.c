/**
 * graph test cases
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
#include <time.h>

#include <ds_types.h>
#include <graph.h>
#include <graph_ops.h>

void tc_graph_vertex_print (GRAPH_T* g)
{
   fprintf (stdout, "[List of vertices]\n");
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vtx = g->vLst;
      while (vtx)
      {
         fprintf (stdout, "v=%lu\n", vtx->id.iid);
         vtx = vtx->next;
      }
   }   
   else if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vtx = g->vLst;
      while (vtx)
      {
         fprintf (stdout, "v=%lu\n", vtx->id.iid);
         vtx = vtx->next;
      }
   }
}

void tc_graph_edge_print (GRAPH_T* g)
{
   EDGE_T* e = NULL;

   fprintf (stdout, "[List of edges]\n");
   while (NULL != (e = graph_edge_next_get (g, e)))
   {
      if (g->type == GRAPH_UNDIRECTED_T)
      {
         fprintf (stdout, "edge (%s) v1=%lu v2=%lu\n",
                  (char*)e->aux, 
                  ((VTX_UD_T*)e->v1)->id.iid,
                  ((VTX_UD_T*)e->v2)->id.iid);
      }
      else if (g->type == GRAPH_DIRECTED_T)
      {
         fprintf (stdout, "edge (%s) v1=%lu v2=%lu\n",
                  (char*)e->aux, 
                  ((VTX_D_T*)e->v1)->id.iid,
                  ((VTX_D_T*)e->v2)->id.iid);
      }
   }
}

int bfs_vertex_func (void* vtx)
{
   fprintf (stdout, "[BFS TC] vertex id=%lu\n", ((VTX_UD_T*)vtx)->id.iid);
   return 0;
}

int bfs_directed_func (void* vtx)
{
   fprintf (stdout, "[BFS TC] vertex id=%lu\n", ((VTX_D_T*)vtx)->id.iid);
   return 0;
}

static void vertex_print_3 (GRAPH_T* g)
{
   VTX_D_T* vtx;
   VTX_EDGE* ve;
   
   vtx = graph_vertex_find_i (g, 6);
   ve = vtx->outELst;
   while (ve)
   {
      printf ("%s\n", (char*)ve->edge->aux);
      ve = ve->next;
   }
}

static void vertex_print_2 (GRAPH_T* g)
{
   VTX_UD_T* vtx;
   VTX_EDGE* ve;
   
   vtx = graph_vertex_find_i (g, 6);
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
   //graph_edge_print (g);
   //graph_vertex_print (g);

   vertex_print_2 (g);


   vtx = graph_vertex_find_i (g, 7);
   while (no < ((VTX_UD_T*)vtx)->no)
   {
      e = graph_vertex_next_edge_get (g, vtx, &ctx);
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
   //char* saveptr = NULL;
   GRAPH_T* g;
   EDGE_T* e;
   unsigned long no;
   char* ctx = NULL;
   
   g = matrix_create (10, 10);
   //graph_edge_print (g);
   //graph_vertex_print (g);

   vtx = graph_vertex_find_i (g, 1);
   if (NULL == vtx)
   {
      fprintf (stderr, "vertext not found\n");
      return GPH_ERR_ERR;
   }
   no = 0;
   while (no < ((VTX_UD_T*)vtx)->no)
   {
      e = graph_vertex_next_edge_get (g, vtx, &ctx);
      DEBUG_EDGE_PRINT_I(g,e);
      no++;
   }
   fprintf (stderr, "Starting BFS\n");
   bfs (g, 100, bfs_vertex_func);

   tc_graph_edge_print (g);
   graphviz_description (g, "graph.lst");
   //fprintf (stderr, "Starting DFS\n");
   //dfs (g, 2, bfs_vertex_func);
   graph_delete (g);
   return GPH_ERR_OK;
}

   
/**
 * @brief Testing construction of a directed graph.
 *
 *       1-->2  ->3-->>4 
 *       |   | /  | /  |
 *       |   |/   |/   |
 *       v   v    v    v
 *       5   6--->7--->8
 *           |
 *           |
 *           V
 *           9
 */
void tc_directed_main (void)
{
   GRAPH_T* g;
   void* vtx;
   EDGE_T* e;
   char* ctx = NULL;
   unsigned long no = 0;
   
   fprintf (stderr, "graph test #1\n");
   g = graph_new (GRAPH_DIRECTED_T, GRAPH_INT_T);
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
   if (GPH_ERR_EDGE_EXISTS == graph_add_i (g, "e11", 4, NULL, 7, NULL, 1, DS_TRUE))
      fprintf (stderr, "edge exists\n");
   fprintf (stderr, "* inserting e10(7,4)\n");               
   graph_add_i (g, "e12", 6, NULL, 9, NULL, 1, DS_TRUE);
   
   fprintf (stderr, "Done inserting edges\n");
   tc_graph_edge_print (g);
   tc_graph_vertex_print (g);

   vertex_print_3 (g);
   //return (0);
   printf ("DDDD\n");
   vtx = graph_vertex_find_i (g, 6);
   printf ("DDDD = %lu\n", ((VTX_D_T*)vtx)->no);
   while (no < ((VTX_D_T*)vtx)->no)
   {
      e = graph_vertex_next_edge_get (g, vtx, &ctx);
      DEBUG_EDGE_PRINT_I(g,e);
      no++;
   }

   fprintf (stderr, "Starting BFS\n");
   bfs (g, 6, bfs_directed_func);

   fprintf (stderr, "Starting DFS\n");
   dfs (g, 2, bfs_directed_func);   
}

int sp_dj_cb (void* v)
{
   VTX_D_T* vtx = v;

   fprintf (stdout, "VID=%lu\n", vtx->id.iid);
}

/**
 * @brief Testing construction of a directed graph.
 *
 *       1-->2  ->3-->>4 
 *       |   | /  | /  |
 *       |   |/   |/   |
 *       v   v    v    v
 *       5   6--->7--->8
 *           |
 *           |
 *           V
 *           9
 */
void tc_dj_main (void)
{
   GRAPH_T* g;
   
   fprintf (stderr, "graph test #1\n");
   g = graph_new (GRAPH_DIRECTED_T, GRAPH_INT_T);
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
   if (GPH_ERR_EDGE_EXISTS == graph_add_i (g, "e11", 4, NULL, 7, NULL, 1, DS_TRUE))
      fprintf (stderr, "edge exists\n");
   fprintf (stderr, "* inserting e10(6,9)\n");               
   graph_add_i (g, "e12", 6, NULL, 9, NULL, 1, DS_TRUE);
   
   fprintf (stderr, "Done inserting edges\n");
   tc_graph_edge_print (g);
   tc_graph_vertex_print (g);

   fprintf (stderr, "Starting Dijkstra's\n");
   sp_dijkstra (g, 1,  sp_dj_cb);


}

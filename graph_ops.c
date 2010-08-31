/**
 * Operations on graphs
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
#include <assert.h>
#include <time.h>
#include <string.h>

#include <ds_types.h>
#include <queue.h>
#include <graph.h>
#include <graph_ops.h>

/**
 *
 */

GPH_ERR_E graphviz_description
(
GRAPH_T* g,
char* filename
)
{
   EDGE_T* e = NULL;
   FILE* fp;

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
         return GPH_ERR_ERR;
   }
   
   fprintf (fp, "graph G {\n");
   fprintf (fp, "node [shape = circle, style=filled];\n");
   fprintf (fp, "rankdir=LR;\n");
   fprintf (fp, "size=\"12,8\"\n");   
   while (NULL != (e = graph_edge_next_get (g, e)))
   {
      fprintf (fp, "\t%lu -- %lu;\n", ((VTX_UD_T*)e->v1)->id.iid,
               ((VTX_UD_T*)e->v2)->id.iid);
   }
   fprintf (fp, "}\n");

   if (NULL != filename)
      fclose (fp);
   
   return GPH_ERR_OK;
}

/**
 * This routine creates an NxM graph and returns it to the user.
 *
 * @param [in] N the number of rows in the matrix
 * @param [in] M the numner of columns in the matrix
 * @return A valid GRAPH_T* if successful, NULL otherwise
 */
GRAPH_T* matrix_create
    (
    const unsigned long N,
    const unsigned long M
    )
    {
    unsigned long vid;
    //unsigned long tmp;
#define label "edge"    
    GRAPH_T* matrix;
    
    if (NULL == (matrix = graph_new (GRAPH_UNDIRECTED_T, GRAPH_INT_T)))
        return NULL;
    
    for (vid = 1; vid <= N*M; vid++) /**< generate integer vertex indices */
    {
       /**< creating the left-right edges */
       if (vid%M != 1)               
          graph_add_i (matrix, label, vid, NULL, vid-1, NULL, 1, DS_TRUE);
       /**< creating the right edge */
       //if (vid%M != 0)
       // graph_add_i (matrix, label, vid, NULL, vid+1, NULL, 1, DS_TRUE);
        /**< creating the up edge */
       //if (vid > M)
       // graph_add_i (matrix, label, vid, NULL, vid-M, NULL, 1, DS_TRUE);
       /**< creating the up-down edge */
       if (vid <= (M*(N-1)))
          graph_add_i (matrix, label, vid, NULL, vid+M, NULL, 1, DS_TRUE);        
    }
    return matrix;
    }

GPH_ERR_E bfs_directed
(
GRAPH_T* g,
unsigned long vid,
BFS_FUNCPTR_T func
)
{
   void* vtx = NULL;
   QUEUE_T* q;
   QUEUE_ERR_E err;
   DS_BFS_AUX_T* aux;
   void* svtx;
   char* ctx = NULL;
   void* vvtx;
   void* uvtx;
   int no;
   
   svtx = graph_vertex_find_i (g, vid);   
   while (NULL != (vtx = graph_vertex_next_vertex_get (g, vtx)))
   {
      aux = malloc (sizeof (DS_BFS_AUX_T));
      if (NULL == aux)
         return GPH_ERR_ERR;
      aux->color = DS_BFS_WHITE;
      aux->distance = -1;
      ((VTX_D_T*)vtx)->aux = aux;
   }
   aux = ((VTX_D_T*)svtx)->aux;
   aux->color = DS_BFS_WHITE;
   aux->distance = 0;
   
   q = queue_create (VPDATA, g->v_no);
   if (NULL == q)
   {
      assert (0); /* for now */
      /* XXX: todo */
   }
   queue_enqueue_vp (q, svtx);
   while (DS_NO == queue_is_empty(q))
   {
      uvtx = queue_dequeue_vp (q, &err);
      no = ((VTX_D_T*)uvtx)->no;
      printf ("t =%lu", no);
      while (no)
      {
         vvtx = graph_vertex_next_adj_get (g, uvtx, &ctx);
         aux = ((VTX_D_T*)vvtx)->aux;
         if (aux->color == DS_BFS_WHITE)
         {
            aux->color = DS_BFS_GRAY;
            aux->distance = ((DS_BFS_AUX_T*)((VTX_D_T*)uvtx)->aux)->distance + 1;
            queue_enqueue_vp (q, vvtx);
         }
         no--;
      }
      func (uvtx);
      ((DS_BFS_AUX_T*)((VTX_D_T*)uvtx)->aux)->color = DS_BFS_BLACK;
   }

   vtx = NULL;
   while (NULL != (vtx = graph_vertex_next_vertex_get (g, vtx)))
   {
      free (((VTX_D_T*)vtx)->aux);
   }
   return GPH_ERR_OK;
}

GPH_ERR_E bfs_undirected
(
GRAPH_T* g,
unsigned long vid,
BFS_FUNCPTR_T func
)
{
   void* vtx = NULL;
   QUEUE_T* q;
   QUEUE_ERR_E err;
   DS_BFS_AUX_T* aux;
   void* svtx;
   char* ctx = NULL;
   void* vvtx;
   void* uvtx;
   int no;
   
   svtx = graph_vertex_find_i (g, vid);   
   while (NULL != (vtx = graph_vertex_next_vertex_get (g, vtx)))
   {
      aux = malloc (sizeof (DS_BFS_AUX_T));
      if (NULL == aux)
         return GPH_ERR_ERR;
      aux->color = DS_BFS_WHITE;
      aux->distance = -1;
      ((VTX_UD_T*)vtx)->aux = aux;
   }
   aux = ((VTX_UD_T*)svtx)->aux;
   aux->color = DS_BFS_WHITE;
   aux->distance = 0;
   
   q = queue_create (VPDATA, g->v_no);
   if (NULL == q)
   {
      assert (0); /* for now */
      /* XXX: todo */
   }
   queue_enqueue_vp (q, svtx);
   while (DS_NO == queue_is_empty(q))
   {
      uvtx = queue_dequeue_vp (q, &err);
      no = ((VTX_UD_T*)uvtx)->no;
      while (no)
      {
         vvtx = graph_vertex_next_adj_get (g, uvtx, &ctx);
         aux = ((VTX_UD_T*)vvtx)->aux;
         if (aux->color == DS_BFS_WHITE)
         {
            aux->color = DS_BFS_GRAY;
            aux->distance = ((DS_BFS_AUX_T*)((VTX_UD_T*)uvtx)->aux)->distance + 1;
            queue_enqueue_vp (q, vvtx);
         }
         no--;
      }
      func (uvtx);
      ((DS_BFS_AUX_T*)((VTX_UD_T*)uvtx)->aux)->color = DS_BFS_BLACK;
   }

   vtx = NULL;
   while (NULL != (vtx = graph_vertex_next_vertex_get (g, vtx)))
   {
      free (((VTX_UD_T*)vtx)->aux);
   }
   return GPH_ERR_OK;
}

/**
 * @code
 * BFS(G, s)
 *  1  for each vertex u <- V [G] - {s}
 *  2       do color[u] <- WHITE
 *  3          d[u] <- 8
 *  4          p[u] <- NIL
 *  5  color[s] <- GRAY
 *  6  d[s] <- 0
 *  7  p[s] <- NIL
 *  8  Q <- Ø
 *  9  ENQUEUE(Q, s)
 * 10  while Q != Ø
 * 11      do u <- DEQUEUE(Q)
 * 12         for each v <- Adj[u]
 * 13             do if color[v] = WHITE
 * 14                   then color[v] <- GRAY
 * 15                        d[v] <- d[u] + 1
 * 16                        p[v] <- u
 * 17                        ENQUEUE(Q, v)
 * 18         color[u] <- BLACK
 * @endcode
 */

GPH_ERR_E bfs
(
GRAPH_T* g,
unsigned long vid,
BFS_FUNCPTR_T func
)
{
   GPH_ERR_E err;
   
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      err = bfs_undirected (g, vid, func);
   }
   else if (g->type == GRAPH_DIRECTED_T)
   {
      err = bfs_directed (g, vid, func);
   }

   return err;
}

/**
 *
 */
static void dfs_visit_undirected
(
GRAPH_T* g,
void* uvtx,
DFS_FUNCPTR_T func
)
{
   struct timespec tp;
   char* ctx = NULL;
   unsigned int no;
   void* vvtx;

   UD_AUX_COLOR(uvtx) = DS_DFS_GRAY;
   //((DS_DFS_AUX_T*)((VTX_D_T*)uvtx)->aux)->color = DS_DFS_GRAY;
   clock_gettime (CLOCK_MONOTONIC, &tp);
   memcpy (&((DS_DFS_AUX_T*)((VTX_UD_T*)uvtx)->aux)->d_time, &tp,
           sizeof (struct timespec));

   no = ((VTX_UD_T*)uvtx)->no;
   while (no)
   {
      vvtx = graph_vertex_next_adj_get (g, uvtx, &ctx);
      if (((DS_DFS_AUX_T*)((VTX_UD_T*)vvtx)->aux)->color == DS_DFS_WHITE)
      {
         dfs_visit_undirected (g, vvtx, func);
      }
      no--;
   }
   ((DS_DFS_AUX_T*)((VTX_UD_T*)uvtx)->aux)->color = DS_DFS_BLACK;
   clock_gettime (CLOCK_MONOTONIC, &tp);
   memcpy (&((DS_DFS_AUX_T*)((VTX_UD_T*)uvtx)->aux)->f_time, &tp,
           sizeof (struct timespec));
   func (uvtx);
}

/**
 *
 */
static void dfs_visit_directed
(
GRAPH_T* g,
void* uvtx,
DFS_FUNCPTR_T func
)
{
   struct timespec tp;
   char* ctx = NULL;
   unsigned int no;
   void* vvtx;

   ((DS_DFS_AUX_T*)((VTX_D_T*)uvtx)->aux)->color = DS_DFS_GRAY;
   clock_gettime (CLOCK_MONOTONIC, &tp);
   memcpy (&((DS_DFS_AUX_T*)((VTX_D_T*)uvtx)->aux)->d_time, &tp,
           sizeof (struct timespec));

   no = ((VTX_D_T*)uvtx)->no;
   while (no)
   {
      vvtx = graph_vertex_next_adj_get (g, uvtx, &ctx);
      if (((DS_DFS_AUX_T*)((VTX_D_T*)vvtx)->aux)->color == DS_DFS_WHITE)
      {
         dfs_visit_directed (g, vvtx, func);
      }
      no--;
   }
   ((DS_DFS_AUX_T*)((VTX_D_T*)uvtx)->aux)->color = DS_DFS_BLACK;
   clock_gettime (CLOCK_MONOTONIC, &tp);
   memcpy (&((DS_DFS_AUX_T*)((VTX_D_T*)uvtx)->aux)->f_time, &tp,
           sizeof (struct timespec));
   func (uvtx);
}

/**
 *
 * Dfs(G)
 * 1  for each vertex u in V [G]
 * 2       do color[u] <- WHITE
 * 3          p[u] <- NIL
 * 4  time <- 0
 * 5  for each vertex u in V [G]
 * 6       do if color[u] = WHITE
 * 7             then DFS-VISIT(u)
 * 
 * DFS-VISIT(u)
 * 1  color[u] <- GRAY     <-White vertex u has just been discovered.
 * 2  time <- time +1
 * 3  d[u] time
 * 4  for each v in Adj[u]  >> Explore edge(u, v).
 * 5       do if color[v] = WHITE
 * 6             then p[v] <- u
 * 7                         DFS-VISIT(v)
 * 8  color[u] BLACK      >> Blacken u; it is finished.
 * 9  f [u] <- time <- time +1
 * 
 */

GPH_ERR_E dfs
(
GRAPH_T* g,
unsigned long vid,
DFS_FUNCPTR_T func
)
{
   void* vtx;
   DS_DFS_AUX_T* aux;

   vtx = NULL;
   while (NULL != (vtx = graph_vertex_next_vertex_get (g, vtx)))
   {
      aux = malloc (sizeof (DS_DFS_AUX_T));
      if (NULL == aux)
         return GPH_ERR_ERR;
      aux->color = DS_DFS_WHITE;
      if (g->type == GRAPH_UNDIRECTED_T)
      {
         ((VTX_UD_T*)vtx)->aux = aux;
      }
      else if (g->type == GRAPH_DIRECTED_T)
      {
         ((VTX_D_T*)vtx)->aux = aux;
      }

   }
   vtx = NULL;
   while (NULL != (vtx = graph_vertex_next_vertex_get (g, vtx)))
   {
      if (g->type == GRAPH_UNDIRECTED_T)
      {
         if (((DS_DFS_AUX_T*)((VTX_UD_T*)vtx)->aux)->color == DS_DFS_WHITE)
            dfs_visit_undirected (g, vtx, func);
      }
      else if (g->type == GRAPH_DIRECTED_T)
      {
         if (((DS_DFS_AUX_T*)((VTX_D_T*)vtx)->aux)->color == DS_DFS_WHITE)
            dfs_visit_directed (g, vtx, func);         
      }

   }
   return GPH_ERR_OK;
}

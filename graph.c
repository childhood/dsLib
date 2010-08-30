/*  Copyright 2010 Gaurav Mathur

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ds_types.h>
#include <graph.h>

/*!
 * This
 *
 */
GRAPH_T* graph_duplicate
(
GRAPH_T* g
)
{
   GRAPH_T* dup_g;

   if (NULL == (dup_g = graph_new (g->type, g->label_type)))
   {
      return NULL;
   }
   /* XXX: todo */
   return NULL;
}

/*!
 * This
 *
 */
unsigned long graph_edges_no_get
(
GRAPH_T* g,
void* v
)
{
   unsigned long no = 0;
   
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      no = ((VTX_UD_T*)v)->no;
   }
   else if (g->type == GRAPH_DIRECTED_T)
   {
      no = ((VTX_D_T*)v)->no;
   }
   return no;
}

/*******************************************************************************
* graph_edge_print - display all the edges of a graph
*
* RETURNS: 
*/

EDGE_T* graph_edge_next_get
(
GRAPH_T* g,
EDGE_T* e
)
{
   if (e == NULL)
   {
      e = g->eLst;
   }
   else
   {
      e = e->next;
   }
   return e;
}

/*******************************************************************************
* vertex_insert - insert a vertext in the graph
*
* RETURNS: 
*/

void graph_vertex_print (GRAPH_T* g)
{
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
         vtx = vtx->next;
      }
   }
}

/*******************************************************************************
* vertex_next_adj_get - 
*
*
* RETURNS: 
*/

void* vertex_next_adj_get
(
GRAPH_T* g,     /* graph to operate on */
void* v,        /* vertext to operate on */
char** ctx  /* saved pointer */
)
{
   void* vtx1;
   void* vtx2;
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      if (NULL == *ctx)
      {
         *ctx = (char*)((VTX_UD_T*)v)->ELst->next;
         vtx1 = ((VTX_UD_T*)v)->ELst->edge->v1;
         vtx2 = ((VTX_UD_T*)v)->ELst->edge->v2;
      }
      else
      {
         EDGE_T* e;
         e = ((VTX_EDGE*)*ctx)->edge;
         *ctx = (char*)((VTX_EDGE*)*ctx)->next;
         vtx1 = e->v1;
         vtx2 = e->v2;
      }
      return (vtx1==v)?vtx2:vtx1;      
   }
   else
   if (g->type == GRAPH_DIRECTED_T)
   {
      /* XXX: todo */
   }
   return NULL;
}

/*******************************************************************************
* vertex_next_edge_get - insert a vertext in the graph
*
* This routine returns the next edge in the list of edges incident to vertex
* <v>. This routine is designed to work inside loop constructs in cases where
* you would want to iterate over all the vertex edges. <ctx> maintains the
* context between each iteration. The contents of <ctx> need to be
* initialied to NULL before the first invocation of this routine.
*
* RETURNS: A valid EDGE_T* pointer or NULL
*/

EDGE_T* vertex_next_edge_get
(
GRAPH_T* g,     /* graph to operate on */
void* v,        /* vertext to operate on */
char** ctx  /* saved pointer */
)
{
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      if (NULL == *ctx)
      {
         *ctx = (char*)((VTX_UD_T*)v)->ELst->next;
         return ((VTX_UD_T*)v)->ELst->edge;
      }
      else
      {
         EDGE_T* e;
         e = ((VTX_EDGE*)*ctx)->edge;
         *ctx = (char*)((VTX_EDGE*)*ctx)->next;
         return e;
      }
   }
   else
   if (g->type == GRAPH_DIRECTED_T)
   {
      /* XXX: todo */
   }
   return NULL;
}

/*******************************************************************************
* vertex_next_edge_get - insert a vertext in the graph
*
* This routine returns the next edge in the list of edges incident to vertex
* <v>. This routine is designed to work inside loop constructs in cases where
* you would want to iterate over all the vertex edges. <ctx> maintains the
* context between each iteration. The contents of <ctx> need to be
* initialied to NULL before the first invocation of this routine.
*
* RETURNS: A valid EDGE_T* pointer or NULL
*/

void* vertex_next_vertex_get
(
GRAPH_T* g,     /* graph to operate on */
void* v        /* vertext to operate on */
)
{
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      if (NULL == v)
      {
         return g->vLst;
      }
      else
      {
         return ((VTX_UD_T*)v)->next;
      }
   }

   if (g->type == GRAPH_DIRECTED_T)
   {
      if (NULL == v)
      {
         return g->vLst;
      }
      else
      {
         return ((VTX_D_T*)v)->next;
      }
   }
   /* should never reach here */
   return NULL;
}
   
/*******************************************************************************
* edge_remove - 
*
* RETURNS: 
*/
   
static GPH_ERR_E vertex_remove
(
GRAPH_T* g,
void* vtx
)
{
   void* iter_vtx;
   void* prev_iter_vtx = NULL;
   void* tmp_vtx;
   
   iter_vtx = g->eLst;
   while (iter_vtx)
   {
      if (iter_vtx == vtx)
      {
         if (NULL == prev_iter_vtx)
         {
            tmp_vtx = g->eLst;
            g->eLst = g->eLst->next;
            free (tmp_vtx);
         }
         else
         {
            if (g->type == GRAPH_UNDIRECTED_T)
            {
               prev_iter_vtx = ((VTX_UD_T*)iter_vtx)->next;
               free (iter_vtx);
            }
            if (g->type == GRAPH_DIRECTED_T)
            {
               prev_iter_vtx = ((VTX_D_T*)iter_vtx)->next;
               free (iter_vtx);
            }
         }
         break;
      }
      if (g->type == GRAPH_UNDIRECTED_T)
      {
         iter_vtx = ((VTX_UD_T*)iter_vtx)->next;
      }
      if (g->type == GRAPH_DIRECTED_T)
      {
         iter_vtx = ((VTX_D_T*)iter_vtx)->next;
          }
   }       
   return GPH_ERR_OK;
}

/*******************************************************************************
* graph_vertex_next_get - get the next vertex object in the graph
*
* This routines returns the next vertex to <vtx> in the graph <g>. This
* routine would be typically used inside loops constructs where you would want
* to iterate over all the vertices in the graph.
*
* RETURNS: A valid vertext pointer or NULL (signifying end of list).
*/

void* graph_vertex_next_get
(
GRAPH_T* g,
void* vtx
)
{
   if (g->type == GRAPH_UNDIRECTED_T)
      return ((VTX_UD_T*)vtx)->next;
   else if (g->type == GRAPH_DIRECTED_T)
      return ((VTX_D_T*)vtx)->next;   
   else
      return NULL;
}

/*******************************************************************************
* graph_vertex_find_i - find a vertex object given it's integer identifier
*
* This routine returns the vertex object for the integer vertex identifier
* <vid> in graph <g>.
*
* RETURNS: A valid vertex object pointer or NULL if no vertex found
*/

void* graph_vertex_find_i
(
GRAPH_T* g,             /* graph to operate on */
unsigned long vid       /* interger vertex identifier */
)
{
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vtx = g->vLst;
      
      while (NULL != vtx)
      {
         if (vtx->id.iid == vid)
         {
            return vtx;
         }
         vtx = vtx->next;
      }
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vtx = g->vLst;
      
      while (NULL != vtx)
      {
         if (vtx->id.iid == vid)
            return vtx;
         vtx = vtx->next;
      }
   }
   return NULL;
}

/*******************************************************************************
* graph_vertex_find_c - find a vertex identifier given it's string label  
*
* RETURNS: 1 if the vertex exists, 0 if not
*/

void* graph_vertex_find_c
    (
    GRAPH_T* g,
    char* vid
    )
{
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vtx = g->vLst;
      while (NULL != vtx)
      {
         if (strcmp (vtx->id.cid, vid))
            return vtx;
      }
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vtx = g->vLst;
      while (NULL != vtx)
      {
         if (strcmp (vtx->id.cid, vid))
            return vtx;
      }
   }
   return NULL;
}

/**
 *
 */

static TRUTH_E graph_edge_exists_undirected
(
GRAPH_T* g,     /* graph to operate on */
VTX_UD_T* v1,   /* edge vertex #1 */
VTX_UD_T* v2    /* edge vertex #2 */
)
{
   unsigned long no;
   char* ctx = NULL;
   EDGE_T* e;
   
   if (v1->no < v2->no)
   {
      no = 0;
      while (no < v1->no)
      {
         e = vertex_next_edge_get (g, v1, &ctx);
         if (e->v1 == v2 || e->v2 == v2)
            return DS_YES;
         no++;
      }
   }
   else
   {
      no = 0;
      while (no < v2->no)
      {
         e = vertex_next_edge_get (g, v2, &ctx);
         if (e->v1 == v1 || e->v2 == v1)
            return DS_YES;
         no++;
      }
   }
   return DS_NO;
}

/**
 *
 */

static TRUTH_E graph_edge_exists_directed
(
GRAPH_T* g,     /* graph to operate on */
VTX_D_T* v1,    /* edge vertex #1 */
VTX_D_T* v2     /* ed */
)
{
   return DS_NO;
}

/**
 * This routine finds out if an edge exists between two vertices. For a
 * directed graph it takes into account direction of the edge too.
 *
 * 
 */

TRUTH_E graph_edge_exists
(
GRAPH_T* g,
void* v1,
void* v2
)
{
   if (g->type == GRAPH_DIRECTED_T)
   {
      return graph_edge_exists_directed (g, v1, v2);
   }
   else if (g->type == GRAPH_UNDIRECTED_T)
   {
      return graph_edge_exists_undirected (g, v1, v2);
   }
   /* should never reach here */
   return DS_NO;
}

/*******************************************************************************
* graph_v_insert - insert a new edge into the graph
*
* RETURNS: A valid vertex node if created or present, NULL on error 
*/

static GPH_ERR_E graph_add_edge_to_vertices
(
GRAPH_T* g,
EDGE_T* edge,    
void* v1,
void* v2
)
{
   VTX_EDGE* ve;
   
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vtx = v1;

      ve = malloc (sizeof (VTX_EDGE));
      if (NULL == ve)
         return GPH_ERR_ERR;
      ve->edge = edge;
      ve->next = NULL;
      
      if (NULL == vtx->ELst)
      {
         vtx->ELst = ve;
         vtx->last_edge = ve;
      }
      else
      {
         vtx->last_edge->next = ve;
         vtx->last_edge = ve;
      }
      vtx->no++;
      
      ve = malloc (sizeof (VTX_EDGE));
      if (NULL == ve)
         return GPH_ERR_ERR;
      ve->edge = edge;
      ve->next = NULL;

      
      vtx = v2;
      if (NULL == vtx->ELst)
      {
         vtx->ELst = ve;
         vtx->last_edge = ve;
      }
      else
      {
         vtx->last_edge->next = ve;
         vtx->last_edge = ve;
      }
      vtx->no++;
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vtx1 = v1;
      VTX_D_T* vtx2 = v2;

   ve = malloc (sizeof (VTX_EDGE));
   if (NULL == ve)
      return GPH_ERR_ERR;
   ve->edge = edge;
   ve->next = NULL;

      
      if (NULL == vtx1->outELst)
      {
         vtx1->outELst = ve;
         vtx1->last_out_edge = ve;
      }
      else
      {
         vtx1->last_out_edge->next = ve;
         vtx1->last_out_edge = ve;
      }

   ve = malloc (sizeof (VTX_EDGE));
   if (NULL == ve)
      return GPH_ERR_ERR;
   ve->edge = edge;
   ve->next = NULL;

      
      if (NULL == vtx2->inELst)
      {
         vtx2->inELst = ve;
         vtx2->last_in_edge = ve;
      }
      else
      {
         vtx2->last_in_edge->next = ve;
         vtx2->last_in_edge = ve;
      }
   }
   return GPH_ERR_OK;
}

/*******************************************************************************
* vertex_insert - insert a vertext in the graph
*
* RETURNS: 
*/

static GPH_ERR_E vertex_insert
(
GRAPH_T* g,
void* vtx
)
{
   if (NULL == g)
      return GPH_ERR_ERR;
   
   if (NULL == g->vLst)
   {
      g->last_vertex = vtx;
      g->vLst = vtx;
   }
   else
   {
      if (g->type == GRAPH_UNDIRECTED_T)
      {         
         VTX_UD_T* lvtx = g->last_vertex;
         lvtx->next = vtx;
         g->last_vertex = vtx;
      }
      if (g->type == GRAPH_DIRECTED_T)
      {
         VTX_D_T* lvtx = g->last_vertex;
         lvtx->next = vtx;
         g->last_vertex = vtx;
      }
   }
   g->v_no++;
   return GPH_ERR_OK;
}

/**
 * Creates a new graph vertex given an integer vertex identifier. If a vertex
 * with the specified vertex identifier exists, the routine will return a
 * vertex object for that identifier.
 *
 * @param[in] g    The graph to operate on
 * @param[in] vid  An integer vertex identifier
 * @param[in] info User-specified information that can be attached to the
 *                 vertex
 * @return A valid vertex node if created or present, NULL on error 
 */
void* graph_v_create_i
(
GRAPH_T* g,         
unsigned long vid,  
void* info          
)
{
   void* v;

   /* Find out of a vertex object exists with the given vid */
   if (NULL != (v = graph_vertex_find_i (g, vid)))
   {
      return v;
   }
   
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vtx;
      
      if (NULL == (vtx = malloc (sizeof (VTX_UD_T))))
         return NULL;
      vtx->ELst = NULL; 
      vtx->next = NULL;
      vtx->no = 0;
      vtx->id.iid = vid;
      vtx->aux = info;
      vertex_insert (g, vtx);
      return vtx;
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vtx;
      if (NULL == (vtx = malloc (sizeof (VTX_UD_T))))
         return NULL;

      vtx->outELst = NULL;
      vtx->inELst = NULL;
      vtx->next = NULL;
      vtx->no = 0;
      vtx->id.iid = vid;
      vtx->aux = info;
      vertex_insert (g, vtx);
      return vtx;
   }
   return NULL;
}

/*******************************************************************************
* graph_v_create_c - create a vertex given a textual vertex identifier
*
* This routine creates a new vertext given a string vertex identifier
* <v>. <info> specifies the aux. information that we might need to attach to
* the graph.
*
* RETURNS: Created vertext if successful, NULL otherwise
*/

static void* graph_v_create_c
(
GRAPH_T* g,
char* v,
void* info
)
{
   void* vtx;
   if (NULL != (vtx = graph_vertex_find_c (g, v)))
      return vtx;
   
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vtx;
      
      if (NULL == (vtx = malloc (sizeof (VTX_UD_T))))
         return NULL;
      vtx->ELst = NULL;
      vtx->next = NULL;
      vtx->no = 0;
      vtx->id.cid = malloc (strlen (v) + 1);
      strcpy (vtx->id.cid, v);
      vtx->aux = info;
      vertex_insert (g, vtx);
      return vtx;
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vtx;
      if (NULL == (vtx = malloc (sizeof (VTX_UD_T))))
         return NULL;
      
      vtx->outELst = NULL;
      vtx->inELst = NULL;
      vtx->next = NULL;
      vtx->no = 0;
      vtx->id.cid = malloc (strlen (v) + 1);
      strcpy (vtx->id.cid, v);
      vtx->aux = info;
      vertex_insert (g, vtx);
   }
   
   return NULL;    
}

/*******************************************************************************
* graph_v_remove_i - remove a integer lable vertex from the graph 
*
* RETURNS: GPH_ERR_E 
*/

static GPH_ERR_E graph_v_remove_i
    (
    GRAPH_T* g,         /* graph to add vertex to */
    unsigned long v     /* vertext identifier */
    )
{
    return GPH_ERR_OK;    
    }

/*******************************************************************************
* edge_remove - 
*
* RETURNS: 
*/

static GPH_ERR_E edge_remove
(
GRAPH_T* g,
EDGE_T* edge
)
{
   EDGE_T* iter_edge;
   EDGE_T* prev_iter_edge = NULL;
   EDGE_T* tmp_edge;
   
   iter_edge = g->eLst;
   while (iter_edge)
   {
      if (iter_edge == edge)
      {
         if (NULL == prev_iter_edge)
         {
            tmp_edge = g->eLst;
            g->eLst = g->eLst->next;
            free (tmp_edge);
         }
         else
         {
            prev_iter_edge = iter_edge->next;
            free (iter_edge);
         }
         break;
      }
      iter_edge = iter_edge->next;
   }       
   return GPH_ERR_OK;
}

/*******************************************************************************
* graph_v_add_c - add a new 
*
* RETURNS: 
*/

static GPH_ERR_E graph_v_remove_c
    (
    GRAPH_T* g,
    char* v
    )
    {

    return GPH_ERR_OK;
    }

/*******************************************************************************
* graph_remove_i - 
*
*
* RETURNS: GPH_ERR_E
*/

GPH_ERR_E graph_remove_i
(
GRAPH_T* g,
unsigned long v1,       /* integer vertex identifier. */
unsigned long v2       /* integer vertex identifier. */
)
{
   return GPH_ERR_ERR;   
}

/*******************************************************************************
* edge_insert - insert an edge in the graph
*
* This routine inserts a newly created edge <edge> into the list of edges in
* the graph <g>.
*
* RETURNS: GPH_ERR_ERR if successful, GPH_ERR_OK if not.
*/

static GPH_ERR_E edge_insert
(
GRAPH_T* g,
EDGE_T* edge
)
{
   if (NULL == g)
      return GPH_ERR_ERR;
   
   if (NULL == g->eLst)
   {
      g->last_edge = edge;
      g->eLst = edge;
   }
   else
   {
      g->last_edge->next = edge;
      g->last_edge = edge;
   }
   g->e_no++;
   return GPH_ERR_OK;
}

/*******************************************************************************
* graph_add_i - add an edge or vertex into the graph
*
* This routine adds an edge and it's two vertices or a stand-alone vertext to
* the graph. If <is_edge> is TRUE, then this API inserts an edge defined by
* the two vertices <v1> and <v2>.  If <g> is a directed graph then <v1> is
* considered to be the source vertex and <v2> the destination vertex. If
* <is_edge> is FALSE, then this API inserts a stand-alone vertext defined by
* <v1>.
*
* RETURNS: GPH_ERR_E
*/

GPH_ERR_E graph_add_i
(
GRAPH_T* g,             /* graph to add the edge or vertices */
void* info,             /* edge label */
unsigned long v1,       /* integer vertex identifier. */
void* v1_info,          /* vertex aux. information */
unsigned long v2,       /* integer vertext identifier. Not used if <is_edge> is FALSE */
void* v2_info,          /* vertex aux. information. Not used if <is_edge> is FALSE */
unsigned int weight,     /* edge weight. Not used if <is_edge> is FALSE */
BOOL_E is_edge          /* are we inserting an edge or a stand-alone vertex */
)
{
   EDGE_T* e;
   void *v1o, *v2o;

   v1o = graph_v_create_i (g, v1, info);
   v2o = graph_v_create_i (g, v2, info);
   if (DS_YES == graph_edge_exists (g, v1o, v2o))
   {
      return GPH_ERR_EDGE_EXISTS;
   }
   
   if (NULL == (e = malloc (sizeof (EDGE_T))))
      return GPH_ERR_MALLOC_FAIL;   
   //fprintf (stderr, "v1=%lu v2=%lu\n", ((VTX_UD_T*)v1o)->id.iid, ((VTX_UD_T*)v2o)->id.iid);
   e->next = NULL;
   e->v1 = v1o;
   e->v2 = v2o;
   e->weight = weight;
   e->aux = info;
   edge_insert (g, e);
   
   /* update the edge lists for the vertices */
   if (GPH_ERR_ERR == graph_add_edge_to_vertices (g, e, v1o, v2o))
   {
      return GPH_ERR_EDGE_ADD_FAIL;
   }
   return GPH_ERR_OK;   
}

/*******************************************************************************
* graph_add_c - add an edge or vertex into the graph
*
* This routine adds an edge and it's two vertices or a stand-alone vertext to
* the graph. If <is_edge> is TRUE, then this API inserts an edge defined by
* the two vertices <v1> and <v2>.  If <g> is a directed graph then <v1> is
* considered to be the source vertex and <v2> the destination vertex. If
* <is_edge> is FALSE, then this API inserts a stand-alone vertext defined by
* <v1>.
*
* RETURNS: GPH_ERR_E
*/

GPH_ERR_E graph_add_c
(
GRAPH_T* g,             /* graph to add the edge or vertices */
void* info,             /* edge label */
char* v1,               /* text vertex identifier. */
void* v1_info,          /* vertex aux. information */
char* v2,               /* text vertex identifier. Not used if <is_edge> is FALSE */
void* v2_info,          /* vertex aux. information. Not used if <is_edge> is FALSE */
unsigned int weight,    /* edge weight. Not used if <is_edge> is FALSE */
BOOL_E is_edge          /* are we inserting an edge or a stand-alone vertex */
)
{
   EDGE_T* e;
   void *v1o, *v2o;

   if (NULL == (e = malloc (sizeof (EDGE_T))))
      return GPH_ERR_MALLOC_FAIL;

   v1o = graph_v_create_c (g, v1, info);
   v2o = graph_v_create_c (g, v2, info);

   e->next = NULL;   
   e->v1 = v1o;
   e->v2 = v2o;
   e->weight = weight;
   e->aux = info;
   edge_insert (g, e);
   
   /* update the edge lists for the vertices */
   if (GPH_ERR_ERR == graph_add_edge_to_vertices (g, e, v1o, v2o))
   {
      return GPH_ERR_EDGE_ADD_FAIL;
   }
   return GPH_ERR_OK;   
}

/**
 * This routine deletes a graph
 *
 * @param[in] g The graph to delete
 * @return GPH_ERR_OK if successfull, GPH_ERR_OK otherwise
 */
GPH_ERR_E graph_delete
(
GRAPH_T* g
)
{
   EDGE_T* ep = g->eLst;
   EDGE_T* en = NULL;

#define NEXT_AND_FREE(PREV, NEXT)                                       \
   do                                                                   \
   {                                                                    \
      while (PREV)                                                      \
      {                                                                 \
         NEXT = PREV->next;                                             \
         free (PREV);                                                   \
         PREV = NEXT;                                                   \
      }                                                                 \
   }while(0)
   
   /* free the edge list */
   NEXT_AND_FREE (ep, en);
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vp = g->vLst;
      VTX_UD_T* vn = NULL;
      
/* free the vertex list */
      NEXT_AND_FREE (vp, vn);
   }
   else if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vp = g->vLst;
      VTX_D_T* vn = NULL;
/* free the out edge list */
      NEXT_AND_FREE (vp, vn);
   }
   
   return GPH_ERR_OK;   
}

/**
 * This routine creates a new graph
 *
 * @param[in] type The type of graph to create - directed or undirected
 * @param[in] label_id_type The type of vertex identifiers the graph will use
 * - integer or string identifiers
 * @return A valid GRAPH_T* if successfull or NULL if unsuccessful
 */
GRAPH_T* graph_new
(
GRAPH_TYPE_E type,              /* directed or undirected graph */
GRAPH_LABEL_E label_id_type     /* integer or string vertex identifiers */
)
{
   GRAPH_T* gph = NULL;
   
   if (NULL == (gph = malloc (sizeof (GRAPH_T))))
      goto graph_new_err;
   gph->eLst = NULL;
   gph->vLst = NULL;
   gph->v_no = 0;
   gph->e_no = 0;
   gph->type = type;
   gph->label_type = label_id_type;
   return gph;
   
graph_new_err:
   if (gph)
      free (gph);
   
   return NULL;
}


/* graph.c - directed and undirected graph lib */

/*
modification history
--------------------
05aug10,gnm written
*/

/*
DESCRIPTION

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ds_types.h>
#include <graph.h>


/*******************************************************************************
* vertex_insert - insert a vertext in the graph
*
* RETURNS: 
*/

static void edge_print (GRAPH_T* g)
{
   EDGE_T* node = g->eLst;
   while (node)
   {
      fprintf (stdout, "edge (%s) v1=%lu v2=%lu\n",
               (char*)node->aux, 
               ((VTX_UD_T*)node->v1)->id.iid,
               ((VTX_UD_T*)node->v2)->id.iid);
      node = node->next;
   }
}

/*******************************************************************************
* vertex_insert - insert a vertext in the graph
*
* RETURNS: 
*/

static void vertex_print (GRAPH_T* g)
{
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vtx = g->vLst;
      while (vtx)
      {
         fprintf (stdout, "vertex %lu\n", vtx->id.iid);
      }
   }   
   else if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vtx = g->vLst;
      while (vtx)
      {
         fprintf (stdout, "vertex %lu\n", vtx->id.iid);
      }
   }
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
         lvtx = vtx;
      }
      if (g->type == GRAPH_DIRECTED_T)
      {
         VTX_D_T* lvtx = g->last_vertex;
         lvtx->next = vtx;
         lvtx = vtx;
      }
   }
   return GPH_ERR_OK;
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
* edge_insert - insert an edge in the graph
*
* RETURNS: 
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
* graph_vertex_find_next - 
*
* RETURNS: 
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
}

/*******************************************************************************
* graph_vertex_find_i - 
*
* RETURNS: 
*/

void* graph_vertex_find_i
    (
    GRAPH_T* g,
    unsigned long vid
    )
{
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vtx = g->vLst;
      
      while (NULL != vtx)
      {
         if (vtx->id.iid == vid)
            return vtx;
      }
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vtx = g->vLst;
      
      while (NULL != vtx)
      {
         if (vtx->id.iid == vid)
            return vtx;
      }
   }
   return NULL;
}

/*******************************************************************************
* graph_vertex_find_c - check if a string labelled vertex exists in the graph  
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
   
   ve = malloc (sizeof (VTX_EDGE));
   if (NULL == ve)
      return GPH_ERR_ERR;
   ve->edge = edge;
   ve->next = NULL;
   
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      VTX_UD_T* vtx = v1;
      
      if (NULL == vtx->ELst)
      {
         vtx->ELst = ve;
      }
      else
      {
         vtx->ELst->next = ve;
      }
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      VTX_D_T* vtx1 = v1;
      VTX_D_T* vtx2 = v2;
      
      if (NULL == vtx1->outELst)
      {
         vtx1->outELst = ve;
      }
      else
      {
         vtx1->outELst->next = ve;
      }

      if (NULL == vtx2->inELst)
      {
         vtx2->inELst = ve;
      }
      else
      {
         vtx2->inELst->next = ve;
      }
   }
   return GPH_ERR_OK;
}

/*******************************************************************************
* graph_v_insert - insert a new edge into the graph
*
* RETURNS: A valid vertex node if created or present, NULL on error 
*/

static void* graph_v_create_i
    (
    GRAPH_T* g,         /* graph to add vertex to */
    unsigned long vid,  /* vertext identifier */
    void* info          /* user-specific vertext information */
    )
{
   void* vtx;
   if (NULL != (vtx = graph_vertex_find_i (g, vid)))
       return vtx;

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
* 
* RETURNS: created vertext if successful, NULL otherwise
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

   if (NULL == (e = malloc (sizeof (EDGE_T))))
      return GPH_ERR_MALLOC_FAIL;

   v1o = graph_v_create_i (g, v1, info);
   v2o = graph_v_create_i (g, v2, info);

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
* graph_delete - delete a graph
*
* RETURNS: GRAPH_T* 
*/

GRAPH_T* graph_delete (GRAPH_T* g)
{
   
   
}

/*******************************************************************************
* graph_new - create a new graph
*
* RETURNS: GRAPH_T* 
*/

GRAPH_T* graph_new (GRAPH_TYPE_E type)
    {
    GRAPH_T* gph = NULL;
    
    if (NULL == (gph = malloc (sizeof (GRAPH_T))))
        goto graph_new_err;
    gph->eLst = NULL;
    gph->vLst = NULL;
    gph->v_no = 0;
    gph->e_no = 0;
    gph->type = type;
    return gph;

graph_new_err:
    if (gph && gph->eLst)
        free (gph->eLst);
    if (gph && gph->vLst)
        free (gph->vLst);
    if (gph)
        free (gph);

    return NULL;
    }

#define GRAPH_TEST

#ifdef GRAPH_TEST
/*******************************************************************************
* graph_main -
*
*       1---2  /3--/4 
*       |   | / | / |
*       |   |/  |/  |
*       5   6---7---8
*/

int graph_main (int argc, char** argv)
{
   GRAPH_T* g;

   fprintf (stderr, "graph test #1\n");
   g = graph_new (GRAPH_UNDIRECTED_T);   
   graph_add_i (g, "e1", 1, NULL, 2, NULL, 1, DS_TRUE);
   graph_add_i (g, "e2", 1, NULL, 5, NULL, 1, DS_TRUE);   
   graph_add_i (g, "e3", 2, NULL, 6, NULL, 1, DS_TRUE);
   graph_add_i (g, "e4", 6, NULL, 7, NULL, 1, DS_TRUE);   
   graph_add_i (g, "e5", 3, NULL, 7, NULL, 1, DS_TRUE);
   graph_add_i (g, "e6", 3, NULL, 4, NULL, 1, DS_TRUE);
   graph_add_i (g, "e7", 7, NULL, 8, NULL, 1, DS_TRUE);
   graph_add_i (g, "e8", 4, NULL, 8, NULL, 1, DS_TRUE);
   graph_add_i (g, "e9", 6, NULL, 3, NULL, 1, DS_TRUE);
   graph_add_i (g, "e10", 7, NULL, 4, NULL, 1, DS_TRUE);   
   edge_print (g);
   vertex_print (g);
}
#endif

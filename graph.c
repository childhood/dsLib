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

#include <sll.h>
#include <graph.h>


/*******************************************************************************
* vertex_insert - insert a vertext in the graph
*
* RETURNS: 
*/
static edge_print (GRAPH_T* g)
{
   SLL_T* eLst;
   SLL_NODE* node;
   
   node = g->eLst->lhead;
   while (node)
   {
      fprintf (stdout, "edge (%s) v1=%lu v2=%lu\n",
               (char*)((EDGE_T*)(node->FVPDATA))->aux,
               ((VTX_UD_T*)((EDGE_T*)node->FVPDATA)->v1)->id.iid,
               ((VTX_UD_T*)((EDGE_T*)node->FVPDATA)->v2)->id.iid);
      node = node->next;
   }
}

/*******************************************************************************
* vertex_insert - insert a vertext in the graph
*
* RETURNS: 
*/
static vertex_print (GRAPH_T* g)
{
   SLL_T* eLst;
   SLL_NODE* node;
   
   node = g->vLst->lhead;
   while (node)
   {
      fprintf (stdout, "vertex %lu\n",
               ((VTX_UD_T*)(node->FVPDATA))->id.iid);
      node = node->next;
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
    if (SLL_ERR_OK != sll_insert (g->vLst, vtx))
        return GPH_ERR_ERR;
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
       if (SLL_ERR_OK != sll_insert (g->eLst, edge))
          return GPH_ERR_ERR;
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
       if (SLL_ERR_OK != sll_delete (g->eLst, edge))
          return GPH_ERR_ERR;
       return GPH_ERR_OK;
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
   SLL_NODE* node = NULL;
   
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      while (NULL != (node = sll_next_get (g->vLst, node)))
      {
         if (((VTX_UD_T*)node->FVPDATA)->id.iid == vid)
            return node->FVPDATA;
      }
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      while (NULL != (node = sll_next_get (g->vLst, node)))
      {
         if (((VTX_D_T*)node->FVPDATA)->id.iid == vid)
            return node->FVPDATA;
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
   SLL_NODE* node = NULL;
   
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      while (NULL != (node = sll_next_get (g->vLst, node)))
      {
         if (strcmp (((VTX_UD_T*)node->FVPDATA)->id.cid, vid))
            return node->FVPDATA;
      }
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      while (NULL != (node = sll_next_get (g->vLst, node)))
      {
         if (strcmp (((VTX_D_T*)node->FVPDATA)->id.cid, vid))
            return node->FVPDATA;
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
   if (g->type == GRAPH_UNDIRECTED_T)
   {
      sll_insert (((VTX_UD_T*)v1)->ELst, edge);
   }
   
   if (g->type == GRAPH_DIRECTED_T)
   {
      sll_insert (((VTX_D_T*)v1)->outELst, edge);
      sll_insert (((VTX_D_T*)v2)->inELst, edge);
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
      if (NULL == (vtx->ELst = sll_new (VPDATA, NULL, NULL, NULL)))
      {
         free (vtx);
         return NULL;
      }
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
      if (NULL == (vtx->outELst = sll_new (VPDATA, NULL, NULL, NULL)))
      {
         free (vtx); return NULL;
      }
      if (NULL == (vtx->inELst = sll_new (VPDATA, NULL, NULL, NULL)))
      {
         free (vtx); free (vtx->outELst); return NULL;
      }
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
      if (NULL == (vtx->ELst = sll_new (VPDATA, NULL, NULL, NULL)))
      {
         free (vtx);
         return NULL;
      }
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
      if (NULL == (vtx->outELst = sll_new (VPDATA, NULL, NULL, NULL)))
      {
         free (vtx); return NULL;
      }
      if (NULL == (vtx->inELst = sll_new (VPDATA, NULL, NULL, NULL)))
      {
         free (vtx); free (vtx->outELst); return NULL;
      }
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
    if (NULL == (gph->eLst = sll_new (VPDATA, NULL, NULL, NULL)))
        goto graph_new_err;        
    if (NULL == (gph->vLst = sll_new (VPDATA, NULL, NULL, NULL)))
        goto graph_new_err;
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

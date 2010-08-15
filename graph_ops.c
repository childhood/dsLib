
#include <stdio.h>

#include <ds_types.h>
#include <graph.h>

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
        /**< creating the left edge */
        if (vid%M != 1)               
            graph_add_i (matrix, label, vid, NULL, vid-1, NULL, 1, DS_TRUE);
        /**< creating the right edge */
        if (vid%M != 0)
            graph_add_i (matrix, label, vid, NULL, vid+1, NULL, 1, DS_TRUE);
        /**< creating the up edge */
        if (vid > M)
            graph_add_i (matrix, label, vid, NULL, vid-M, NULL, 1, DS_TRUE);
        /**< creating the down edge */
        if (vid <= (M*(N-1)))
            graph_add_i (matrix, label, vid, NULL, vid+M, NULL, 1, DS_TRUE);        
        }
    return matrix;
    }

void bfs
    (
    GRAPH_T* g
    )
    {
    
    }


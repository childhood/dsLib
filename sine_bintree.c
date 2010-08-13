/* sine_bintree.c - binary tree implementation */

#undef TEST_BINTREE

#include <stdio.h> /* NULL */
#include <sys/types.h>
#include <stdlib.h> /* malloc */
#include <assert.h>
#include <stdarg.h> /* va_* */

#include <sine_types.h>
#include <sine_bintree.h>

typedef enum {GO_LEFT=1, GO_RIGHT=2, GO_NOWHERE=3} BTREE_DIR_E;

/*******************************************************************************
 * btree_node_compare - compare two node data 
 *
 * ARGS:
 * RETURNS:
 */
static inline BTREE_DIR_E btree_node_compare
    (
    BTREE_NODE_T* node,
    NODE_DATA_T data,
    NODE_DATA_TYPE_E type
    )
    {
    switch (type)
        {
        case IDATA:
            if (node->FIDATA > data.idata)
                return GO_LEFT;
            else if (node->FIDATA < data.idata)
                return GO_RIGHT;
            else return GO_NOWHERE;
            break;
        case UIDATA:
            if (node->FUIDATA > data.uidata)
                return GO_LEFT;
            else if (node->FUIDATA < data.uidata)
                return GO_RIGHT;
            return GO_NOWHERE;
            break;
        case CDATA:
            if (node->FCDATA > data.cdata)
                return GO_LEFT;
            else if (node->FCDATA < data.cdata)
                return GO_RIGHT;
            else return GO_NOWHERE;
            break;
        case UCDATA:
            if (node->FUCDATA > data.ucdata)
                return GO_LEFT;
            else if (node->FUCDATA < data.ucdata)
                return GO_RIGHT;
            else return GO_NOWHERE;
            break;
        case VPDATA:
            if (node->FVPDATA > data.vpdata)
                return GO_LEFT;
            else if (node->FVPDATA < data.vpdata)
                return GO_RIGHT;
            else return GO_NOWHERE;
            break;
        case FPDATA:
            if (node->FFPDATA > data.fpdata)
                return GO_LEFT;
            else if (node->FFPDATA < data.fpdata)
                return GO_RIGHT;
            else return GO_NOWHERE;
            break;
        }
    return GO_NOWHERE;
    }

/*******************************************************************************
 * btree_clear_mark - reset visted marks
 *
 * ARGS:
 * RETURNS:
 */
static inline void btree_clear_mark
    (
    BTREE_CTX* ctx
    )
    {
    BTREE_NODE_T* node = ctx->tree;
    
    while (node != NULL)
        {
        printf ("a\n");
        node->visited = false;
        node = node->next;
        }
    }

/*******************************************************************************
 * btree_find - find a node in a  binary tree
 *
 * ARGS:
 * RETURNS:
 */

int btree_find
    (
    BTREE_CTX* ctx,
    NODE_DATA_T data,
    NODE_DATA_TYPE_E type
    )
    {
    
    return 0;
    }


/*******************************************************************************
 * btree_inorder - inorder traversal of binary tree
 *
 * ARGS:
 * RETURNS:
 */

int btree_inorder
    (
    BTREE_CTX* ctx,
    btree_inorder_func func,
    void* arg
    )
    {
    BTREE_NODE_T* node = ctx->tree;
    int ret = 0;
    
    if (node == NULL)
        return ret;
    
    btree_clear_mark (ctx);
#define LEFT_DONE(node) \
    ((node->lchild == NULL)?1:((node->lchild->visited==true)?1:0))
#define RIGHT_DONE(node) \
    ((node->rchild == NULL)?1:((node->rchild->visited==true)?1:0))
#define NODE_DONE(node) \
    (node->visited==true)

    while (1)
        {
        if (!LEFT_DONE(node))
            { /* go down the left subtree */
            node = node->lchild;
            continue;
            }

        if (node->visited == false)
            {
            ret = func (ctx, node, arg);
            if (ret) return ret;
            node->visited = true;
            }
        
        if (!RIGHT_DONE(node))
            { /* go down the right subtree */
            node = node->rchild;
            continue;
            }

        if (LEFT_DONE(node) && RIGHT_DONE(node) && NODE_DONE(node) &&
            node->parent)
            {
            node = node->parent;
            }
        
        if (LEFT_DONE(node) && RIGHT_DONE(node) && NODE_DONE(node) &&
            !node->parent)
            {/* at the tree root and all done*/
            break;
            }
        }
    return 0;
    }

/*******************************************************************************
 * btree_delete - delete a node from the binary tree
 *
 * ARGS:
 * RETURNS: 0 - node found and deleted
 *      -1 - not not found
 */

int btree_delete
    (
    BTREE_CTX* ctx,
    NODE_DATA_T data,
    NODE_DATA_TYPE_E type
    )
    {
    return 0;
    }

/*******************************************************************************
 * btree_insert - insert a node(s) into the binary tree
 *
 * ARGS: ctx - binary tree context
 *      argc - number of data and type pairs
 *      type1 - type of data1 (NODE_DATA_TYPE_E)
 *      data1 - data to insert
 *      type2 - type of data2
 *      data2 - data to insert 
 *      ...
 * RETURNS:
 */

static inline int btree_add
    (
    va_list ap,
    NODE_DATA_TYPE_E type,
    BTREE_NODE_T* node
    )
    {
    switch (type)
        {
        case IDATA:
            node->FIDATA = va_arg (ap, int);
            break;
        case UIDATA:
            node->FUIDATA = va_arg (ap, unsigned int);
            break;
        case CDATA:
            node->FCDATA = (char)va_arg (ap, int);
            break;
        case UCDATA:
            node->FUCDATA = (unsigned char)va_arg (ap, unsigned int);
            break;
        case VPDATA:
            node->FVPDATA = va_arg (ap, void*);
            break;
        case FPDATA:
            node->FFPDATA = va_arg (ap, FUNCPTR2_T);
            break;                
        }
    return 0;
    }

/*******************************************************************************
 * btree_insert - insert a node(s) into the binary tree
 *
 * ARGS: ctx - binary tree context
 *      argc - number of data and type pairs
 *      type1 - type of data1 (NODE_DATA_TYPE_E)
 *      data1 - data to insert
 *      type2 - type of data2
 *      data2 - data to insert 
 *      ...
 * RETURNS:
 */

int btree_insert
    (
    BTREE_CTX* ctx,
    int argc,
    ...
    )
    {
    BTREE_NODE_T* peg_cur;
    BTREE_NODE_T* peg_prev;
    BTREE_DIR_E dir;
    NODE_DATA_TYPE_E type;
    va_list data_and_type;
    
    int idx;
    
    va_start (data_and_type, argc);
    for (idx = 0; idx < argc; idx++)
        {
        BTREE_NODE_T* node = malloc (sizeof(BTREE_NODE_T));
        assert (node != NULL);

        type = va_arg (data_and_type, NODE_DATA_TYPE_E);
        btree_add (data_and_type, type, node);
        node->type = type;
        node->rchild = NULL;
        node->lchild = NULL;
        node->next = NULL;
        node->visited = false;
        node->parent = NULL;
        ctx->num_nodes++;
        if (ctx->tree == NULL)
            {
            ctx->tree = node;
            ctx->last = node;
            fprintf (stderr, "adding node=%p [data=%ld] parent=NONE\n", node,
                     node->data.idata);
            return 0;
            }
        ctx->last->next = node;
        ctx->last = node;
        peg_cur = ctx->tree;
        while (peg_cur != NULL)
            {
            peg_prev = peg_cur;
            dir = btree_node_compare (peg_cur, node->data, type);
            if (dir == GO_LEFT)
                peg_cur = peg_cur->lchild;
            else if (dir == GO_RIGHT)
                peg_cur = peg_cur->rchild;
            else if (dir == GO_NOWHERE)
                peg_cur = peg_cur->rchild;
            }
        
        if (dir == GO_LEFT)
            peg_prev->lchild = node;
        else if (dir == GO_RIGHT)
            peg_prev->rchild = node;
        else if (dir == GO_NOWHERE)
            peg_prev->rchild = node;
        node->parent = peg_prev;
        fprintf (stderr, "adding node=%p [data=%ld] parent=%p  left=%p right=%p\n",
                 node,
                 node->data.idata, peg_prev, peg_prev->lchild, peg_prev->rchild);
        return 0;
        }
    va_end (data_and_type);
    return 0;
    }

/*******************************************************************************
 * btree_new - create a new tree
 *
 * ARGS:
 * RETURNS:
 */

BTREE_CTX* btree_new
    (
    int arg1, int arg2
    )
    {
    BTREE_CTX* b = malloc (sizeof (BTREE_CTX));
    assert (b != NULL);
    b->tree = NULL;
    b->num_nodes = 0;
    b->last = NULL;
    return b;
    }

#ifdef TEST_BINTREE
int traverse(BTREE_CTX* ctx, BTREE_NODE_T* node, void* arg)
    {
    switch (node->type)
        {
        case IDATA:
        case UIDATA:
        case CDATA:
        case UCDATA:
            fprintf (stdout, "%ld\n", node->data.idata);
            break;
        case FPDATA:
        case VPDATA:
            ;
        }
    return 0;
    }

int main (int argc, char** argv)
    {
    BTREE_CTX* ctx = btree_new(0, 0);
    FILE* fp;
    int iter = 10;
    unsigned int val;

    fp = fopen ("/dev/random", "r");
    if (NULL == fp)
        fprintf (stderr, "error");
    fread (&val, sizeof (val), 1, fp);
    fclose (fp);    
    printf ("+%u_", val);
    srand (val);
    while (iter)
        {
        val = rand ();
            printf ("%d-", val);
        btree_insert (ctx, 1, IDATA, val);
        iter--;
        }
        btree_inorder (ctx, traverse, NULL);
    return 0;
    }
#endif    


#ifndef __SINE_BINTREE_H
#define __SINE_BINTREE_H

typedef struct _btree_node
    {
#define FIDATA   data.idata
#define FUIDATA  data.uidata
#define FCDATA   data.cdata    
#define FUCDATA  data.ucdata    
#define FVPDATA  data.vpdata
#define FFPDATA  data.fpdata 
    NODE_DATA_T data;
    NODE_DATA_TYPE_E type;
    struct _btree_node* rchild;
    struct _btree_node* lchild;
    struct _btree_node* parent;
    struct _btree_node* next;
#if __STDC_VERSION__ >= 199901L
    _Bool visited;
#else
    int visited;
#endif    
    } BTREE_NODE_T;

typedef struct
    {
    BTREE_NODE_T* tree;
    BTREE_NODE_T* last;
    int num_nodes;
    } BTREE_T;

/* RETURN: should return 0 on success */
typedef int (*btree_inorder_func)(BTREE_T*, BTREE_NODE_T*, void*);
/* RETURN: should return 0 on success */
typedef int (*btree_postorder_func)(BTREE_T*, BTREE_NODE_T*, void*);
/* RETURN: should return 0 on success */
typedef int (*btree_preoorder_func)(BTREE_T*, BTREE_NODE_T*, void*);

#endif /* !defined __SINE_BINTREE_H */    

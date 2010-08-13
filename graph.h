/* sll.h - header information for single linked list operations */

/*
* Modification History
* 06aug10,gnm written 
* 
*/

typedef enum {
   GRAPH_DIRECTED_T=0,
   GRAPH_UNDIRECTED_T=1
}GRAPH_TYPE_E;

/* vertex identifier */
typedef union
    {        
    char* cid;          /* vertex identified by a textual label, or */
    unsigned long iid;  /* vertex identified by an integer label */
    }VTXID_U;

/* edge identifier */
typedef union
    {             
    char* cid;          /* edge identified by a textual label, or */
    unsigned long iid;  /* edge identified by an integer label*/
    }EDGID_U;

/* edge node */
typedef struct _dsedge
    {
    void* v1;            /* edge vertex #1 */
    void* v2;            /* edge vertext #2 */
    unsigned long weight;/* edge weight */
    void* aux;           /* auxilliary data to attach to the vertex */
    EDGID_U id;              /* edge identifier */
    }EDGE_T;

/* vertex node for a directed graph */
typedef struct _dsvtxd
    {
    void* outELst;      /* list of outward directed edges incident on the vertex */
    void* inELst;       /* list of inward directed edges incident on the vertex */
    unsigned long no;   /* total number of edges incident on the vertex */
    void* aux;          /* auxilliary data to attach to the vertex */
    VTXID_U id;         /* vertex identifier */
}VTX_D_T;

/* vertex node for an un-directed graph */
typedef struct _dsvtxud
    {
    void* ELst;         /* list of edges incident on the vertex */
    unsigned long no;   /* total number of edges incident on the vertex */
    void* aux;          /* auxilliary data to attach to the vertex */
    VTXID_U id;         /* vertex identifier */
    }VTX_UD_T;

/* A graph */
typedef struct _dsgraph
    {
    SLL_T* eLst;         /* list of edges in the graph */
    SLL_T* vLst;         /* list of vertices in the graph */
    unsigned long v_no;  /* total number of vertices in the graph */
    unsigned long e_no;  /* total number of edges in the graph */
    VTXID_U last_vid;
    EDGID_U last_eid;
    GRAPH_TYPE_E type;
    }GRAPH_T;

/* graph operation result code  */
typedef enum {
   GPH_ERR_ERROR_HIGH = -512,   /* fencepost */
   GPH_ERR_MALLOC_FAIL,
   GPH_ERR_EDGE_ADD_FAIL,
   GPH_ERR_ERR = -1,            /* generic operational error */
   GPH_ERR_OK = 0,              /* routine returned without any errors */
   GPH_ERR_VERTEX_EXISTS = 1   
} GPH_ERR_E;




typedef int(*BFS_FUNCPTR_T)(void*);
typedef int(*DFS_FUNCPTR_T)(void*);

typedef enum {DS_BFS_GRAY=0, DS_BFS_WHITE, DS_BFS_BLACK} DS_BFS_COLOR_E;
typedef enum {DS_DFS_GRAY=0, DS_DFS_WHITE, DS_DFS_BLACK} DS_DFS_COLOR_E;

typedef struct ds_bfs_AUX {
   DS_BFS_COLOR_E color;
   long distance;
} DS_BFS_AUX_T;

typedef struct ds_dfs_AUX {
   DS_DFS_COLOR_E color;
   struct timespec d_time;
   struct timespec f_time;
} DS_DFS_AUX_T;

GRAPH_T* matrix_create (const unsigned long row, const unsigned long column);

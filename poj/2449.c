#include <stdlib.h>
#include <stdio.h>

#define N (1000)
#define M (N * N)
#define L (10)
#define PATH_MAX_NUM ((N)*(N))
#define INF 100000000

int graph[N][N];
int v_graph[N][N];//反向图
int H[N][N];
int m, n;
int S, T, K;
int kk[N];

typedef struct path_s {
    struct path_s *prev;//子路径, prev = path - sink
    int sink;
    int len;//路径的节点数
    int g;//A*算法中的实际代价，也是该条路径的总代价
    int f;//从路径最后一个节点到目标节点T的估计代价
}path_t;

typedef struct priority_queue_s {
    path_t *path[PATH_MAX_NUM];
    int size;
}priority_queue_t;

typedef struct edge_s {
    struct edge_s *prev;
    int v;
    int w;
}edge_t;

path_t *unused_path = NULL;
path_t path_pool[PATH_MAX_NUM];

priority_queue_t q;
priority_queue_t *pq = &q;

edge_t edge_pool[M];
int edge_num;
edge_t *edges[N];

void add_edge(int u, int v, int w) {
    edge_pool[edge_num].prev = edges[u];
    edge_pool[edge_num].v = v;
    edge_pool[edge_num].w = w;
    edges[u] = edge_pool + edge_num;
    edge_num++;
}
void init_path_pool()
{
    int i;
    path_pool[0].prev = NULL;
    path_pool[0].len = 1;
    for(i = 1; i < PATH_MAX_NUM; i++) {
        path_pool[i].prev = path_pool + (i-1);
        path_pool[i].len = path_pool[i-1].len + 1;
    }
    unused_path = path_pool + (PATH_MAX_NUM - 1);
}
void free_path(path_t *path)
{
     path->prev = unused_path;
     unused_path = path;
}

path_t* get_path()
{
    if(unused_path == NULL) {
        printf("get_path unused_path == NULL, pq->size=%d\n", pq->size);
        exit(-1);
    }
    path_t *path_tmp = unused_path;
    unused_path = unused_path->prev;
    return path_tmp;
}

void init_pq()
{
    pq = &q;
    pq->size = 0;
}
#define is_pq_empty() (pq->size <= 0)

void push_pq(path_t *path)
{
     int t = pq->size;
     path_t *path_tmp;
     pq->path[pq->size] = path;
     pq->size = pq->size + 1;
     if(pq->size > PATH_MAX_NUM) {
        printf("push_pq: pq->size = %d > PATH_MAX_NUM(%d)\n", pq->size, PATH_MAX_NUM);
        exit(-1);
     }
     while(t != 0) {
         if(pq->path[t]->f >= pq->path[(t-1)/2]->f) return;
         path_tmp = pq->path[t];
         pq->path[t] = pq->path[(t-1)/2];
         pq->path[(t-1)/2] = path_tmp;
         t = (t-1)/2;
     }

}

path_t* pop_pq()
{
    path_t *path_tmp;
    int t = 0;
    if(pq->size == 0) {
        printf("pop_pq: pq->size == 0\n");
        exit(-1);
    }
    pq->size = pq->size - 1;
    path_tmp = pq->path[0];
    pq->path[0] = pq->path[pq->size];
    pq->path[pq->size] = path_tmp;
    while(2*t + 1 < pq->size) {
        t = 2*t + 1;
        if(t+1 < pq->size && pq->path[t]->f > pq->path[t+1]->f) t++;
        if(pq->path[(t-1)/2]->f <= pq->path[t]->f) break;
        path_tmp = pq->path[(t-1)/2];
        pq->path[(t-1)/2] = pq->path[t];
        pq->path[t] = path_tmp;
    }
    return pq->path[pq->size];
}

path_t* top_pq()
{
    if(pq->size == 0) {
        printf("top_pq: pq->size == 0\n");
        exit(-1);
    }
    return pq->path[0];
}

void read_input()
{
     int u, v, w;
     int i,j;
     scanf("%d %d", &n, &m);
     for(i = 0; i < n; i++) {
         for(j = 0; j < n; j++) {
             graph[i][j] = v_graph[i][j] = INF;
         }
         graph[i][i] = v_graph[i][i] = 0;
     }
     //init edge
     edge_num = 0;
     for(i = 0; i < n; i++) {
         edges[i] = NULL;
     }
     for(i = 0; i < m; i++) {
         scanf("%d %d %d", &u, &v, &w);
         //u--; v--; //change index starting with 1 into with 0
         graph[u][v] = v_graph[v][u] = w;
         add_edge(u, v, w);
     }
     for(i = 0; i < n; i++) {
         edge_t *edge = edges[i];
         while(edge) {
             //printf("edge->u=%d, edge->v=%d, edge->w=%d\n", i, edge->v, edge->w);
             edge = edge->prev;
         }
     }
     //exit(0);
     scanf("%d %d %d", &S, &T, &K);
     //S--; T--; //change index starting with 1 into with 0
}
void calculate_H()
{
    int i, j, k;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            H[i][j] = v_graph[i][j];
        }
    }
    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(H[i][k] + H[k][j] < H[i][j])
                    H[i][j] = H[i][k] + H[k][j];
            }
        }
    }
}

void init_kk()
{
    int i;
    for(i = 0; i < n; i++) kk[i] = 0;
}

void print_path(path_t *path)
{
    while(path) {
        printf("%d<-", path->sink);
        path = path->prev;
    }
    printf("\n");
}

int ksp_by_A_star(int s, int t, int k)
{
     //printf("s=%d, t=%d, k=%d\n", s, t, k);
     path_t *path, *pt;
     edge_t *edge;
     calculate_H();
     init_kk();
     init_path_pool();
     path = get_path();
     init_pq();
     if(H[t][s] >= INF) return -1;
     path->sink = s;
     path->prev = NULL;
     path->len = 1;
     path->g = 0;
     path->f = path->g + H[t][s];
     push_pq(path);
     //printf("pq->size=%d\n", pq->size);
     while(!is_pq_empty()) {
         path = pop_pq();
         //printf("path->sink=%d, path->len=%d, path->f=%d, path->g=%d\n", path->sink,  path->len, path->f, path->g);
         kk[path->sink]++;
         if(kk[path->sink] > k) continue;
         if(path->sink == t && kk[path->sink] == k) {
             //print_path(path);
             return path->f;
         }
         if(path->len > 4) continue;
         edge = edges[path->sink];
         while(edge) {
             if(H[t][edge->v] >= INF) {
                 edge = edge->prev;
                 continue;
             }
             //printf("     edge->v=%d, edge->w=%d\n", edge->v, edge->w);
             pt = get_path();
             pt->sink = edge->v;
             pt->len = path->len + 1;
             pt->prev = path;
             pt->g = path->g + edge->w;
             pt->f = pt->g + H[t][edge->v];
             push_pq(pt);
             //printf("     pq->path[0].sink=%d\n", pq->path[0]->sink);
             edge = edge->prev;
         }
         //exit(0);
         //free_path(path);
     }
     return -1;
}
int main() {
    read_input();
    int i, j;
    for(i = 1; i < n; i++) {
        //int res = ksp_by_A_star(S, T, K + (S==T));
        int res = ksp_by_A_star(0, i, K + (0==i));
        printf("%d\n", res);
    }
    return 0;
}

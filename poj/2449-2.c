#include <stdlib.h>
#include <stdio.h>

#define N (1100)
#define M (N * N)
#define L (10)
#define PATH_MAX_NUM (2*(N)*(N))
#define INF 99999999

//int graph[N][N];
int v_graph[N][N];//反向图
int H[N];
int (*h);
int m, n;
int S, T, K;
int kk[N];

typedef struct path_s {
    struct path_s *prev;//子路径, prev = path - sink
    int sink;
    //int len;//路径的节点数
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

path_t path_pool[PATH_MAX_NUM];
int path_num;
path_t *unused_path;

priority_queue_t q;
priority_queue_t *pq = &q;

edge_t edge_pool[M];
int edge_num;

edge_t *edges[N];

void init_edge_pool()
{
    edge_num = 0;
}

void add_edge(int u, int v, int w) {
    edge_pool[edge_num].prev = edges[u];
    edge_pool[edge_num].v = v;
    edge_pool[edge_num].w = w;
    edges[u] = edge_pool + edge_num;
    edge_num++;
}
void init_path_pool()
{
    path_num = 0;
    unused_path = NULL;
}

void free_path(path_t *path)
{
    path->prev = unused_path;
    unused_path = path;
}

path_t* get_path()
{
    if(path_num + 1 >= PATH_MAX_NUM) {
        //printf("get_path unused_path == NULL, pq->size=%d\n", pq->size);
        //exit(-1);
        if(unused_path) {
            path_t *tmp = unused_path;
            unused_path = tmp->prev;
            return tmp;
        }
        //for(;;);
    }
    path_num++;
    //path_num /= PATH_MAX_NUM;
    return path_pool + (path_num - 1);
}

void init_pq()
{
    pq = &q;
    pq->size = 0;
}
#define is_pq_empty() (0 >= pq->size)

//void push_pq(path_t *path)
//{
//    if(PATH_MAX_NUM < pq->size) {
//        //printf("push_pq: pq->size = %d > PATH_MAX_NUM(%d)\n", pq->size, PATH_MAX_NUM);
//        //exit(-1);
//        for(;;);
//     }
//     int t = pq->size;
//     int p = (t-1)/2;
//     pq->path[t] = path;
//     
//     while(0 != t) {
//         if(pq->path[t]->f >= pq->path[p]->f) break;
//         pq->path[t] = pq->path[p];
//         t = p;
//         p = (t-1)/2;
//     }
//     pq->path[t] = path;
//     pq->size = pq->size + 1;
//
//}

path_t* pop_pq()
{
    path_t *path_tmp;
    int t = 0;
    if(pq->size == 0) {
        //printf("pop_pq: pq->size == 0\n");
        //exit(-1);
        //for(;;);
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

void push_pq(path_t *path)
{
    if(PATH_MAX_NUM < pq->size) {
        //printf("push_pq: pq->size = %d > PATH_MAX_NUM(%d)\n", pq->size, PATH_MAX_NUM);
        //exit(-1);
        for(;;);
     }
     int t = pq->size;
     //path_t *path_tmp;
     pq->path[t] = path;
     pq->size = pq->size + 1;
     
     while(t != 0) {
         if(pq->path[t]->f >= pq->path[(t-1)/2]->f) break;
         //path_tmp = pq->path[t];
         pq->path[t] = pq->path[(t-1)/2];
         //pq->path[(t-1)/2] = path_tmp;
         t = (t-1)/2;
     }
     pq->path[t] = path;

}

void push_pq(path_t *path)
{
    if(pq->size > PATH_MAX_NUM) {
        //printf("push_pq: pq->size = %d > PATH_MAX_NUM(%d)\n", pq->size, PATH_MAX_NUM);
        //exit(-1);
        for(;;);
     }
     int t = pq->size;
     path_t *path_tmp;
     pq->path[pq->size] = path;
     pq->size = pq->size + 1;
     
     while(t != 0) {
         if(pq->path[t]->f >= pq->path[(t-1)/2]->f) break;
         path_tmp = pq->path[t];
         pq->path[t] = pq->path[(t-1)/2];
         pq->path[(t-1)/2] = path_tmp;
         t = (t-1)/2;
     }

}

//path_t* pop_pq()
//{
//    path_t *path_tmp;
//    int t = 0;
//    if(pq->size == 0) {
//        //printf("pop_pq: pq->size == 0\n");
//        //exit(-1);
//        for(;;);
//    }
//    pq->size = pq->size - 1;
//    path_tmp = pq->path[0];
//    pq->path[0] = pq->path[pq->size];
//    pq->path[pq->size] = path_tmp;
//    while(2*t + 1 < pq->size) {
//        t = 2*t + 1;
//        if(t+1 < pq->size && pq->path[t]->f > pq->path[t+1]->f) t++;
//        if(pq->path[(t-1)/2]->f <= pq->path[t]->f) break;
//        path_tmp = pq->path[(t-1)/2];
//        pq->path[(t-1)/2] = pq->path[t];
//        pq->path[t] = path_tmp;
//    }
//    return pq->path[pq->size];
//}

//path_t* top_pq()
//{
//    if(pq->size == 0) {
//        //printf("top_pq: pq->size == 0\n");
//        //exit(-1);
//    }
//    return pq->path[0];
//}

void read_input()
{
     int u, v, w;
     int i,j;
     scanf("%d%d", &n, &m);
     
     for(i = 0; i < n; i++) {
         for(j = 0; j < n; j++) {
             //graph[i][j] = v_graph[i][j] = INF;
             v_graph[i][j] = INF;
         }
         //graph[i][i] = v_graph[i][i] = 0;
         v_graph[i][i] = 0;
     }
     
     //init edge_pool
	 init_edge_pool();
	 
	 //init edges
     for(i = 0; i < n; i++) {
         edges[i] = NULL;
     }
     for(i = 0; i < m; i++) {
         scanf("%d%d%d", &u, &v, &w);
         u--; v--; //change index starting with 1 into with 0
         //graph[u][v] = v_graph[v][u] = w;
         v_graph[v][u] = w;
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
     scanf("%d%d%d", &S, &T, &K);
     S--; T--; //change index starting with 1 into with 0
}
//void calculate_H()
//{
//    int i, j, k;
//    for(i = 0; i < n; i++) {
//        for(j = 0; j < n; j++) {
//            H[i][j] = v_graph[i][j];
//        }
//    }
//    for(k = 0; k < n; k++) {
//        for(i = 0; i < n; i++) {
//            for(j = 0; j < n; j++) {
//                if(H[i][k] + H[k][j] < H[i][j])
//                    H[i][j] = H[i][k] + H[k][j];
//            }
//        }
//    }
//}
void print_H(int s)
{
    int *h = H;
    int i;
    for(i = 0; i < n; i++) {
        printf("%d->%d:%d; ", i+1, s+1, h[i]);
    }
}
void dijkstra(int s)
{
    int *h = H;
    int i,j;
    for(i = 0; i < n; i++) {
        h[i] = v_graph[s][i];
    }
    int visit[N] = {0};
    visit[s] = 1;
    for(;;) {
        int min = INF;
        int k = -1;
        for(i = 0; i < n; i++) {
            if(!visit[i] && h[i] < min) {
                min = h[i];
                k = i;
            }
        }
        if(-1 == k) break;
        for(i = 0; i < n; i++) {
            if(!visit[i] && v_graph[k][i] >= INF) continue;
            if(h[k] + v_graph[k][i] < h[i]) {
                h[i] = h[k] + v_graph[k][i];
            }
        }
        visit[k] = 1;
    }
    
}

void init_kk()
{
    int i;
    for(i = 0; i < n; i++) kk[i] = 0;
}

void print_path(path_t *path)
{
    int f = path->f;
    while(path) {
        printf("%d", path->sink);
        if(path->prev) printf("<-");
        else printf("::%d\n", f);
        path = path->prev;
    }
}

int ksp_by_A_star(int s, int t, int k)
{
     //printf("s=%d, t=%d, k=%d\n", s, t, k);
     path_t *path, *pt;
     edge_t *edge;
     init_kk();
     init_path_pool();
     path = get_path();
     init_pq();
     dijkstra(t);
     //print_H(t);
     h = H;
     if(h[s] >= INF) {
         //printf("-1 H[t][s] >= INF\n");
         //printf("s=%d, t=%d, k=%d, rtt=%d\n", s+1, t+1, kk[path->sink], -1);
         return -1;
     }
     path->sink = s;
     path->prev = NULL;
     //path->len = 1;
     path->g = 0;
     path->f = path->g + h[s];
     push_pq(path);
     //printf("pq->size=%d\n", pq->size);
     while(!is_pq_empty()) {
         path = pop_pq();
         //printf("path->sink=%d, path->len=%d, path->f=%d, path->g=%d\n", path->sink,  path->len, path->f, path->g);
         kk[path->sink]++;
         if(kk[path->sink] > k) continue;
         if(path->sink == t) {
             //print_path(path);
             //printf("s=%d, t=%d, k=%d, rtt=%d\n", s+1, t+1, kk[path->sink], path->f);
         }
         if(path->sink == t && kk[path->sink] == k) {
             return path->f;
         }
         //if(path->len >= 3) continue;
         edge = edges[path->sink];
         while(edge) {
             if(h[edge->v] >= INF) {
                 edge = edge->prev;
                 continue;
             }
             //printf("     edge->v=%d, edge->w=%d\n", edge->v, edge->w);
             pt = get_path();
             pt->sink = edge->v;
             //pt->len = path->len + 1;
             pt->prev = path;
             pt->g = path->g + edge->w;
             pt->f = pt->g + h[edge->v];
             push_pq(pt);
             //printf("     pq->path[0].sink=%d\n", pq->path[0]->sink);
             edge = edge->prev;
         }
         //exit(0);
         free_path(path);
     }
     //printf("-1\n");
     //printf("s=%d, t=%d, k=%d, rtt=%d\n", s+1, t+1, kk[path->sink], -1);
     return -1;
}
int main() {

    int i, j, k;
    read_input();
    //calculate_H();
    
////////////////////////////////////////////////////////////
    if(S==T) K++;
    int res = ksp_by_A_star(S, T, K);
    printf("%d\n", res);
    return 0;
////////////////////////////////////////////////////////////
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
           K = 10;
           //int res = ksp_by_A_star(S, T, K + (S==T));
           int res = ksp_by_A_star(j, i, K + (j==i));
           //printf("%d\n", res);
        }
    }
    return 0;

    
    K = 5;
    for(i = 0; i < n; i++) {
        int res = ksp_by_A_star(114, i, K + (114==i));
        //printf("%d\n", res);
    }
    return 0;
}

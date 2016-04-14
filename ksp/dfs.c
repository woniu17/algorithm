#include<stdio.h>

#define N (1100)
#define M (N * N)
#define K (5)
#define MAX_PATH_STEP_NUM (10)
#define PATH_STEP_LIMIT (5)
#define MAX_PATH_NUM (N * N)
#define INF 99999999

typedef struct path_s {
    int nodes[MAX_PATH_STEP_NUM];
    int dist;//路径距离
    int step;//路径跳数
}path_t;

int graph[N][N];
path_t kspath[N][N][K];
int n, m, k = 5;

void read_input()
{
     int u, v, w;
     int i,j;
     scanf("%d %d", &n, &m);
     //printf("n=%d, m=%d, k=%d\n", n, m, k);
     for(i = 0; i < n; i++) {
         for(j = 0; j < n; j++) {
             graph[i][j] = INF;
         }
         graph[i][i] = 0;
     }
     for(i = 0; i < m; i++) {
         scanf("%d %d %d", &u, &v, &w);
         graph[u][v] = w;
     }
}

void init_kspath()
{
    int  i, j, p;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(p = 0; p < k; p++) {
                kspath[i][j][p].step = 0;
                kspath[i][j][p].dist = INF;
            }
        }
    }
}
inline void save_path(path_t *path)
{
    int u, v;
    int i;
    int j = -1, max = -1;
    u = path->nodes[0];
    v = path->nodes[path->step-1];
    for(i = 0; i < k; i++)
        if(kspath[u][v][i].dist > max) max = kspath[u][v][i].dist, j = i;
    if(max <= path->dist) return;
    if(path->step > 3) return;
    kspath[u][v][j].dist = path->dist;
    kspath[u][v][j].step = path->step;
    for(i = 0; i < path->step; i++) kspath[u][v][j].nodes[i] = path->nodes[i];

}

void print_result() {

    int  i, j, p, res;
    for(i = 114; i < 115; i++) {
        for(j = 0; j < n; j++) {
            for(p = 0; p < k; p++) {
                res = kspath[i][j][p].dist;
                if(INF == res) res = -1;
                printf("%d\n", res);
            }
        }
    }


}

void dfs()
{
    int  i, j, p, q, r;
    int visit[N] = {0};
    path_t path;
    read_input();
    init_kspath();
    for(i = 114; i < 115; i++) {
        visit[i] = 1;
        path.step = 1; path.dist = 0; path.nodes[0] = i;
        for(j = 0; j < n; j++) {
            if(visit[j]) continue;
            if(graph[i][j] >= INF) continue;
            visit[j] = 1;
            path.step++; path.dist += graph[i][j]; path.nodes[1] = j;
            save_path(&path);
            for(p = 0; p < n; p++) {
                if(visit[p]) continue;
                if(graph[j][p] >= INF) continue;
                visit[p] = 1;
                path.step++; path.dist += graph[j][p]; path.nodes[2] = p;
                save_path(&path);
                for(q = 0; q < n; q++) {
                    if(visit[q]) continue;
                    if(graph[p][q] >= INF) continue;
                    visit[q] = 1;
                    path.step++; path.dist += graph[p][q]; path.nodes[3] = q;
                    save_path(&path);
                    for(r = 0; r < n; r++) {
                        if(visit[r]) continue;
                        if(graph[q][r] >= INF) continue;
                        path.step++; path.dist += graph[q][r]; path.nodes[4] = r;
                        save_path(&path);
                        path.step--; path.dist -= graph[q][r];
                    }
                    visit[q] = 0;
                    path.step--; path.dist -= graph[p][q];
                }
                visit[p] = 0;
                path.step--; path.dist -= graph[j][p];
            }
            visit[j] = 0;
            path.step--; path.dist -= graph[i][j];
        }
        visit[i] = 0;
    }
}

int main()
{
    dfs();
    print_result();
    return 0;
}

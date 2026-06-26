#include <stdio.h>

#define MAXN 1000
#define NO_EDGE 0
#define INFINITY 9999999

typedef struct {
    int n;
    int L[MAXN][MAXN];
} Graph;

int mark[MAXN];
int pi[MAXN];
int p[MAXN];
Graph G; 

void init_graph(Graph* G, int n) {
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->L[i][j] = NO_EDGE;
}

void read_graph(Graph* G, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong the mo tap tin %s\n", filename);
        return;
    }
    
    int n, m;
    fscanf(f, "%d %d", &n, &m); 
    
    init_graph(G, n);
    
    int i;
    for (i = 0; i < m; i++) {
        int u, v, w;
        fscanf(f, "%d %d %d", &u, &v, &w);
        G->L[u][v] = w;
    }
    
    fclose(f);
}

void Dijkstra(Graph* G, int s) {
    int i, j, it;
    
    for (i = 1; i <= G->n; i++) {
        pi[i] = INFINITY;
        mark[i] = 0;
    }
    pi[s] = 0;
    p[s] = -1;
    
    for (it = 1; it < G->n; it++) {
        int min_pi = INFINITY;
        for (j = 1; j <= G->n; j++) {
            if (mark[j] == 0 && pi[j] < min_pi) {
                min_pi = pi[j];
                i = j;
            }
        }
            
        mark[i] = 1;
        
        for (j = 1; j <= G->n; j++) {
            if (G->L[i][j] != NO_EDGE && mark[j] == 0) {
                if (pi[i] + G->L[i][j] < pi[j]) {
                    pi[j] = pi[i] + G->L[i][j];
                    p[j] = i;
                }
            }
        }
    }
}

int main() {
    read_graph(&G, "dothi.txt");
    
    Dijkstra(&G, 1);
    
    printf("Ket qua duong di ngan nhat tu dinh 1:\n");
    int i;
    for (i = 1; i <= G.n; i++) {
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
    }
    
    return 0;
}

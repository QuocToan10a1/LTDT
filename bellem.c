#include <stdio.h>

#define MAXN 1000
#define INFINITY 9999999

// C?u trúc luu tr? 1 cung c?a d? th?
typedef struct {
    int u, v; // d?nh d?u u, d?nh cu?i v
    int w;    // tr?ng s? w
} Edge;

// C?u trúc luu tr? d? th? b?ng danh sách cung
typedef struct {
    int n, m; // n: s? d?nh, m: s? cung
    Edge edges[MAXN]; // m?ng luu các cung c?a d? th?
} Graph;

int pi[MAXN];
int p[MAXN];

// Kh?i t?o d? th?
void init_graph(Graph* G, int n) {
    G->n = n;
    G->m = 0;
}

// Thêm 1 cung vào d? th?
void add_edge(Graph* G, int u, int v, int w) {
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->edges[G->m].w = w;
    G->m++;
}

// Gi?i thu?t Bellman - Ford tìm du?ng di ng?n nh?t
void Bellman_Ford(Graph* G, int s) {
    int i, it, k;
    
    // 1. Kh?i t?o
    for (i = 1; i <= G->n; i++) {
        pi[i] = INFINITY;
    }
    pi[s] = 0;
    p[s] = -1; // tru?c d?nh s không có d?nh nào c?
    
    // 2. L?p n-1 l?n
    for (it = 1; it < G->n; it++) {
        // Duy?t qua t?t c? các cung và c?p nh?t (n?u tho? di?u ki?n)
        for (k = 0; k < G->m; k++) {
            int u = G->edges[k].u;
            int v = G->edges[k].v;
            int w = G->edges[k].w;
            
            // Ði?u ki?n pi[u] != INFINITY d? tránh tràn s? (overflow) khi c?ng
            if (pi[u] != INFINITY && pi[u] + w < pi[v]) {
                pi[v] = pi[u] + w;
                p[v] = u;
            }
        }
    }
    
    // 3. Duy?t qua các cung m?t l?n n?a d? phát hi?n chu trình âm
    int negative_cycle = 0;
    for (k = 0; k < G->m; k++) {
        int u = G->edges[k].u;
        int v = G->edges[k].v;
        int w = G->edges[k].w;
        
        if (pi[u] != INFINITY && pi[u] + w < pi[v]) {
            negative_cycle = 1;
            break; // Phát hi?n du?c chu trình âm thì d?ng luôn
        }
    }
    
    // 4. In k?t qu?
    if (negative_cycle) {
        printf("Do thi co chua chu trinh am!\n");
    } else {
        printf("Ket qua duong di ngan nhat tu dinh %d:\n", s);
        for (i = 1; i <= G->n; i++) {
            if (pi[i] == INFINITY) {
                printf("pi[%d] = INFINITY, p[%d] = -1 (Khong the di toi)\n", i, i);
            } else {
                printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
            }
        }
    }
}

int main() {
    Graph G;
    int n, m, i;
    int u, v, w;
    
    // M? t?p tin ch?a d? li?u d? th?
    FILE* f = fopen("dothi.txt", "r");
    if (f == NULL) {
        printf("Khong the mo tap tin dothi.txt\n");
        return 1;
    }
    
    // Ð?c s? d?nh n và s? cung m
    fscanf(f, "%d %d", &n, &m);
    init_graph(&G, n);
    
    // Ð?c thông tin các cung
    for (i = 0; i < m; i++) {
        fscanf(f, "%d %d %d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    
    fclose(f); // Ðóng t?p tin
    
    // Ch?y gi?i thu?t Bellman - Ford b?t d?u t? d?nh 1
    Bellman_Ford(&G, 1);
    
    return 0;
}

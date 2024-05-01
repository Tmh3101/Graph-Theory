 #include <stdio.h>
#include <limits.h>

#define MAXN 100
#define NOEDGE INT_MIN
#define oo 99999

typedef struct {
	int L[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			pG->L[i][j] = NOEDGE;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int w){
	if(w < 0) return;
	pG->L[u][v] = w;
}


int mark[MAXN], pi[MAXN], p[MAXN];
void MooreDijkstra(Graph *pG, int s){
	int u, v, it, j, min_pi;
	for (u = 1; u <= pG->n; u++){
		mark[u] = 0;
		pi[u] = oo;
		p[u] = 0;
	}
	pi[s] = 0;
	p[s] = -1;

	for(it = 1; it < pG->n; it++){
		min_pi = oo;
		for(j = 1; j <= pG->n; j++){
			if(mark[j] == 0 && pi[j] < min_pi){
				min_pi = pi[j];
				u = j;
			}
		}
		mark[u] = 1;
		for(v = 1; v <= pG->n; v++){
			if(pG->L[u][v] != NOEDGE && mark[v] == 0){
				if(pi[u] + pG->L[u][v] < pi[v]){
					pi[v] = pi[u] + pG->L[u][v];
					p[v] = u;
				}
			}
		}
	}
}




int main(){

	Graph G;
	int m, n, u, v, w, e;
	freopen("dothi.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for(e = 1; e <= m; e++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}

	MooreDijkstra(&G, 1);

	for(u = 1; u <= n; u++){
		printf("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, p[u]);
	}


	return 0;
}
#include <stdio.h>
#include <limits.h>

#define MAXN 100
#define NOEDGE INT_MIN
#define oo INT_MAX

typedef struct {
	int A[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			pG->A[i][j] = NOEDGE;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->A[u][v] = w;
}

int mark[MAXN], pi[MAXN], p[MAXN];
void MooreDijkstra(Graph *pG, int s){
	int u, v, it, min_pi, i;
	for(u = 1; u <= pG->n; u++){
		mark[u] = 0;
		pi[u] = oo;
		p[u] = 0;
	}

	pi[s] = 0;
	p[s] = -1;

	for(it = 1; it < pG->n; it++){
		min_pi = oo;
		for(i = 1; i <= pG->n; i++){
			if(mark[i] == 0 && min_pi > pi[i]){
				min_pi = pi[i];
				u = i;
			}
		}

		mark[u] = 1;
		for(v = 1; v <= pG->n; v++){
			if(pG->A[u][v] != NOEDGE && mark[v] == 0){
				if(pi[u] + pG->A[u][v] < pi[v]){
					pi[v] = pi[u] + pG->A[u][v];
					p[v] = u;
				}
			}
		}
	}
}



int main(){

	Graph G;
	int n, m, u, v, w, i;
	freopen("graph.txt", "r", stdin);

	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for(i = 0; i < m; i++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}

	MooreDijkstra(&G, 1);

	for(i = 1; i <= n; i++){
		printf("%d: %d %d\n", i, pi[i], p[i]);
	}



	return 0;
}
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
	pG->L[u][v] = w;
	pG->L[v][u] = w;
}

int mark[MAXN], pi[MAXN], p[MAXN];

int Prim(Graph *pG, Graph *pT, int s){
	int u, v, it, j, min_dist;
	for (u = 1; u <= pG->n; u++){
		mark[u] = 0;
		pi[u] = oo;
		p[u] = -1;
	}
	pi[s] = 0;

	for(it = 1; it <= pG->n; it++){
		min_dist = oo;
		for(j = 1; j <= pG->n; j++){
			if(mark[j] == 0 && pi[j] < min_dist){
				min_dist = pi[j];
				u = j;
			}
		}
		mark[u] = 1;
		printf("%d\n", u);
		for(v = 1; v <= pG->n; v++){
			if(pG->L[u][v] != NOEDGE && mark[v] == 0){
				if(pG->L[u][v] < pi[v]){
					pi[v] = pG->L[u][v];
					p[v] = u;
				}
			}
		}
	}

	init_graph(pT, pG->n);
	int sum_w = 0;

	for(u = 1; u <= pG->n; u++){
		if(p[u] != -1){
			int w = pG->L[p[u]][u];
			add_edge(pT, p[u], u, w);
			sum_w += w;
		}
	}

	return sum_w;
}


int main(){

	Graph G, T;
	int m, n, u, v, w, e;
	freopen("dothi.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for(e = 1; e <= m; e++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}

	Prim(&G, &T, 1);

	return 0;
}
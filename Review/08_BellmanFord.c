#include <stdio.h>
#include <limits.h>

#define MAXM 100
#define MAXN 100
#define NOEDGE INT_MIN
#define oo INT_MAX

typedef struct {
	int u, v, w;
} Edge;

typedef struct {
	Edge edges[MAXM];
	int n, m;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->edges[pG->m].w = w;
	pG->m++;
}

int pi[MAXN], p[MAXN];
void BellmanFord(Graph *pG, int s){
	int u, v, w, it, k;
	for(u = 1; u <= pG->n; u++){
		pi[u] = oo;
		p[u] = 0;
	}

	pi[s] = 0;
	p[s] = -1;

	for(it = 1; it < pG->n; it++){
		for(k = 0; k < pG->m; k++){

			u = pG->edges[k].u;
			v = pG->edges[k].v;
			w = pG->edges[k].w;

			if(pi[u] == oo) continue;
			if(pi[u] + w < pi[v]) {
				pi[v] = pi[u] + w;
				p[v] = u;
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

	BellmanFord(&G, 1);

	for(i = 1; i <= n; i++){
		printf("%d: %d %d\n", i, pi[i], p[i]);
	}



	return 0;
}
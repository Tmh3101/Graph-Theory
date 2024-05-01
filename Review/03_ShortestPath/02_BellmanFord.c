#include <stdio.h>
#define MAXM 100
#define MAXN 100
#define oo 99999

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
	pG->edges[pG->m++].w = w;
}

int pi[MAXN], p[MAXN];
void BellmanFord(Graph *pG, int s){
	int u, v, w;
	for(u = 1; u <= pG->n; u++){
		pi[u] = oo;
		p[u] = 0;
	}

	pi[s] = 0;
	p[s] = -1;

	int i, j;
	for(i = 1; i < pG->n; i++){
		for(j = 0; j < pG->m; j++){

			u = pG->edges[j].u;
			v = pG->edges[j].v;
			w = pG->edges[j].w;

			if(pi[u] == oo) continue;
			if(pi[u] + w < pi[v]){
				pi[v] = pi[u] + w;
				p[v] = u;
			}

		}
	}
}

int main(){
	freopen("graph.txt", "r", stdin);

	Graph G;

	int n, m;
	scanf("%d%d", &n, &m);

	init_graph(&G, n);

	int e, u, v, w;
	for(e = 0; e < m; e++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}

	for(e = 0; e < m; e++){
		printf("%d %d %d\n", G.edges[e].u, G.edges[e].v, G.edges[e].w);
	}

	int s, t;

	scanf("%d%d", &s, &t);

	BellmanFord(&G, s);

	for(u = 1; u <= n; u++){
		printf("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, p[u]);
	}

	printf("--> %d", pi[t]);

	return 0;
}
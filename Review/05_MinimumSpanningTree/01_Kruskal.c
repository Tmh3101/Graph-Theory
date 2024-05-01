#include <stdio.h>
#define MAXM 100
#define MAXN 100

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

int find_root(int *parent, int u){
	if(u == parent[u]) return u;
	return find_root(parent, parent[u]);
}

int Kruskal(Graph *pG, Graph *pT){
	int i, j, e, u, v, w;
	for(i = 0; i < pG->m - 1; i++){
		for(j = pG->m - 1; j > i; j--){
			if(pG->edges[j].w < pG->edges[j - 1].w){
				Edge tmp = pG->edges[j];
				pG->edges[j] = pG->edges[j - 1];
				pG->edges[j - 1] = tmp;
			}
		}
	}

	int parent[MAXN];
	for(i = 1; i <= pG->n; i++){
		parent[i] = i;
	}

	init_graph(pT, pG->n);
	int sum_w = 0;

	for(e = 0; e < pG->m; e++){
		u = pG->edges[e].u;
		v = pG->edges[e].v;
		w = pG->edges[e].w;

		int root_u = find_root(parent, u);
		int root_v = find_root(parent, v);

		if(root_u != root_v){
			add_edge(pT, u, v, w);
			parent[root_v] = root_u;
			sum_w += w;
		}
	}

	return sum_w;
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

	Graph T;
	int sum_w = Kruskal(&G, &T);

	printf("%d\n", sum_w);
	for(e = 0; e < T.m; e++){
		printf("(%d, %d): %d\n", T.edges[e].u, T.edges[e].v, T.edges[e].w);
	}




	return 0;
}
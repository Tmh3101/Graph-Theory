#include <stdio.h>
#define MAX_M 500
#define MAX_N 100

typedef struct {
	int u, v, w;
} Edge;

typedef struct {
	int n, m;
	Edge edges[MAX_M];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edge(Graph *pG, int u, int v, int w){
	if(u > v) {
		pG->edges[pG->m].u = v;
		pG->edges[pG->m].v = u;
	} else {
		pG->edges[pG->m].u = u;
		pG->edges[pG->m].v = v;
	}
	pG->edges[pG->m].w = w;
	pG->m++;
}



int parent[MAX_N];

int find_root(int u){
	if(parent[u] == u) return u;
	return find_root(parent[u]);
}

int Kruskal(Graph *pG, Graph *pT){
	int i, j, u, e;
	for(i = 0; i < pG->m - 1; i++){
		for(j = i + 1; j < pG->m; j++){
			if(pG->edges[i].w > pG->edges[j].w){
				Edge tmp = pG->edges[i];
				pG->edges[i] = pG->edges[j];
				pG->edges[j] = tmp;
			}
		}
	}

	init_graph(pT, pG->n);

	for(u = 1; u <= pG->n; u++){
		parent[u] = u;
	}

	int sum_w = 0;

	for(e = 0; e < pG->m; e++){
		int u = pG->edges[e].u;
		int v = pG->edges[e].v;
		int w = pG->edges[e].w;
		int root_u = find_root(u);
		int root_v = find_root(v);

		if(root_u != root_v){
			add_edge(pT, u, v, w);
			parent[root_v] = root_u;
			sum_w += w;
		}
	}

	return sum_w;

}





int main(){

	Graph G, T;

	freopen("dothi.txt", "r", stdin);
	int n, m, u, v, w, e;

	scanf("%d%d", &n, &m);
 
	init_graph(&G, n);

	for(e = 1; e <= m; e++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}

	int sum_w = Kruskal(&G, &T);
	printf("%d\n", sum_w);

	for(e = 0; e < T.m; e++){
		printf("%d %d %d\n", T.edges[e].u, T.edges[e].v, T.edges[e].w);
	}
	
	return 0;
}
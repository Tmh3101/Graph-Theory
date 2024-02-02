#include <stdio.h>

#define MAXM 100
#define MAXN 50
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
	pG->edges[pG->m].w = w;
	pG->m++;
}

int pi[MAXN], p[MAXN], negative_cycle = 0;
void BellmanFord(Graph *pG, int s){
	int it, k, u, v, w;

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
			if(pi[u] + w < pi[v]){
				pi[v] = pi[u] + w;
				p[v] = u;
			}

		}
	}

	for(k = 0; k < pG->m; k++){

		u = pG->edges[k].u;
		v = pG->edges[k].v;
		w = pG->edges[k].w;

		if(pi[u] == oo) continue;
		if(pi[u] + w < pi[v]){
			negative_cycle = 1;
			return;
		}
	}

}

void print_path(int s, int t){
	int path[MAXN], n = 0;
	path[n++] = t;
	int parent = p[t];

	while(parent != s){
		if(parent == 0) return;
		path[n++] = parent;
		parent = p[parent];
	}
	path[n] = s;

	int i;
	for(i = n; i > 0; i--){
		printf("%d -> ", path[i]);
	}
	printf("%d\n", path[0]);
}


int main(){

	Graph G;
	int u, v, w, n, m, e, s;
	freopen("dothi.txt", "r", stdin);

	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for(e = 0; e < m; e++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
			
	}

	scanf("%d", &s);

	BellmanFord(&G, s);
	printf("%s", (negative_cycle) ? "YES" : "NO");

	return 0;
}
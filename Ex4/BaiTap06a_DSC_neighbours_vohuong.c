#include <stdio.h>
#define MAX_M 500

typedef struct {
	int u, v;
} Edge;

typedef struct {
	int n, m;
	Edge edges[MAX_M];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edge(Graph *pG, int u, int v){
	if(u < 1 || v < 1 || u > pG->n || v > pG->n){
		printf("cung %d %d khong hop le", u, v);
		return;
	}
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->m++;
}

int degree(Graph *pG, int u){
	int deg = 0, i;
	for(i = 0; i < pG->m; i++){
		if(pG->edges[i].u == u) deg++;
		if(pG->edges[i].v == u) deg++;
	}
	return deg;
}

int adjacent(Graph *pG, int u, int v){
	int i;
	for(i = 0; i < pG->m; i++){
		if(pG->edges[i].u == u && pG->edges[i].v == v)
			return 1;
		if(pG->edges[i].u == v && pG->edges[i].v == u)
			return 1;
	}
	return 0;
}

//tim dinh ke nhau voi dinh u - vo huong
void neighbours(Graph *pG, int u){
	int i;
	for(i = 1; i <= pG->n; i++){
		if(adjacent(pG, u, i)) printf("%d ", i);
	}
	printf("\n");
}

int main(){
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	int u, v, i;
	for(i = 0; i < m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	printf("n = %d, m = %d\n", G.n, G.m);
	
	for(i = 1; i <= G.n; i++){
		printf("neighbours(%d) = ", i);
		neighbours(&G, i);
	}
	
	return 0;
}

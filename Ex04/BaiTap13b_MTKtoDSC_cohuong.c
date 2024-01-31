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
	if(u < 1 || v < 1 || u > pG->n || v > pG->n)
		return;
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

void neighbours(Graph *pG, int u){
	int i;
	for(i = 1; i <= pG->n; i++){
		if(adjacent(pG, u, i)) printf(" %d", i);
	}
	printf("\n");
}

int main(){
	Graph G;
	int n;
	scanf("%d", &n);
	init_graph(&G, n);
	
	int input[n][n], i, j, k;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			scanf("%d", &input[i][j]);
		}
	}
	
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			for(k = 1; k <= input[i][j]; k++){
				add_edge(&G, i, j);
			}
		}
	}
	
	for(i = 0; i < G.m; i++){
		printf("%d %d\n", G.edges[i].u, G.edges[i].v);
	}
	
	return 0;
}

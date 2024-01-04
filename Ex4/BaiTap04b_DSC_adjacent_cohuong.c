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

//kiem tra u va v co ke nhau hay khong
int adjacent(Graph *pG, int u, int v){
	int i;
	for(i = 0; i < pG->m; i++){
		if(pG->edges[i].u == u && pG->edges[i].v == v)
			return 1;
	}
	return 0;
}

int main(){
	Graph G;
	init_graph(&G, 4);
	
	add_edge(&G, 1, 2);
	add_edge(&G, 3, 4);
	
	printf("n = %d, m = %d\n", G.n, G.m);
	
	int e;
	for(e = 0; e < G.m; e++){
		printf("%d %d\n", G.edges[e].u, G.edges[e].v);
	}
	
	if(adjacent(&G, 1, 2)) printf("%d la dinh ke cua %d", 2, 1);
	else printf("%d khong phai la dinh ke cua %d", 2, 1);
	
	return 0;
}

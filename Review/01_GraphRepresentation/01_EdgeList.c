//don do thi vo huong

#include <stdio.h>

#define MAX_M 500

typedef struct {
	int u, v;
} Edge;

typedef struct {
	Edge edges[MAX_M];
	int n, m;
} Graph;

void initGraph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void addEdge(Graph *pG, int u, int v){
	if(u == v) return; //khong khuyen

	//don do thi vo huong
	if(adjacent(pG, u, v)) return;

	pG->edges[pG->m].u = u;
	pG->edges[pG->m++].v = v;
}

int adjacent(Graph *pG, int u, int v){
	int e;
	for(e = 0; e < pG->m; e++){
		if(pG->edges[e].u == u && pG->edges[e].v == v) return 1;
		if(pG->edges[e].u == v && pG->edges[e].v == u) return 1;
	}
	return 0;
}

int degree(Graph *pG, int u){
	int e, deg = 0;
	for(e = 0; e < pG->m; e++){
		//deg_out				 //deg_out
		if(u == pG->edges[e].u || u == pG->edges[e].v) deg++;
	}
	return deg;
}




int main(){

	Graph G;

	freopen("graph.txt", "r", stdin);

	int n, m;
	scanf("%d%d", &n, &m);
	initGraph(&G, n);

	int e, u, v;
	for(e = 0; e < m; e++){
		scanf("%d%d", &u, &v);
		addEdge(&G, u, v);
	}

	for(e = 0; e < G.m; e++){
		printf("%d, %d\n", G.edges[e].u, G.edges[e].v);
	}

	return 0;
}
#include <stdio.h>
#define MAX_M 500

typedef struct {
	int u, v;
} Edge;

typedef struct {
	Edge edges[MAX_M];
	int n, m;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edge(Graph *pG, int x, int y){
	pG->edges[pG->m].u = x;
	pG->edges[pG->m].v = y;
	pG->m++;
}

int degree(Graph *pG, int x){
	int deg = 0, i;
	for(i = 0; i < pG->m; i++){
		if(pG->edges[i].u == x) deg++;
		if(pG->edges[i].v == x) deg++;
	}
	return deg;
}

int adjacent(Graph *pG, int x, int y){
	int i;
	for(i = 0; i < pG->m; i++){
		if(pG->edges[i].u == x && pG->edges[i].v == y) return 1;
		if(pG->edges[i].u == y && pG->edges[i].v == x) return 1;
	}
	return 0;
}

void neighbours(Graph *pG, int x){
	int i;
	for(i = 0; i < pG->m; i++){
		if(adjacent(pG, x, i)) printf("%d ", i);
	}
	printf("\n");
}


int main(){
	Graph G;
	freopen("dt.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	int i, u, v;
	for(i = 0; i < m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	printf("n = %d, m = %d\n", G.n, G.m);
	for(i = 0; i < G.m; i++){
		printf("%d %d\n", G.edges[i].u, G.edges[i].v);
	}
	
	printf("Degree:\n");
	for(i = 1; i <= G.n; i++){
		printf("%d %d\n", i, degree(&G, i));
	}
	
	printf("%d ke voi %d: %d\n", 1, 8, adjacent(&G, 1, 8));
	
	printf("cac dinh ke cua 1 la: ");
	neighbours(&G, 1);
	
	
	return 0;
}

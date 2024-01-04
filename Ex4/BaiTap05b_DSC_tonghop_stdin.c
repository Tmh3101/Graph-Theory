#include <stdio.h>
#define MAX_M 500

//khai bao cau truc cung
typedef struct {
	int u, v;
} Edge;

//khai bao cau truc do thi
typedef struct {
	int n, m;
	Edge edges[MAX_M];
} Graph;

//khoi tao do thi
void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

//them cung vao do thi
void add_edge(Graph *pG, int u, int v){
	if(u < 1 || v < 1 || u > pG->n || v > pG->n){
		printf("cung %d %d khong hop le", u, v);
		return;
	}
	pG->edges[pG->m].u = u;
	pG->edges[pG->m].v = v;
	pG->m++;
}

//tinh bac cua mot dinh (bao gom truong hop co khuyen)
int degree(Graph *pG, int u){
	int deg = 0, i;
	for(i = 0; i < pG->m; i++){
		if(pG->edges[i].u == u) deg++;
		if(pG->edges[i].v == u) deg++;
	}
	return deg;
}

int main(){
	Graph G;
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
		printf("degree(%d) = %d\n", i, degree(&G, i));
	}
	
	return 0;
}

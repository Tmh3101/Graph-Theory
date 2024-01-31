#include <stdio.h>
#define MAX_N 100

typedef struct {
	int A[MAX_N][MAX_N];
	int n, m;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	int u, v;
	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			pG->A[u][v] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] += 1;
	pG->m++;	
}

int degree(Graph *pG, int u){
	int deg = 0, i;
	for(i = 1; i <= pG->n; i++){
		deg += pG->A[u][i] + pG->A[i][u];
	}
	return deg + pG->A[u][u];
}

void neighbours(Graph *pG, int u){
	int i;
	for(i = 1; i <= pG->n; i++){
		if(pG->A[u][i] != 0) printf(" %d", i);
	}
	printf("\n");
}


int main(){
	Graph G;
	int n;
	scanf("%d", &n);
	init_graph(&G, n);
	
	int u, v;
	for(u = 1; u <= n; u++){
		do {
			scanf("%d", &v);
			add_edge(&G, u, v);
		} while (v != 0);
	}
	
	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			printf("%d ", G.A[u][v]);
		}
		printf("\n");
	}
	
	return 0;
}

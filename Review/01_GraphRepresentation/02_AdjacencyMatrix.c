#include <stdio.h>
#define MAX_N 100

typedef struct {
	int A[MAX_N][MAX_N];
	int n;
} Graph;

void initGraph(Graph *pG, int n){
	pG->n = n;
	int u, v;
	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			pG->A[u][v] = 0;
		}
	}
}

void addEdge(Graph *pG, int u, int v){
	pG->A[u][v] = 1;
	pG->A[v][u] = 1;
}

int degree(Graph *pG, int u){
	int v, deg = 0;
	for(v = 1; v <= pG->n; v++){
		deg += pG->A[u][v];
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

	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			printf("%d ", G.A[u][v]);
		}
		printf("\n");
	}

	printf("%d\n", degree(&G, 3));

	for(u = 1; u <= n; u++){
		printf("neighbours(%d) =", u);
		for(v = 1; v <= n; v++){
			if(G.A[u][v] != 0) printf(" %d", v);
		}
		printf("\n");
	}
	
	return 0;
}
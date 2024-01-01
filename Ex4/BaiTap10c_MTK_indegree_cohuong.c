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

int indegree(Graph *pG, int u){
	int in_deg = 0, i;
	for(i = 1; i <= pG->n; i++){
		in_deg += pG->A[i][u];
	}
	return in_deg;
}


int main(){
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	int i, u, v;
	for(i = 0; i < m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(u = 1; u <= G.n; u++){
		for(v = 1; v <= G.n; v++){
			printf("%d ", G.A[u][v]);
		}
		printf("\n");
	}
	
	for(i = 1; i <= G.n; i++){
		printf("in_deg(%d) = %d\n", i, indegree(&G, i));
	}
	
	
	return 0;
}

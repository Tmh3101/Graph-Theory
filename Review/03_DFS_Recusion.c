#include <stdio.h>

#define MAXN 100

typedef struct {
	int A[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			pG->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] = 1;
	pG->A[v][u] = 1;
}

int mark[MAXN];
void DFS_Recusion(Graph *pG, int u){

	if(mark[u] == 1) return;

	mark[u] = 1;
	printf("%d ", u);

	int v;
	for(v = 1; v <= pG->n; v++){
		if(pG->A[u][v] != 0) DFS_Recusion(pG, v);
	}
	
}

int main(){

	Graph G;
	int n, m, u, v, i;
	freopen("graph.txt", "r", stdin);

	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for(i = 0; i < m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	for(i = 1; i <= n; i++){
		mark[i] = 0;
	}

	for(i = 1; i <= n; i++){
		if(mark[i] == 0) DFS_Recusion(&G, i);
	}

	return 0;
}
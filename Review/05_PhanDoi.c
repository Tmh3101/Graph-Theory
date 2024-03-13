#include <stdio.h>

#define MAXN 100
#define WHITE 0
#define BLUE 1
#define RED 2

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

int color[MAXN], parent[MAXN], conflict;
void DFS_Recusion_PhanDoi(Graph *pG, int u, int c){

	color[u] = c;
	if(parent[u] == 0) parent[u] = -1;

	int v;
	for(v = 1; v <= pG->n; v++){
		if(pG->A[u][v] != 0 && v != parent[u]){
			parent[v] = u;
			if(color[v] == WHITE) DFS_Recusion_PhanDoi(pG, v, 3 - c);
			else if(color[v] == color[u]) conflict = 1;
		}
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
		color[i] = WHITE;
		parent[i] = 0;
	}

	conflict = 0;

	for(i = 1; i <= n; i++){
		if(color[i] == WHITE) DFS_Recusion_PhanDoi(&G, i, BLUE);
	}

	printf("%s", (conflict) ? "YES" : "NO");

	return 0;
}
#include <stdio.h>

#define MAXN 100
#define WHITE 0
#define GRAY 1
#define BLACK 2

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

int color[MAXN], parent[MAXN], has_circle;
void DFS_Recusion_Circle(Graph *pG, int u){

	color[u] = GRAY;
	if(parent[u] == 0) parent[u] = -1;

	int v;
	for(v = 1; v <= pG->n; v++){
		if(pG->A[u][v] != 0 && v != parent[u]){
			parent[v] = u;
			if(color[v] == WHITE) DFS_Recusion_Circle(pG, v);
			else if(color[v] == GRAY) has_circle = 1;
		}
	}

	color[u] = BLACK;
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

	has_circle = 0;

	for(i = 1; i <= n; i++){
		if(color[i] == WHITE) DFS_Recusion_Circle(&G, i);
	}

	printf("%s", (has_circle) ? "YES" : "NO");

	return 0;
}
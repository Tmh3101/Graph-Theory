#include <stdio.h>
#define MAX_N 20

typedef struct {
	int A[MAX_N][MAX_N];
	int n, m; 

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

void add_edge(Graph *pG, int x, int y){
	pG->A[x][y] = 1;
	pG->A[y][x] = 1;
}

int degree(Graph *pG, int x){
	int deg = 0, i;
	for(i = 1; i <= pG->n; i++){
		if(pG->A[x][i] == 1) deg++;
	}
	return deg;
}

int adjacent(Graph *pG, int x, int y){
	return pG->A[x][y] != 0;
}

void neighbours(Graph *pG, int x){
	int i;
	for(i = 1; i <= pG->n; i++){
		if(adjacent(pG, x, i)) printf("%d ", pG->A[x][i]);
	}
	printf("\n");
}

int main(){

	Graph G;
	int n, m;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	int e, u ,v;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			printf("%d ", G.A[i][j]);
		}
		printf("\n");
	}

	return 0;
}

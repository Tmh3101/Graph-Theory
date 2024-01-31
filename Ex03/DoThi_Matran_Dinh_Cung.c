#include <stdio.h>
#define MAX_N 100
#define MAX_M 500

typedef struct {
	int A[MAX_N][MAX_N];
	int n, m;
} Graph;

void init_graph(Graph *pG, int n, int m){
	pG->n = n;
	pG->m = m;
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			pG->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *pG, int e, int x, int y){
	pG->A[x][e] = 1;
	pG->A[y][e] = 1;
}

int degree(Graph *pG, int x){
	int deg = 0, i;
	for(i = 1; i <= pG->m; i++){
		if(pG->A[x][i] == 1) deg++;
	}
	return deg;
}

int adjacent(Graph *pG, int x, int y){
	int i;
	if(x == y) return 0;
	for(i = 1; i <= pG->m; i++){
		if(pG->A[x][i] == 1 && pG->A[y][i] == 1) return 1;
	}
	return 0;
}

void neighbours(Graph *pG, int x){
	int i;
	for(i = 1; i <= pG->n; i++){
		if(i == x) continue;
		if(adjacent(pG, x, i)) printf("%d ", i);
	}
	printf("\n");
}


int main(){
	
	Graph G;
	int n, m;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);
	
	int e, u ,v;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, e, u, v);
	}
	
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			printf("%d ", G.A[i][j]);
		}
		printf("\n");
	}
	
	printf("degree 5: %d\n", degree(&G, 5));
	printf("neighbours of 5: ");
	neighbours(&G, 5);
	return 0;
}

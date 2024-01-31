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
	pG->A[u][v] = 1;
	pG->A[v][u] = 1;
	pG->m++;	
}

int degree(Graph *pG, int u){
	int deg = 0, i;
	for(i = 1; i <= pG->n; i++){
		deg += pG->A[u][i];
	}
	return deg + pG->A[u][u];
}


int main(){
	
	freopen("dothi.txt", "r", stdin);
    Graph G;
    int n, m, u, v, e;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
	
	for(u = 1; u <= G.n; u++){
		for(v = 1; v <= G.n; v++){
			printf("%d ", G.A[u][v]);
		}
		printf("\n");
	}
	
	for(u = 1; u <= G.n; u++){
		printf("deg(%d) = %d\n", u, degree(&G, u));
	}
	
	int u_maxDeg = 1;
	for(u = 2; u <= G.n; u++){
		if(degree(&G, u) > degree(&G, u_maxDeg)) u_maxDeg = u;
	}
	
	printf("%d %d", u_maxDeg, degree(&G, u_maxDeg));
	
	
	return 0;
}

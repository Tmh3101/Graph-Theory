#include <stdio.h>
#define MAXN 100
#define oo 99999
#define NOEDGE 0

typedef struct {
	int A[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int u, v;
	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			pG->A[u][v] = NOEDGE;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->A[u][v] = w;
	pG->A[v][u] = w;
}

int mark[MAXN], pi[MAXN], p[MAXN];
int Prim(Graph *pG, Graph *pT, int s){
	int u, v, i, j;

	for(u = 1; u <= pG->n; u++){
		mark[u] = 0;
		pi[u] = oo;
		p[u] = 0;
	}

	pi[s] = 0;
	p[s] = -1;

	for(i = 1; i < pG->n; i++){
		int min_dist = oo;
		for(j = 1; j <= pG->n; j++){
			if(mark[j] == 0 && pi[j] < min_dist){
				min_dist = pi[j];
				u = j;
			}
		}

		mark[u] = 1;

		for(v = 1; v <= pG->n; v++){
			if(pG->A[u][v] != NOEDGE && mark[v] == 0){
				if(pG->A[u][v] < pi[v]){
					pi[v] = pG->A[u][v];
					p[v] = u;
				}
			}
		}
	}

	init_graph(pT, pG->n);
	int sum_w = 0;

	for(u = 1; u <= pG->n; u++){
		if(p[u] != -1){
			int w = pG->A[p[u]][u];
			add_edge(pT, p[u], u, w);
			sum_w += w;
		}
	}

	return sum_w;	
}


int main(){
	freopen("graph.txt", "r", stdin);
	Graph G;

	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	int e, u, v, w;
	for(e = 0; e < m; e++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}

	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			printf("%d ", G.A[u][v]);
		}
		printf("\n");
	}

	Graph T;
	int sum_w = Prim(&G, &T, 1);

	printf("%d\n", sum_w);

	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			printf("%d ", T.A[u][v]);
		}
		printf("\n");
	}


	return 0;
}
#include <stdio.h>

#define MAXN 100
#define NOEDGE 100
#define oo 99999

typedef struct{
	int W[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			pG->W[i][j] = NOEDGE;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->W[u][v] = w;
}

int pi[MAXN][MAXN], next[MAXN][MAXN], negative_cycle = 0;
void FloyWarshall(Graph *pG){
	int u, v, k;
	for(u = 1; u <= pG->n; u++){
		for(v = 1; v <= pG->n; v++){
			pi[u][v] = oo;
			next[u][v] = -1;
		}
		pi[u][u] = 0;
	}

	for(u = 1; u <= pG->n; u++){
		for(v = 1; v <= pG->n; v++){
			if(pG->W[u][v] != NOEDGE){
				pi[u][v] = pG->W[u][v];
				next[u][v] = v;
			}
		}
	}

	for(k = 1; k <= pG->n; k++){
		for(u = 1; u <= pG->n; u++){
			for(v = 1; v <= pG->n; v++){
				if(pi[u][k] != oo && pi[k][v] != oo && pi[u][k] + pi[k][v] < pi[u][v]){
					pi[u][v] = pi[u][k] + pi[k][v];
					next[u][v] = next[u][k];
				}
			}
		}	
	}

	for(u = 1; u <= pG->n; u++){
		if(pi[u][u] < 0){
			negative_cycle = 1;
			break;
		}
	}

}




int main(){
	Graph G;

	freopen("dothi.txt", "r", stdin);
	int n, m, u, v, w, e;

	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for(e = 0; e < m; e++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}

	FloyWarshall(&G);

	if(negative_cycle) printf("YES");
	else printf("NO");

	return 0;
}
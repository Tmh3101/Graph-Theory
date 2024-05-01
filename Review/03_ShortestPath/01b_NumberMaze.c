#include <stdio.h>
#define MAXN 100
#define oo 99999
#define NODEGE -1

typedef struct {
	int A[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int u, v;
	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			pG->A[u][v] = NODEGE;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->A[u][v] = w;
}

int pi[MAXN], p[MAXN], mark[MAXN];
void MooreDijkstra(Graph *pG, int s){
	int u, v, i, j;
	for(u = 1; u <= pG->n; u++){
		pi[u] = oo;
		p[u] = 0;
		mark[u] = 0;
	}

	pi[s] = 0;
	p[s] = -1;

	for(i = 1; i < pG->n; i++){
		int min_pi = oo;
		for(j = 1; j <=pG->n; j++){
			if(mark[j] == 0 && pi[j] < min_pi){
				min_pi = pi[j];
				u = j;
			}
		}

		mark[u] = 1;
		for(v = 1; v <= pG->n; v++){
			if(pG->A[u][v] != NODEGE && mark[v] == 0){
				if(pi[u] + pG->A[u][v] < pi[v]){
					pi[v] = pi[u] + pG->A[u][v];
					p[v] = u;
				}
			}
		}
	}

}

int main(){

	freopen("numbermaze.txt", "r", stdin);

	int n, m;
	scanf("%d%d", &m, &n);

	int matrix[m][n];

	int i, j;
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			scanf("%d", &matrix[i][j]);
		}
	}

	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	Graph G;
	init_graph(&G, m * n);

	int u, v;
	for(u = 1; u <= m * n; u++){
		i = (u - 1) / n;
		j = (u - 1) % n;

		int di[] = {-1 , 1, 0, 0};
		int dj[] = {0 , 0, 1, -1};

		int k;
		for(k = 0; k < 4; k++){
			int ii = i + di[k];
			int jj = j + dj[k];

			if(ii >= 0 && ii <= m && jj >= 0 && jj <= n){
				v = ii * n + jj + 1;
				add_edge(&G, u, v, matrix[ii][jj]);
			}

		}

	}

	for(u = 1; u <= G.n; u++){
		for(v = 1; v <= G.n; v++){
			if(G.A[u][v] == NODEGE) printf("- ");
			else printf("%d ", G.A[u][v]);
		}
		printf("\n");
	}

	MooreDijkstra(&G, 1);

	for(u = 1; u <= n; u++){
		printf("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, p[u]);
	}

	printf("%d", pi[m * n]);

	return 0;
}
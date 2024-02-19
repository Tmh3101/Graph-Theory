#include <stdio.h>
#include <limits.h>

#define MAXN 100
#define NOEDGE 0
#define oo 99999

typedef struct {
	int L[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			pG->L[i][j] = NOEDGE;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int w){
	pG->L[u][v] = w;
}


int mark[MAXN], pi[MAXN], p[MAXN];
void MooreDijkstra(Graph *pG, int s){
	int u, v, it, j, min_pi;
	for (u = 1; u <= pG->n; u++){
		mark[u] = 0;
		pi[u] = oo;
		p[u] = 0;
	}
	pi[s] = 0;
	p[s] = -1;

	for(it = 1; it < pG->n; it++){
		min_pi = oo;
		for(j = 1; j <= pG->n; j++){
			if(mark[j] == 0 && pi[j] < min_pi){
				min_pi = pi[j];
				u = j;
			}
		}
		mark[u] = 1;
		for(v = 1; v <= pG->n; v++){
			if(pG->L[u][v] != NOEDGE && mark[v] == 0){
				if(pi[u] + pG->L[u][v] < pi[v]){
					pi[v] = pi[u] + pG->L[u][v];
					p[v] = u;
				}
			}
		}
	}
}

void print_path(int s, int t){
	int path[MAXN], n = 0;
	path[n++] = t;

	int parent = p[t];
	while(parent != s){
		if(parent == 0) return;
		path[n++] = parent;
		parent = p[parent];
	}
	path[n] = s;

	int i;
	for(i = n; i > 0; i--){
		printf("%d -> ", path[i]);
	}
	printf("%d\n", path[0]);

}

int main(){

	Graph G;
	int m, n, u, v, w, e, i, j;
	freopen("dothi.txt", "r", stdin);
	scanf("%d%d", &m, &n);
	init_graph(&G, m * n);

	int matrix[m][n];
	
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
	printf("\n");
	
	
	for(u = 1; u <= m * n; u++){
		i = (u - 1) / n;
		j = (u - 1) % n;
		
		int di[] = {-1, 1, 0, 0};
		int dj[] = {0, 0, -1, 1};
		
		int k;
		for(k = 0; k < 4; k++){
			int ii = i + di[k];
			int jj = j + dj[k];
			
			if(ii >= 0 && ii < m && jj >= 0 && jj < n){
				v = ii * n + jj + 1;
				//printf("%d\n", matrix[ii][jj]);
				add_edge(&G, u, v, matrix[ii][jj]);
			}
		
		}
		
	}
	
	for(u = 1; u <= n * m; u++){
		for(v = 1; v <= n * m; v++){
			printf("%d ", G.L[u][v]);
		}
		printf("\n");
	}
	printf("\n");

	MooreDijkstra(&G, 1);
	
	
	for(u = 1; u <= n * m; u++){
		printf("pi[%d] = %d\n", u, pi[u]);
	}
	
	

	printf("%d", pi[m * n]);

	return 0;
}

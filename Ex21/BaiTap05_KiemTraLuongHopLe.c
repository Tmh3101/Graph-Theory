#include <stdio.h>

#define MAXN 100
#define NO_EDGE 0
#define oo 99999

typedef struct {
	int C[MAXN][MAXN];//kha nang thong qua
	int F[MAXN][MAXN];//luong qua cung
	int n; //so dinh
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			pG->C[i][j] = NO_EDGE;
			pG->F[i][j] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int c, int f){
	pG->C[u][v] = c;
	pG->F[u][v] = f;
}

int main(){

	Graph G;
	int n, m, u, v, e, c, f;
	freopen("data_BT5.txt", "r", stdin);
	scanf("%d%d", &n, &m);

	init_graph(&G, n);

	for(e = 0; e < m; e++){
		scanf("%d%d%d%d", &u, &v, &c, &f);
		add_edge(&G, u, v, c, f);
	}
	
	int out = 0, in = 0;
	for(u = 1; u <= n; u++){
		out += G.F[1][v];
		in += G.F[v][n];
		
		int F_in = 0, F_out = 0;
		for(v = 1; v <= n; v++){
			
			if(G.F[u][v] > G.C[u][v]){
				printf("NO");
				return 0;
			}
			
			if(u != 1 && u != n){
				F_in += G.F[v][u];
				F_out += G.F[u][v];
			} 
		}
		if(F_in != F_out){
			printf("NO");
			return 0;
		}
	}
	
	if(out != in){
		printf("NO");
		return 0;
	}

	printf("YES");
	return 0;
}

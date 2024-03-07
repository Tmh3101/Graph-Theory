#include <stdio.h>

#define MAXN 100

typedef struct {
	int A[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 1; i <= pG->n; i++){
		for(j = 1; j <= pG->n; j++){
			pG->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] = 1;
}

typedef struct {
	int data[100];
	int size;
} List;

void make_null_list(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[(pL->size)++] = x;
}

int element_at(List *pL, int i){
	return pL->data[i - 1];
}

void copy_list(List *S1, List *S2){
	S1->size = 0;
	int i;
	for(i = 1; i <= S2->size; i++){
		push_back(S1, element_at(S2, i));
	}
}

int r[MAXN];
void ranking(Graph *pG){
	int u, v, i;
	int d[MAXN];
	for(u = 1; u <= pG->n; u++){
		d[u] = 0;
		r[u] = -1;
		for(v = 1; v <= pG->n; v++){
			if(pG->A[v][u] != 0) d[u]++;
		}
	}

	List S1, S2;
	make_null_list(&S1);

	for(u = 1; u <= pG->n; u++){
		if(d[u] == 0) push_back(&S1, u);
	}

	int k = 0;
	while(S1.size > 0){
		make_null_list(&S2);

		for(i = 1; i <= S1.size; i++){
			u = element_at(&S1, i);
			r[u] = k;

			for(v = 1; v <= pG->n; v++){
				if(pG->A[u][v] != 0){
					d[v]--;
					if(d[v] == 0) push_back(&S2, v);
				}
			}
		}

		copy_list(&S1, &S2);
		k++;
	}

}


int main(){

	Graph G;

	freopen("dothi.txt", "r", stdin);
	int n, m, u, v, e;

	scanf("%d%d", &n, &m);

	init_graph(&G, n);

	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	ranking(&G);

	for(u = 1; u <= n; u++){
		printf("r[%d] = %d\n", u, r[u]);
	}

	return 0;
}
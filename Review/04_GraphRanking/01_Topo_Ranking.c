#include <stdio.h>
#define MAXN 100

typedef struct {
	int A[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int u, v;
	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			pG->A[u][v] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] += 1;
}

typedef struct {
	int data[100];
	int size;
} List;

void make_null_list(List *pL){
	pL->size = 0;
}

int empty(List *pL){
	return pL->size == 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size++] = x;
}

int get_element_at(List *pL, int i){
	return pL->data[i];
}

void copy_list(List *pL1, List *pL2){
	make_null_list(pL1);
	int i;
	for(i = 0; i < pL2->size; i++){
		push_back(pL1, get_element_at(pL2, i));
	}
}

int r[MAXN];
void topo_ranking(Graph *pG){

	int d[MAXN];

	int u, v;
	for(u = 1; u <= pG->n; u++){
		r[u] = -1;
		d[u] = 0;
		for(v = 1; v <= pG->n; v++){
			if(pG->A[v][u] != 0) d[u]++;
		}
	}

	List L1, L2;
	make_null_list(&L1);
	for(u = 1; u <= pG->n; u++){
		if(d[u] == 0) push_back(&L1, u);
	}

	int k = 0;
	while(!empty(&L1)){
		make_null_list(&L2);
		int i;
		for(i = 0; i < L1.size; i++){
			u = get_element_at(&L1, i);
			r[u] = k;

			for(v = 1; v <= pG->n; v++){
				if(pG->A[u][v] != 0){
					d[v]--;
					if(d[v] == 0) push_back(&L2, v);
				}
			}
		}

		k++;
		copy_list(&L1, &L2);
	}

}

int main(){
	freopen("graph.txt", "r", stdin);
	Graph G;

	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	int e, u ,v;
	for(e = 0; e < m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	topo_ranking(&G);

	for(u = 1; u <= n; u++){
		printf("r[%d] = %d\n", u, r[u]);
	}

	return 0;
}
#include <stdio.h>
#define MAXN 100
#define oo 99999

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

int indegree(Graph *pG, int u){
	int v, deg = 0;
	for(v = 1; v <= pG->n; v++){
		deg += pG->A[v][u];
	}
	return deg;
}

int outdegree(Graph *pG, int u){
	int v, deg = 0;
	for(v = 1; v <= pG->n; v++){
		deg += pG->A[u][v];
	}
	return deg;
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
List topo_ranking(Graph *pG){
	List topo;
	make_null_list(&topo);

	int d[MAXN];

	int u, v;
	for(u = 1; u <= pG->n; u++){
		r[u] = -1;
		d[u] = 0;
		for(v = 1; v <= pG->n; v++){
			d[u] = indegree(pG, u);
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
			push_back(&topo, u);
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

	return topo;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int min(int a, int b){
	return (a < b) ? a : b;
}

int main(){
	freopen("graph.txt", "r", stdin);
	Graph G;

	int n;
	scanf("%d", &n);
	init_graph(&G, n + 2);

	int d[MAXN];
	int u, v, i;
	for(u = 1; u <= n; u++){
		scanf("%d", &d[u]);
		do {
			scanf("%d", &v);
			if(v != 0) add_edge(&G, v, u);
		} while(v != 0);
	}

	int alpha = n + 1;
	int beta = n + 2;

	for(u = 1; u <= n; u++){
		if(indegree(&G, u) == 0) add_edge(&G, alpha, u);
		if(outdegree(&G, u) == 0) add_edge(&G, u, beta);
	}

	for(u = 1; u <= n + 2; u++){
		for(v = 1; v <= n + 2; v++){
			printf("%d ", G.A[u][v]);
		}
		printf("\n");
	}

	List topo = topo_ranking(&G);

	for(i = 0; i < topo.size; i++){
		printf("%d ", get_element_at(&topo, i));
	}

	int t[MAXN], T[MAXN];

	t[alpha] = 0;
	for(i = 1; i < topo.size; i++){
		int u = get_element_at(&topo, i);
		t[u] = -oo;
		for(v = 1; v <= G.n; v++){
			if(G.A[v][u] != 0){
				t[u] = max(t[u], t[v] + d[v]);
			}
		}
	}

	T[beta] = t[beta];
	for(i = topo.size - 2; i >= 0 ; i--){
		int u = get_element_at(&topo, i);
		T[u] = oo;
		for(v = 1; v <= G.n; v++){
			if(G.A[u][v] != 0){
				T[u] = min(T[u], T[v] - d[u]);
			}
		}
	}

	printf("\n");
	for(u = 1; u <= n + 2; u++){
		printf("t[%d] = %d, T[%d] = %d\n", u, t[u], u, T[u]);
	}

	return 0;
}
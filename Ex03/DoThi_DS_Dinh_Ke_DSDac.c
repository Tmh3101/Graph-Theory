#include <stdio.h>
#define MAX_N 100
#define MAX_M 500

typedef struct {
	int data[MAX_N];
	int size;
} List;

void make_null(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
}

int element_at(List *pL, int p){
	return pL->data[p - 1];
}

int size(List *pL){
	return pL->size;
}

typedef struct {
	List adj[MAX_N];
	int n, m;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	int i;
	for(i = 1; i <= n; i++){
		make_null(&(pG->adj[i]));
	}
}

void add_edge(Graph *pG, int x, int y){
	push_back(&(pG->adj[x]), y);
	push_back(&(pG->adj[y]), x);
	pG->m++;
}

int degree(Graph *pG, int x){
	return pG->adj[x].size;
}

int adjacent(Graph *pG, int x, int y){
	int i;
	for(i = 1; i <= pG->adj[x].size; i++){
		if(element_at(&(pG->adj[x]), i) == y) return 1;
	}
	return 0;
}

void neighbours(Graph *pG, int x){
	int i;
	for(i = 1; i <= pG->adj[x].size; i++){
		printf("%d ", element_at(&(pG->adj[x]), i));
	}
	printf("\n");
}

int main(){
	
	Graph G;
	int n, m;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	int e, u ,v;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	int i, j;
	for(i = 1; i <= G.n; i++){
		printf("%d: ", i);
		for(j = 1; j <= G.m; j++){
			printf("%d ", element_at(&(G.adj[i]), j));
		}
		printf("\n");
	}
	
	printf("Degree 5: %d\n", degree(&G, 5));
	printf("Neighbours of 5: ");
	neighbours(&G, 5);
	
	return 0;
}

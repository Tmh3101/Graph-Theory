#include <stdio.h>
#define MAX_ELEMENTS 100
#define MAX_N 100

typedef struct {
	int data[MAX_ELEMENTS];
	int size;
} List;

void make_null(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
}

int element_at(List *pL, int i){
	return pL->data[i - 1];
}

typedef struct {
	int n;
	List adj[MAX_N];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i;
	for(i = 1; i <= n; i++){
		make_null(&(pG->adj[i]));
	}
}

void add_edge(Graph *pG, int u, int v){
	push_back(&(pG->adj[u]), v);
	if(u != v) push_back(&(pG->adj[v]), u);	
}

int adjacent(Graph *pG, int u, int v){
	int i;
	for(i = 1; i <= pG->adj[u].size; i++){
		if(element_at(&(pG->adj[u]), i) == v) return 1;
	}
	return 0;
}

int degree(Graph *pG, int u){
	return pG->adj[u].size;
}

void neighbours(Graph *pG, int u){
	int i;
	for(i = 1; i <= pG->adj[u].size; i++){
		printf("%d ", element_at(&(pG->adj[u]), i));
	}
}

int main(){
	
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m, i, j, u, v;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(i = 0; i < m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(i = 1; i <= G.n; i++){
		printf("%d: ", i);
		neighbours(&G, i);
		printf("=> deg(%d) = %d\n", i, degree(&G, i));
	}
	
	
	
	return 0;
}

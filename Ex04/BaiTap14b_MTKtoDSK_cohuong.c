#include <stdio.h>
#define MAX_ELEMENTS 100
#define MAX_N 100

typedef struct {
	int data[MAX_ELEMENTS];
	int size;
} List;

void make_null(List *pL){
	pL->size = 0;
	pL->data[pL->size] = 0;
}

void push_back(List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
	pL->data[pL->size] = 0;
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
	int n;
	scanf("%d", &n);
	init_graph(&G, n);
	
	int input[n + 1][n + 1], i, j, k;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			scanf("%d", &input[i][j]);
		}
	}
	
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			for(k = 0; k < input[i][j]; k++){
				add_edge(&G, i, j);
			}
		}
	}
	
	for(i = 1; i <= n; i++){
		for(j = 1; j <= G.adj[i].size + 1; j++){
			printf("%d ", element_at(&G.adj[i], j));
		}
		printf("\n");
	}
	
	
	return 0;
}

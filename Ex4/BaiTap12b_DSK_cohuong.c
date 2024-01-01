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
}

int adjacent(Graph *pG, int u, int v){
	int i;
	for(i = 1; i <= pG->adj[u].size; i++){
		if(element_at(&(pG->adj[u]), i) == v) return 1;
	}
	return 0;
}

int indegree(Graph *pG, int u){
	return pG->adj[u].size;
}

int outdegree(Graph *pG, int u){
	int deg = 0, i, j;
	for(i = 1; i <= pG->n; i++){
		for(j = 1; j <= pG->adj[i].size; j++){
			if(u == element_at(&(pG->adj[i]), j)) deg++;
		}
	}
	return deg;
}

void neighbours(Graph *pG, int u){
	int i, j;
	for(i = 1; i <= pG->adj[u].size; i++){
		printf("%d ", element_at(&(pG->adj[u]), i));
	}
	for(i = 1; i <= pG->n; i++){
		if(i == u) continue;
		for(j = 1; j <= pG->adj[i].size; j++){
			if(u == element_at(&(pG->adj[i]), j)) {
				printf("%d ", i);
				break;
			}
		}
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
		for(j = 1; j <= G.adj[i].size; j++){
			printf("%d ", element_at(&(G.adj[i]), j));
		}
		printf("\n");
	}
	
	printf("==================================\n");
	
	for(i = 1; i <= G.n; i++){
		printf("neighbours(%d): ", i);
		neighbours(&G, i);
		printf("=> in_deg(%d) = %d ", i, indegree(&G, i));
		printf("|| out_deg(%d) = %d\n", i, indegree(&G, i));
	}
	
	
	
	return 0;
}

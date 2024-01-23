#include <stdio.h>
#define MAX_N 20
#define MAX_Lenght 20
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct {
	int A[MAX_N][MAX_N];
	int n;
} Graph;

void init_Graph(Graph *G, int n){
	int i, j;
	G->n = n;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
}

int adjacent(Graph *G, int x, int y){
	return G->A[x][y] != 0;
}

int degree(Graph *G, int x){
	int deg = 0, i;
	for(i = 1; i <= G->n; i++){
		if(adjacent(G, i, x)) deg++;
	}
	return deg;
}

typedef struct {
	int data[MAX_Lenght];
	int size;
} List;

void make_null_list(List *list){
	list->size = 0;
}

void push_back(List *list, int x){
	list->data[list->size] = x;
	list->size++;
}

int element_at(List *list, int i){
	return list->data[i - 1];
}

List neighbors(Graph *G, int n){
	List L;
	make_null_list(&L);
	int i;
	for(i = 1; i <= G->n; i++){
		if(adjacent(G, n, i)){
			push_back(&L, i);
		}
	}
	return L;
}

int mark[MAX_N]; 

int color[MAX_N];
int has_circle;
void DFS_Recursion(Graph *G, int u){
	
	color[u] = GRAY;
	
	List L = neighbors(G, u);
	int i;
	for(i = 1; i <= L.size; i++){
		int v = element_at(&L, i);
		if(color[v] == WHITE) DFS_Recursion(G, v);
		else if(color[v] == GRAY) has_circle = 1; 
	}
	color[u] = BLACK;
}

int main(){
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m, i;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int e, u, v;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(i = 1; i <= n; i++){
		mark[i] = 0;
		color[i] = WHITE;
	}
	has_circle = 0;
	
	for(i = 1; i <= n; i++){
		if(color[i] == WHITE){
			DFS_Recursion(&G, i);
		}
	}
	
	if(has_circle) printf("NO");
	else printf("YES");
		
	return 0;
}

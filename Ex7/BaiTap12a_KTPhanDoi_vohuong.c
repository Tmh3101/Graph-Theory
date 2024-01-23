#include <stdio.h>
#define MAX_N 20
#define MAX_Lenght 20
#define NO_COLOR 0
#define BLUE 1
#define RED 2

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

int color[MAX_N];
int conflict;
void DFS_Recursion(Graph *G, int u, int c){
	
	//to mau dinh dang duyet
	color[u] = c;
	
	//xet cac dinh ke cua u
	List L = neighbors(G, u);
	int i;
	for(i = 1; i <= L.size; i++){
		int v = element_at(&L, i);
		if(color[v] == NO_COLOR) DFS_Recursion(G, v, 3 - c); //neu v chua duyet -> duyet no
		else if(color[v] == color[u]) conflict = 1;
	}
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
		color[i] = NO_COLOR;
	}
	conflict = 0;
	
	for(i = 1; i <= n; i++){
		if(color[i] == NO_COLOR){
			DFS_Recursion(&G, i, BLUE);
		}
	}
	
	if(conflict) printf("IMPOSSIBLE");
	else {
		for(i = 1; i <= n; i++){
			if(color[i] == BLUE){
				printf("%d ", i);
			}
		}
		printf("\n");
		for(i = 1; i <= n; i++){
			if(color[i] == RED){
				printf("%d ", i);
			}
		}
	}
		
	return 0;
}

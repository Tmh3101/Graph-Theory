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
	G->A[y][x] = 1;
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
int has_circle;
int parent[MAX_N];
void DFS_Recursion(Graph *G, int u, List *list){
	
	if(has_circle) return;
	//to mau dinh dang duyet
	color[u] = GRAY;
	if(parent[u] == 0) parent[u] = -1;
	//xet cac dinh ke cua u
	List L = neighbors(G, u);
	int i;
	for(i = 1; i <= L.size; i++){
		int v = element_at(&L, i);
		if(parent[u] == v) continue;
		parent[v] = u;
		if(color[v] == WHITE) DFS_Recursion(G, v, list); //neu v chua duyet -> duyet no
		else if(color[v] == GRAY){
			has_circle = 1; //neu v dang duoc duyet->quay lai mot nut nao do-> co chua chu trinh
			push_back(list, v);
			push_back(list, u);
			int x = parent[u];
			while(x != v){
				push_back(list, x);
				x = parent[x];
			}
			push_back(list, x);
		}
	}
	//danh dau u da duyet
	color[u] = BLACK;
}

int main(){
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int e, u, v;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(i = 1; i <= n; i++){
		parent[i] = 0;
		color[i] = WHITE;
	}
	has_circle = 0;
	
	List list;
	make_null_list(&list);
	for(i = 1; i <= n; i++){
		if(color[i] == WHITE){
			DFS_Recursion(&G, i, &list);
			if(has_circle) {
				for(j = 1; j <= list.size; j++){
					printf("%d ", element_at(&list, j));
				}
				return 0;
			}
		}
	}
	printf("-1");
		
	return 0;
}

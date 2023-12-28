#include <stdio.h>
#define MAX_Vertices 20
#define MAX_Length 20


typedef struct {
	int A[MAX_Vertices][MAX_Vertices];
	int n; //so luong dinh

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
		if(adjacent(G, x, i)) deg++;
	}
	return deg;
}

//Tao cau truc danh sach phuc vu cho viec lay cac neighbors cua mot dinh
typedef struct {
	int data[MAX_Length];
	int size;
} List;

void make_null(List *list){
	list->size = 0;
}

void push_back(List *list, int x){
	list->data[list->size] = x;
	list->size++;
}

int element_at(List list, int i){
	return list.data[i - 1];
}

List neighbors(Graph *G, int x){
	List L;
	make_null(&L);
	int i;
	for(i = 1; i <= G->n; i++){
		if(adjacent(G, x, i)) push_back(&L, i);
	}
	return L;
}

int main(){

	Graph G;
	int n, m;
	freopen("DFS.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	
	int e, u ,v;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			printf("%d ", G.A[i][j]);
		}
		printf("\n");
	}

	return 0;
}

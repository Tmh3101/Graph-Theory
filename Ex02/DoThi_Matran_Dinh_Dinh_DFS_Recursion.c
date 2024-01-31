#include <stdio.h>
#define MAX_Vectices 20
#define MAX_Lenght 20

typedef struct {
	int A[MAX_Vectices][MAX_Vectices];
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

//xem hai dinh co la lang gieng hay khong
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

//tao cau truc list de phuc vu cho viec lay dan sach lang gieng
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

int element_at(List list, int i){
	return list.data[i - 1];
}

List neighbors(Graph *G, int n){
	List L;
	make_null_list(&L);
	int i;
	for(i = 1; i <= G->n; i++){
		if(adjacent(G, i, n)){
			push_back(&L, i);
		}
	}
	return L;
}

int mark[MAX_Vectices];
void DFS_Recursion(Graph *G, int u){
	if(mark[u] == 1) return;
	printf("%d\n", u);
	mark[u] = 1;
	List list = neighbors(G, u);
	int i;
	for(i = 1; i <= list.size; i++){
		DFS_Recursion(G, element_at(list, i));
	}
}


int main(){
	Graph G;
	freopen("DFS_Recursion.txt", "r", stdin);
	int n, m; //n - so dinh, m - so cung
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int e, u, v, i;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(i = 1; i <= n; i++){
		mark[i] = 0;
	}
	
	DFS_Recursion(&G, 1);
	
	
	
	return 0;
}



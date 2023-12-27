#include <stdio.h>
#define MAX_Vectices 20
#define MAX_Lenght 20
#define MAX_Stack 40

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

//khoi tao cau truc ngan xep
typedef struct {
	int data[MAX_Stack];
	int size;
} Stack;

void make_null_stack(Stack *S){
	S->size = 0;
}

int empty(Stack S){
	return S.size == 0;
}

void push_stack(Stack *S, int n){
	S->data[S->size] = n;
	S->size++;
}

int top(Stack S){
	return S.data[S.size - 1];
}

int pop(Stack *S){
	S->size--;
}

List depth_first_search(Graph *G, int n){
	//dua mot dinh vao ngan xep
	Stack S;
	make_null_stack(&S);
	push_stack(&S, n);
	List list_dfs;
	make_null_list(&list_dfs);
	
	//khoi tao danh sach danh dau cac dinh da duoc duyet
	int mark[MAX_Vectices], i;
	for(i = 1; i <= G->n; i++){
		mark[i] = 0;
	}
	
	//trong khi ngan xep khac rong
	while(!empty(S)){
		//lay mot dinh tu ngan xep
		int u = top(S);
		pop(&S);
		
		//bo qua neu u da duoc duyet
		if(mark[u] == 1) continue;
		
		//duyet u va danh dau da duyet
		push_back(&list_dfs, u);
		mark[u] = 1;
		
		//lay danh sach lang gieng
		List list = neighbors(G, u);
		
		for(i = 1; i <= list.size; i++){
			int v = element_at(list, i);
			if(mark[v] == 0){
				push_stack(&S, v); 
			}
		}
	}
	return list_dfs;
}

int main(){
	Graph G;
	freopen("DFS.txt", "r", stdin);
	int n, m; //n - so dinh, m - so cung
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int e, u, v;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	int mark_dfs[MAX_Vectices], i, j;
	for(i = 1; i <= G.n; i++){
		mark_dfs[i] = 0;
	}
	
	for(i = 1; i <= G.n; i++){
		if(mark_dfs[i] == 0){
			List dfs = depth_first_search(&G, i);
			for(j = 1; j <= dfs.size; j++){
				printf("Duyet: %d\n", element_at(dfs, j));
				mark_dfs[element_at(dfs, j)] = 1;
			}			
		}
	}
	
	

	
	return 0;
}



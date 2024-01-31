#include <stdio.h>
#define MAX_N 20
#define MAX_Lenght 20

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

typedef struct {
	int data[MAX_Lenght];
	int top;
} Stack;

void make_null_stack(Stack *pS){
	pS->top = -1;
}

int empty(Stack *pS){
	return pS->top == -1;
}

void push_stack(Stack *pS, int x){
	pS->top++;
	pS->data[pS->top] = x;
}

int top(Stack *pS){
	return pS->data[pS->top];
}

void pop(Stack *pS){
	pS->top--;
}

int min(int a, int b){
	return (a < b) ? a : b;
}

int num[MAX_N], min_num[MAX_N], k, on_stack[MAX_N];
Stack S;
int strong_connected;

void SCC(Graph *pG, int u){
	num[u] = k;
	min_num[u] = k;
	k++;
	push_stack(&S, u);
	on_stack[u] = 1;
	
	List list = neighbors(pG, u);
	int i;
	for(i = 1; i <= list.size; i++){
		int v = element_at(&list, i);
		if(num[v] == -1){
			SCC(pG, v);
			min_num[u] = min(min_num[u], min_num[v]);
		} else if (on_stack[v]) {
			min_num[u] = min(min_num[u], num[v]);
		}
	}
	
	if(min_num[u] == num[u]){
		strong_connected++;
		int w;
		do {
			w = top(&S);
			pop(&S);
			on_stack[w] = 0;
		} while (w != u);
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
	
	k = 1;
	make_null_stack(&S);
	strong_connected = 0;
	for(i = 1; i <= n; i++){
		num[i] = -1;
		on_stack[i] = 0;
	}
	
	for(i = 1; i <= n; i++){
		if(num[i] == -1) SCC(&G, i);
	}
	
	printf("%d", strong_connected);
		
	return 0;
}

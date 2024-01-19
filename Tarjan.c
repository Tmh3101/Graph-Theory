#include <stdio.h>

#define MAX_N 100
#define MAX_Element 100

typedef struct{
	int data[MAX_Element];
	int size;
} List;

void make_null_list(List *pL){
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
	int A[MAX_N][MAX_N];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] += 1;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] != 0;
}

List neighbours(Graph *pG, int u){
	List list;
	make_null_list(&list);
	int v;
	for(v = 1; v <= pG->n; v++){
		if(adjacent(pG, u, v)) push_back(&list, v);
	}
	return list;
}

typedef struct {
	int data[MAX_Element];
	int top;
} Stack;

void make_null_stack(Stack *pS){
	pS->top = -1;
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

int empty(Stack *pS){
	return pS->top == -1;
}

int min(int a, int b){
	return (a < b) ? a : b;
}

int num[MAX_N];
int min_num[MAX_N];
int k;
Stack S;
int on_stack[MAX_N];

void SCC(Graph *pG, int u){
	num[u] = k;
	min_num[u] = k;
	k++;
	push_stack(&S, u);
	on_stack[u] = 1;

	List list = neighbours(pG, u);
	int i;
	for(i = 1; i <= list.size; i++){
		int v = element_at(&list, i);
		if(num[v] == -1) {
			SCC(pG, v);
			min_num[u] = min(min_num[u], min_num[v]);
		}
		else if(on_stack[u] == 1){
			min_num[u] = min(min_num[u], num[v]);
		}
	}

	if(num[u] == min_num[u]){
		printf("Tim duoc BPLT manh, %d la dinh khop: ", u);
		int w;
		Stack tmp;
		make_null_stack(&tmp);
		do {
			w = top(&S);
			pop(&S);
			on_stack[w] = 0;
			push_stack(&tmp, w);
		} while (w != u);

		while(!empty(&tmp)){
			printf("%d ", top(&tmp));
			pop(&tmp);
		}
		printf("\n");
	}
}



int main(){
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	int i, u, v, e;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	for(i = 1; i <= n; i++){
		num[i] = -1;
	}

	make_null_stack(&S);
	k = 1;

	for(u = 1; u <= n; u++){
		if(num[u] == -1) SCC(&G, u);
	}

	return 0;
}
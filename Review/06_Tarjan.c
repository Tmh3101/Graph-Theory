#include <stdio.h>

#define MAXN 100

typedef struct {
	int A[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			pG->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] = 1;
}

typedef struct {
	int data[100];
	int top;
} Stack;

void make_null_stack(Stack *pS){
	pS->top = -1;
}

void push(Stack *pS, int x){
	pS->data[++(pS->top)] = x;
	pS->data[pS->top] = x;
}

int pop(Stack *pS){
	return pS->data[(pS->top)--];
}

int empty(Stack *pS){
	return pS->top == -1;
}

int min(int a, int b){
	return (a < b) ? a : b;
}

int num[MAXN], min_num[MAXN], on_stack[MAXN], k;
Stack S;
void Tarjan(Graph *pG, int u){
	num[u] = k;
	min_num[u] = k;
	k++;

	push(&S, u);
	on_stack[u] = 1;

	int v;
	for(v = 1; v <= pG->n; v++){
		if(pG->A[u][v] != 0){
			if(num[v] == -1){
				Tarjan(pG, v);
				min_num[u] = min(min_num[u], min_num[v]);
			} else if(on_stack[v]) {
				min_num[u] = min(min_num[u], num[v]);
			}
		}
	}

	if(min_num[u] == num[u]){
		int w;
		do{
			w = pop(&S);
			on_stack[w] = 0;
		} while (w != u);
	}

}

int main(){

	Graph G;
	int n, m, u, v, i;
	freopen("graph.txt", "r", stdin);

	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	for(i = 0; i < m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	for(i = 1; i <= n; i++){
		num[i] = -1;
		on_stack[i] = 0;
	}
	k = 1;
	make_null_stack(&S);

	for(i = 1; i <= n; i++){
		if(num[i] == -1) Tarjan(&G, i);
	}

	for(i = 1; i <= n; i++){
		printf("%d %d\n", num[i], min_num[i]);
	}


	return 0;
}
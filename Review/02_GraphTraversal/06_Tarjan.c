#include <stdio.h>
#define MAXN 100
#define WHITE 0
#define BLUE 1
#define RED 2

typedef struct {
	int A[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int u, v;
	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			pG->A[u][v] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] = 1;
	//pG->A[v][u] = 1;
}

typedef struct {
	int data[MAXN];
	int top;
} Stack;

void make_null_stack(Stack *pS){
	pS->top = -1;
}

int empty(Stack *pS){
	return pS->top == -1;
}

void push(Stack *pS, int x){
	pS->data[++pS->top] = x;
}

int pop(Stack *pS){
	return pS->data[pS->top--];
}

int min(int a, int b){
	return (a < b) ? a : b;
}

int num[MAXN], min_num[MAXN], on_stack[MAXN], k;
Stack S;
void Tarjan(Graph *pG, int u){
	num[u] = k;
	min_num[u] = k++;

	push(&S, u);
	on_stack[u] = 1;

	int v;
	for(v = 1; v <= pG->n; v++){
		if(pG->A[u][v] == 0) continue;
		if(num[v] == -1) {
			Tarjan(pG, v);
			min_num[u] = min(min_num[u], min_num[v]);
		} else if(on_stack[v]) {
			min_num[u] = min(min_num[u], num[v]);
		}
	}

	if(num[u] == min_num[u]){
		int w;
		do {
			w = pop(&S);
			on_stack[w] = 0;
		} while(w != u);
	}

}

int main(){
	Graph G;
	freopen("graph.txt", "r", stdin);

	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);

	int e, u, v;
	for(e = 0; e < m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			printf("%d ", G.A[u][v]);
		}
		printf("\n");
	}

	for(u = 1; u <= n; u++){
		num[u] = -1;
		on_stack[u] = 0;
	}
	k = 1;
	make_null_stack(&S);

	for(u = 1; u <= n; u++){
		if(num[u] == -1) Tarjan(&G, 1);
	}
	
	for(u = 1; u <= n; u++){
		printf("%d %d\n", num[u], min_num[u]);
	}


	return 0;
}
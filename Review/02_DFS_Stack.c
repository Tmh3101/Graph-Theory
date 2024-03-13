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
	pG->A[v][u] = 1;
}

typedef struct {
	int u, p;
} ElementType;

typedef struct {
	ElementType data[100];
	int top;
} Stack;

void make_null_stack(Stack *pS){
	pS->top = -1;
}

void push(Stack *pS, ElementType x){
	pS->data[++(pS->top)].u = x.u;
	pS->data[pS->top].p = x.p;
}

ElementType pop(Stack *pS){
	return pS->data[(pS->top)--];
}

int empty(Stack *pS){
	return pS->top == -1;
}

int mark[MAXN], p[MAXN];
void DFS(Graph *pG, int s){
	Stack S;
	make_null_stack(&S);

	ElementType pair;
	pair.u = s;
	pair.p = -1;

	push(&S, pair);

	while(!empty(&S)){

		ElementType pair = pop(&S);

		int u = pair.u;
		int p = pair.p;

		if(mark[u] == 1) continue;

		printf("%d %d\n", u, p);
		mark[u] = 1;

		int v;
		for(v = 1; v <= pG->n; v++){
			if(pG->A[u][v] != 0){
				ElementType pair;
				pair.u = v;
				pair.p = u;
				push(&S, pair);
			}
		}
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
		mark[i] = 0;
		p[i] = 0;
	}

	for(i = 1; i <= n; i++){
		if(mark[i] == 0) DFS(&G, i);
	}

	return 0;
}
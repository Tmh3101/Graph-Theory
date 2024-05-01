#include <stdio.h>
#define MAXN 100

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
	pG->A[v][u] = 1;
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


int mark[MAXN];
void DFS(Graph *pG, int s){
	Stack S;
	make_null_stack(&S);

	push(&S, s);

	while(!empty(&S)){
		int u = pop(&S);
		if(mark[u]) continue;

		mark[u] = 1;
		printf("%d ", u);

		int v;
		for(v = pG->n; v >= 1; v--){
			if(pG->A[u][v] != 0) push(&S, v);
		}
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
		mark[u] = 0;
	}

	for(u = 1; u <= n; u++){
		if(mark[u] == 0) DFS(&G, 1);
	}


	return 0;
}
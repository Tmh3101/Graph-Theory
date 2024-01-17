#include <stdio.h>
#define MAX_N 100

typedef struct {
	int A[MAX_N][MAX_N];
	int n, m;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	int u, v;
	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			pG->A[u][v] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] += 1;
	pG->A[v][u] += 1;
	pG->m++;	
}

typedef struct {
	int data[100];
	int size;
} List;

void make_null_list(List *L){
	L->size = 0;
}

void push_back(List *L, int x){
	L->data[L->size] = x;
	L->size++;
}

int element_at(List *L, int i){
	return L->data[i - 1];
}

List neighbours(Graph *pG, int u){
	int i;
	List L;
	make_null_list(&L);
	for(i = 1; i <= pG->n; i++){
		if(pG->A[u][i] != 0) push_back(&L, i);
	}
	return L;
}

typedef struct {
	int data[50];
	int top;
} Stack;

void make_null_stack(Stack *S){
	S->top = -1;
}

int empty(Stack *S){
	return S->top == -1;
}

void push_stack(Stack *S, int x){
	S->top++;
	S->data[S->top] = x;
}

int top(Stack *S){
	return S->data[S->top];
}

void pop(Stack *S){
	S->top--;
}

int mark[MAX_N];
List BFS(Graph *G, int s){
	List res;
	make_null_list(&res);

	Stack S;
	make_null_stack(&S);
	push_stack(&S, s);
	
	while(!empty(&S)){
		int u = top(&S);
		pop(&S);

		if(mark[u] != 0) continue;
		push_back(&res, u);
		mark[u] = 1;

		List list = neighbours(G, u);
		int i;
		for(i = 1; i <= list.size; i++){
			int v = element_at(&list, i);
			if(mark[v] == 0) push_stack(&S, v);
		}
	}
	return res;
}


int main(){
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	int i, u, v;
	for(i = 0; i < m; i++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for(i = 1; i <= n; i++){
		mark[i] = 0;
	}
	
	List bfs = BFS(&G, 1);
	for(i = 1; i <= bfs.size; i++){
		printf("%d ", element_at(&bfs, i));
	}

	for(i = 1; i <= n; i++){
		if(mark[i] == 0) {
			printf("\nNO");
			return 0;
		}
	}
	printf("\nYES");
	
	return 0;
}

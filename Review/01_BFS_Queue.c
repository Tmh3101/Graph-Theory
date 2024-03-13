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
	int front, rear;
} Queue;

void make_null_queue(Queue *pQ){
	pQ->front = 0;
	pQ->rear = -1;
}

void enqueue(Queue *pQ, ElementType x){
	pQ->data[++(pQ->rear)].u = x.u;
	pQ->data[pQ->rear].p = x.p;
}

ElementType dequeue(Queue *pQ){
	return pQ->data[(pQ->front)++];
}

int empty(Queue *pQ){
	return pQ->rear < pQ->front;
}


int mark[MAXN], p[MAXN];
void BFS(Graph *pG, int s){
	Queue Q;
	make_null_queue(&Q);

	ElementType pair;

	pair.u = s;
	pair.p = -1;

	enqueue(&Q, pair);

	while(!empty(&Q)){
		ElementType pair = dequeue(&Q);

		int u = pair.u;
		int p = pair.p;

		if(mark[u] == 1) continue;

		printf("%d %d\n", u, p);
		mark[u] = 1;

		int v;
		for(v = 1; v <= pG->n; v++){
			if(pG->A[u][v] != 0) {
				ElementType pair;
				pair.u = v;
				pair.p = u;
				enqueue(&Q, pair);
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
		if(mark[i] == 0) BFS(&G, i);
	}

	return 0;
}
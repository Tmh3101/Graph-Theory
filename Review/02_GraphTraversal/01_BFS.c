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
	int data[100];
	int front, rear;
} Queue;

void make_null_queue(Queue *pQ){
	pQ->front = 0;
	pQ->rear = -1;
}

int empty(Queue *pQ){
	return pQ->front > pQ->rear;
}

void enQueue(Queue *pQ, int x){
	pQ->data[++pQ->rear] = x;
}

int deQueue(Queue *pQ){
	return pQ->data[pQ->front++];
}


int mark[MAXN];
void BFS(Graph *pG, int s){
	Queue Q;
	make_null_queue(&Q);

	enQueue(&Q, s);

	while(!empty(&Q)){
		int u = deQueue(&Q);
		if(mark[u]) continue;

		mark[u] = 1;
		printf("%d ", u);

		int v;
		for(v = 1; v <= pG->n; v++){
			if(pG->A[u][v] != 0) enQueue(&Q, v);
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
		if(mark[u] == 0) BFS(&G, 1);
	}


	return 0;
}
#include <stdio.h>

#define MAXN 100

typedef struct {
	int A[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 1; i <= pG->n; i++){
		for(j = 1; j <= pG->n; j++){
			pG->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *pG, int u, int v){
	pG->A[u][v] = 1;
}

typedef struct {
	int data[100];
	int size;
} List;

void make_null_list(List *pL){
	pL->size = 0;
}

void push_back(List *pL, int x){
	pL->data[(pL->size)++] = x;
}

int element_at(List *pL, int i){
	return pL->data[i - 1];
}

typedef struct {
	int data[100];
	int front, rear;
} Queue;

void make_null_queue(Queue *pQ){
	pQ->front = 0;
	pQ->rear = -1;
}

int empty_queue(Queue *pQ){
	return pQ->rear < pQ->front;
}

void enqueue(Queue *pQ, int x){
	pQ->data[++(pQ->rear)] = x;
}

int dequeue(Queue *pQ){
	return pQ->data[(pQ->front)++];
}

List topo_sort(Graph *pG){
	List topo;
	make_null_list(&topo);

	int u, v, x;
	int d[MAXN];
	for(u = 1; u <= pG->n; u++){
		d[u] = 0;
		for(x = 1; x <= pG->n; x++){
			if(pG->A[x][u] != 0) d[u]++;
		}
	}

	Queue Q;
	make_null_queue(&Q);

	for(u = 1; u <= pG->n; u++){
		if(d[u] == 0) enqueue(&Q, u);
	}

	while(!empty_queue(&Q)){
		u = dequeue(&Q);
		push_back(&topo, u);

		for(v = 1; v <= pG->n; v++){
			if(pG->A[u][v] != 0){
				d[v]--;
				if(d[v] == 0) enqueue(&Q, v);
			}
		}
	}

	return topo;

}


int main(){

	Graph G;

	freopen("dothi.txt", "r", stdin);
	int n, m, u, v, e, i;

	scanf("%d%d", &n, &m);

	init_graph(&G, n);

	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	List topo = topo_sort(&G);

	for(i = 1; i <= topo.size; i++){
		printf("%d ", element_at(&topo, i));
	}

	return 0;
}
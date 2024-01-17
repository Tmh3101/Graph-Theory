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

void merge_list(List *L1, List *L2){
	int i;
	for(i = 1; i <= L2->size; i++){
		push_back(L1, element_at(L2, i));
	}
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
	int u, p;
} ElementType;

typedef struct {
	ElementType data[100];
	int front, rear;
} Queue;

void make_nulL_queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

int empty(Queue *Q){
	return Q->rear < Q->front;
}

void enqueue(Queue *Q, ElementType x){
	Q->rear++;
	Q->data[Q->rear].u = x.u;
	Q->data[Q->rear].p = x.p;
	
}

ElementType front(Queue *Q){
	return Q->data[Q->front];
}

void dequeue(Queue *Q){
	Q->front++;
}

int mark[MAX_N];
int parent[MAX_N];
List BFS(Graph *G, int s){
	List res;
	make_null_list(&res);

	Queue Q;
	make_nulL_queue(&Q);

	ElementType pair;
	pair.u = s;
	pair.p = -1;

	enqueue(&Q, pair);
	
	while(!empty(&Q)){
		ElementType pair = front(&Q);
		dequeue(&Q);

		int u = pair.u;
		int p = pair.p;

		if(mark[u] != 0) continue;

		push_back(&res, u);
		mark[u] = 1;
		parent[u] = p;

		List list = neighbours(G, u);
		int i;
		for(i = 1; i <= list.size; i++){
			int v = element_at(&list, i);
			if(mark[v] == 0) {
				ElementType pair;
				pair.u = v;
				pair.p = u;
				enqueue(&Q, pair);
			}
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
		parent[i] = 0;
	}

	
	List bfs = BFS(&G, 1);
	for(i = 2; i <= n; i++){
		if(mark[i] == 0){
			List l = BFS(&G, i);
			merge_list(&bfs, &l);
		}
	}

	printf("Thu tu duyet: ");
	for(i = 1; i <= bfs.size; i++){
		printf("%d ", element_at(&bfs, i));
	}

	printf("\nTree:");
	for(i = 1; i <= n; i++){
		printf("\n%d %d", i, parent[i]);
	}


	
	
	return 0;
}

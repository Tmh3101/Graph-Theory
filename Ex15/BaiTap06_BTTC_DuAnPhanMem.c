#include <stdio.h>

#define MAXN 100
#define oo 99999

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

int deg_in(Graph *pG, int u){
	int deg = 0, v;
	for(v = 1; v <= pG->n; v++){
		if(pG->A[v][u] != 0) deg++;
	}
	return deg;
}

int deg_out(Graph *pG, int u){
	int deg = 0, v;
	for(v = 1; v <= pG->n; v++){
		if(pG->A[u][v] != 0) deg++;
	}
	return deg;
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

void copy_list(List *S1, List *S2){
	S1->size = 0;
	int i;
	for(i = 1; i <= S2->size; i++){
		push_back(S1, element_at(S2, i));
	}
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

	int u, v;
	int deg[MAXN];
	for(u = 1; u <= pG->n; u++){
		deg[u] = deg_in(pG, u);
	}

	Queue Q;
	make_null_queue(&Q);

	for(u = 1; u <= pG->n; u++){
		if(deg[u] == 0) enqueue(&Q, u);
	}

	while(!empty_queue(&Q)){
		u = dequeue(&Q);
		push_back(&topo, u);

		for(v = 1; v <= pG->n; v++){
			if(pG->A[u][v] != 0){
				deg[v]--;
				if(deg[v] == 0) enqueue(&Q, v);
			}
		}
	}

	return topo;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int min(int a, int b){
	return (a < b) ? a : b;
}

int main(){

	Graph G;

	freopen("bttc_dapm.txt", "r", stdin);
	int n, m, u, v, e, i;

	scanf("%d", &n);
 
	init_graph(&G, n + 2);
	int alpha = n + 1, beta = n + 2;
	int d[MAXN];

	for(u = 1; u <= n; u++){
		scanf("%d", &d[u]);
	}

	scanf("%d", &m);

	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	for(u = 1; u <= G.n - 2; u++){
		if(deg_in(&G, u) == 0) add_edge(&G, alpha, u);
		else if(deg_out(&G, u) == 0) add_edge(&G, u, beta);
	}

	List L = topo_sort(&G);

	//tinh t[u] - thoi gian som nhat
	int t[MAXN];
	t[alpha] = 0;

	for(i = 2; i <= L.size; i++){ //khong can tinh alpha
		u = element_at(&L, i);
		t[u] = -oo;

		for(v = 1; v <= G.n; v++){
			if(G.A[v][u] != 0) {
				t[u] = max(t[u], t[v] + d[v]);
			}
		}
	}

	//tinh T[u] - thoi gian tre nhat
	// int T[MAXN];
	// T[beta] = t[beta];

	// for(i = L.size - 1; i >= 1; i--){ //khong can tinh beta
	// 	u = element_at(&L, i);
	// 	T[u] = +oo;

	// 	for(v = 1; v <= G.n; v++){
	// 		if(G.A[u][v] != 0) {
	// 			T[u] = min(T[u], T[v] - d[u]);
	// 		}
	// 	}
	// }

	printf("%d", t[beta]);

	return 0;
}
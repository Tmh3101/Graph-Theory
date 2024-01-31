#include <stdio.h>
#define MAX_Vertices 20
#define MAX_Length 20
#define MAX_Element 40


typedef struct {
	int A[MAX_Vertices][MAX_Vertices];
	int n; //so luong dinh

} Graph;

void init_Graph(Graph *G, int n){
	int i, j;
	G->n = n;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

int adjacent(Graph *G, int x, int y){
	return G->A[x][y] != 0;
}

int degree(Graph *G, int x){
	int deg = 0, i;
	for(i = 1; i <= G->n; i++){
		if(adjacent(G, x, i)) deg++;
	}
	return deg;
}

//Tao cau truc danh sach phuc vu cho viec lay cac neighbors cua mot dinh
typedef struct {
	int data[MAX_Length];
	int size;
} List;

void make_null(List *list){
	list->size = 0;
}

void push_back(List *list, int x){
	list->data[list->size] = x;
	list->size++;
}

int element_at(List list, int i){
	return list.data[i - 1];
}

List neighbors(Graph *G, int x){
	List L;
	make_null(&L);
	int i;
	for(i = 1; i <= G->n; i++){
		if(adjacent(G, x, i)) push_back(&L, i);
	}
	return L;
}

typedef struct {
	int data[MAX_Element];
	int front, rear;
} Queue;

void make_null_Queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

int empty_Queue(Queue Q){
	return Q.front > Q.rear;
}

void push_Queue(Queue *Q, int x){
	Q->rear++;
	Q->data[Q->rear] = x;
}

int pop_Queue(Queue *Q){
	int res = Q->data[Q->front];
	Q->front++;
	return res;
}

void breach_first_search(Graph *G){
	Queue Q;
	make_null_Queue(&Q);
	
	int mark[MAX_Vertices];
	int i;
	for(i = 1; i <= G->n; i++){
		mark[i] = 0;
	}
	push_Queue(&Q, 1);
	
	while(!empty_Queue(Q)){
		int u = pop_Queue(&Q);
		if(mark[u] == 1) continue;
		printf("%d\n", u);
		mark[u] = 1;
		
		List L = neighbors(G, u);
		for(i = 1; i <= L.size; i++){
			int v = element_at(L, i);
			if(mark[v] == 0) push_Queue(&Q, v);
		}
	}
}

int main(){

	Graph G;
	int n, m;
	freopen("BFS.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	
	int e, u ,v;
	for(e = 1; e <= m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	breach_first_search(&G);

	return 0;
}

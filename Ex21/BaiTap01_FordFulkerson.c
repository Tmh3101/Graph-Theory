#include <stdio.h>

#define MAXN 100
#define NO_EDGE 0
#define oo 99999

typedef struct {
	int C[MAXN][MAXN];//kha nang thong qua
	int F[MAXN][MAXN];//luong qua cung
	int n; //so dinh
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			pG->C[i][j] = NO_EDGE;
			pG->F[i][j] = NO_EDGE;
		}
	}
}

void add_edge(Graph *pG, int u, int v, int c){
	pG->C[u][v] = c;
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

void enqueue(Queue *pQ, int x) {
	pQ->data[++(pQ->rear)] = x;
}

int dequeue(Queue *pQ){
	return pQ->data[(pQ->front)++];
}

int min(int a, int b){
	return (a < b) ? a : b;
}

typedef struct {
	int dir;
	int p;
	int sigma;
} Label;

Label labels[MAXN];

int FordFulkerson(Graph *pG, int s, int t){
	int max_flow = 0;
	int u, v;

	Queue Q;
	do {

		//B1: xoa cac nhan va gan nhan cho dinh s, dua s vao queue
		for(u = 1; u <= pG->n; u++){
			labels[u].dir = 0;
		}
		labels[s].dir = 1;
		labels[s].p = s;
		labels[s].sigma = oo;

		make_null_queue(&Q);
		enqueue(&Q, s);

		//B2: Lap gan nhan cho cac dinh tim duong tang luong
		int found = 0;
		while(!empty(&Q)){

			u = dequeue(&Q);
			for(v = 1; v <= pG->n; v++){
				//cung thuan
				if(pG->C[u][v] != NO_EDGE && labels[v].dir == 0 && pG->F[u][v] < pG->C[u][v]){
					labels[v].dir = 1;
					labels[v].p = u;
					labels[v].sigma = min(labels[u].sigma, pG->C[u][v] - pG->F[u][v]);
					enqueue(&Q, v);
				}
				//cung nghich
				else if(pG->C[v][u] != NO_EDGE && labels[v].dir == 0 && pG->F[v][u] > 0){
					labels[v].dir = -1;
					labels[v].p = u;
					labels[v].sigma = min(labels[u].sigma, pG->F[v][u]);
					enqueue(&Q, v);
				}
			}

			if(labels[t].dir != 0){
				found = 1;
				break;
			}
		}

		//B3: tang luong
		if(found == 1){
			int sigma = labels[t].sigma;
			u = t;

			while(u != s){
				int p = labels[u].p;
				if(labels[u].dir == 1) pG->F[p][u] += sigma;
				else if(labels[u].dir == -1) pG->F[p][u] -= sigma;
				u = p;
			}

			max_flow += sigma;

		} else break;


	} while(1);

	return max_flow;
}

int main(){

	Graph G;
	int n, m, u, v, e, c;
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &n, &m);

	init_graph(&G, n);

	for(e = 0; e < m; e++){
		scanf("%d%d%d", &u, &v, &c);
		add_edge(&G, u, v, c);
	}

	int max_flow = FordFulkerson(&G, 1, n);
	printf("Max flow: %d", max_flow);

	return 0;
}
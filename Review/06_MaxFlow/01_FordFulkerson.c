#include <stdio.h>
#define MAXN 100
#define NOEDGE 0
#define oo 99999

typedef struct {
	int C[MAXN][MAXN];
	int F[MAXN][MAXN];
	int n;
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	int u, v;
	for(u = 1; u <= n; u++){
		for(v = 1; v <= n; v++){
			pG->C[u][v] = NOEDGE;
			pG->F[u][v] = NOEDGE;
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

void en_queue(Queue *pQ, int x){
	pQ->data[++pQ->rear] = x;
}

int de_queue(Queue *pQ){
	return pQ->data[pQ->front++];
}

int min(int a, int b){
	return (a < b) ? a : b;
}

typedef struct {
	int dir, p, sigma;
} Label;

Label labels[MAXN];

int FordFulkerson(Graph *pG, int s, int t){
	int max_flow = 0;

	do {

		int u, v;
		for(u = 1; u <= pG->n; u++){
			labels[u].dir = 0;
		}

		labels[s].dir = 1;
		labels[s].p = s;
		labels[s].sigma = oo;

		Queue Q;
		make_null_queue(&Q);
		en_queue(&Q, s);

		int found = 0;
		while(!empty(&Q)){
			u = de_queue(&Q);
			for(v = 1; v <= pG->n; v++){

				if(pG->C[u][v] != NOEDGE && labels[v].dir == 0 && pG->F[u][v] < pG->C[u][v]){
					labels[v].dir = 1;
					labels[v].p = u;
					labels[v].sigma = min(labels[u].sigma, pG->C[u][v] - pG->F[u][v]);
					en_queue(&Q, v);
				}

				if(pG->C[v][u] != NOEDGE && labels[v].dir == 0 && pG->F[v][u] > 0){
					labels[v].dir = -1;
					labels[v].p = u;
					labels[v].sigma = min(labels[u].sigma, pG->F[u][v]);
					en_queue(&Q, v);
				}
			}

			if(labels[t].dir != 0){
				found = 1;
				break;
			}
		}

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
	freopen("graph.txt", "r", stdin);
	Graph G;

	int n, m;
	scanf("%d%d", &n, &m);

	init_graph(&G, n);

	int e, u, v, c;
	for(e = 1; e <= m; e++){
		scanf("%d%d%d", &u, &v, &c);
		add_edge(&G, u, v, c);
	}

	int max_flow = FordFulkerson(&G, 1, n);
	printf("Max flow: %d", max_flow);
	printf("\nS:");
	for(u = 1; u <= n; u++){
		if(labels[u].dir != 0) printf(" %d", u);
	}

	printf("\nT:");
	for(u = 1; u <= n; u++){
		if(labels[u].dir == 0) printf(" %d", u);
	}

	return 0;
}
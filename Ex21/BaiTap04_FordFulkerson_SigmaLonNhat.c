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
	int dir;
	int p;
	int sigma;
} Label;
Label labels[MAXN];

//List co thu tu
typedef struct {
	int data[100];
	int lenght;
} List;

void make_null_list(List *pL){
	pL->lenght = 0;
}

int empty(List *pL){
	return !(pL->lenght);
}

void push_list(List *pL, int x){
	pL->data[(pL->lenght)++] = x;
	int i, j;
	for(i = 0; i < pL->lenght; i++){
		for(j = pL->lenght - 1; j > i; j--){
			if(labels[pL->data[j]].sigma < labels[pL->data[j - 1]].sigma){
				int tmp = pL->data[j];
				pL->data[j] = pL->data[j - 1];
				pL->data[j - 1] = tmp;
			}
		}
	}
}

int pop_list(List *pL){
	int tmp = pL->data[pL->lenght - 1];
	(pL->lenght)--;
	return tmp;
}

int min(int a, int b){
	return (a < b) ? a : b;
}


int FordFulkerson(Graph *pG, int s, int t){
	int max_flow = 0;
	int u, v;

	List L;
	do {

		//B1: xoa cac nhan va gan nhan cho dinh s, dua s vao queue
		for(u = 1; u <= pG->n; u++){
			labels[u].dir = 0;
		}
		labels[s].dir = 1;
		labels[s].p = s;
		labels[s].sigma = oo;

		make_null_list(&L);
		push_list(&L, s);

		//B2: Lap gan nhan cho cac dinh tim duong tang luong
		int found = 0;
		while(!empty(&L)){

			u = pop_list(&L);
			for(v = 1; v <= pG->n; v++){
				//cung thuan
				if(pG->C[u][v] != NO_EDGE && labels[v].dir == 0 && pG->F[u][v] < pG->C[u][v]){
					labels[v].dir = 1;
					labels[v].p = u;
					labels[v].sigma = min(labels[u].sigma, pG->C[u][v] - pG->F[u][v]);
					push_list(&L, v);
				}
				//cung nghich
				else if(pG->C[v][u] != NO_EDGE && labels[v].dir == 0 && pG->F[v][u] > 0){
					labels[v].dir = -1;
					labels[v].p = u;
					labels[v].sigma = min(labels[u].sigma, pG->F[v][u]);
					push_list(&L, v);
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
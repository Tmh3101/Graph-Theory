#include <stdio.h>

#define MAXN 100
#define MAXN 500
#define INF 99999

typedef struct {
	int u, v, w, link;
} Edge;

typedef struct {
	int n, m;
	Edge edges[MAXM];
} Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
}

void add_edge(Graph *pG, int u, int v, int w, int link){
	int m = pG->m;
	pG->edges[m].u = u;
	pG->edges[m].v = v;
	pG->edges[m].w = w;
	pG->edges[m].link = link;
	pG->m++;
}

typedef struct {
	int n;
	int parent[MAXN];
	int weight[MAXN];
	int link[MAXN];
} Tree;

void init_tree(Tree *pT, int n){
	pT->n = n;
	int i;
	for(i = 1; i <= n; i++){
		pT->parent[i] = -1;
		pT->weight[i] = INF;
		pT->link[i] = -1;
	}
}

void buildH(Graph *pG, int root, Tree *pH){
	init_tree(pH, pG->n);
	int e;
	for(e = 0; e < pG->m; e++){
		int u = pG->edges[e].u;
		int v = pG->edges[e].v;
		int w = pG->edges[e].w;
		int link = pG->edges[e].link;

		if(w < pH->weight[v]){
			pH->parent[v] = u;
			pH->weight[v] = w;
			H->link[v] = link;
		}

	}

	pH->parent[root] = -1;
	pH->weight[root] = 0;
}

int id[MAXN];
int find_cycles(Tree *pH, int root){
	int i, u, no = 0;
	int color[MAXN];
	for(i = 1; i <= pH->n; i++){
		id[i] = -1;
		color[i] = -1;
	}

	for(i = 1; i <= pH->n; i++){
		int u = i;
		while(u != root && id[u] == -1 && color[u] != i){
			color[u] = i;
			u = pH->parent[u];
		}

		if(color[u] == i){
			no++;
			int v = pH->parent[u];
			while(v != u){
				id[v] = no;
				v = pH->parent[v];
			}
			id[u] = no;
		}
	}
	return no;
}

void contact(Graph *pG, Tree *pH, int no, Graph *pG1){
	init_graph(pG1, no);
	int e;
	for(e = 0; e < pG->m; e++){
		int u = pG->edges[e].u;
		int v = pG->edges[e].v;
		int w = pG->edges[e].w;

		if(id[u] != id[v]){
			add_edge(G1, id[u], id[v], w - pH->weight[v], e);
		}
		
	}
}

void expand(Tree *pH, Graph *pG1, Tree *pH1){
	int i;
	for(i = 1; i <= pH->n; i++){
		Edge pe = pG1->edges[H->link[i]];

		pH1->parent[pe.v] = pe.u;
		pH1->weight[pe.v] += pH->weight[i];
		pH1->link[pe.v] = pe.link;
	}
}

#define MAXIT 10
void ChuLiu(Graph *pG0, int s, Tree *pT){
	Graph G[MAXN];
	Tree H[MAXN];
	int i, e;

	int t = 0;
	int root = s;
	G[0] = *pG0;

	//Pha co
	while(1){
		//Xay dung do thi xap thi
		buildH(&G[t], root, &H[t]);
		int no = find_cycles(&H[t], root);
		if(no == 0) break;

		//Dat ten moi cho cac dinh khong nam trong CT
		for(i = 1; i <= H[t].n; i++){
			if(id[i] == -1) id[i] = ++no;
		}

		//Co
		contract(&G[t], &H[t], no, &G[t + 1]);
		root = id[root]; //goc moi
		t++;

		//Pha gian
		int k;
		for(k = t; k > 0; k--){
			expand(&H[k], &G[k - 1], &H[k - 1]);
		}

		//Ket qua la H[0]
		*pT = H[0];
	}

}


int main(){
	Graph G;
	int n, m, i, e, u, v, w;

	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 0; e < m; e++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w - 1);
	}

	Tree T;
	ChuLiu(&G, 1, &T);

	for(i = 1; i <= T.n; i++){
		if(T.parent[i] != -1){
			printf("(%d, %d) %d\n", T.parent[i], i, T.weight[i]);
		}
	}

	return 0;
}
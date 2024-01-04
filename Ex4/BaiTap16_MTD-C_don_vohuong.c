#include <stdio.h>
#define MAX_N 100
#define MAX_N 500

typedef struct {
	int n, m;
	int A[MAX_N][MAX_M];	
} Graph;

void init_graph(Graph *pG, int n, int m){
	pG->n = n;
	pG->m = m;
	int u, e;
	for(u = 1; u <= n; u++){
		for(e = 1; e <= m; e++){
			pG->A[u][e] = 0;
		}
	}
}

void add_edge(Graph *pG, int e, int u, int v){
	pG->A[u][e] = 1;
	pG->A[u][e] = 1;
}

int adjacent(Graph *pG, int u, int v){
	int e;
	for(e = 1, e <= pG->m; e++){
		if(pG->A[u][e] == 1 && pG->A[v][e] == 1) return 1;
	}
	return 0;
}

int degree(Graph *pG, int u){
	int deg = 0, e;
	for(e = 1; e <= pG->m; e++){
		if(pG->A[u][e] == 1) deg++;
	}
	return deg;
}



#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct {
    ElementType data[MAX_ELEMENTS];
    int size;
} List;

void make_null(List* L) {
    L->size = 0;
}

void push_back(List* L, ElementType x) {
    L->data[L->size] = x;
    L->size++;
}

ElementType element_at(List* L, int i) {
    return L->data[i-1];
}

int count_list(List* L) {
    return L->size;
}

int contains(List L, int x){
	int i;
	for(i = 1; i <= L.size; i++){
		if(element_at(&L, i) == x) return 1;
	}
	return 0;
}

List neighbors(Graph *pG, int u){
	List L;
	make_null(&L);
	int e, v;
	for(e = 1; e <= pG->m; e++){
		if(pG->A[u][e] == 1){
			for(v = 1; v <= pG->n; v++){
				if(v == u) continue;
				if(pG->A[v][e] == 1 && !contains(L, v)){
					push_back(&L, v);
					break;
				}
			}
		}
	}
	return L;
}


int main(){
	
	return 0;
}

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
int N, M, S;

typedef struct vertex{
	int num;
	int flag;
	int print;
	int pre;
	struct vertex *next;
}v;

typedef struct edge {
	int a, b;
	int weight;
	int pass;
	struct edge *enext;
	v *v1;
	v *v2;
}e;

v **V;
e *H_edge;

void getvnode(v **p) {
	(*p) = (v *)malloc(sizeof(v));
	(*p)->next = NULL;
	(*p)->flag = 0;
	(*p)->print =0;
}

void getenode(e **p) {
	(*p) = (e *)malloc(sizeof(e));
	(*p)->v1 = NULL;
	(*p)->v2 = NULL;
	(*p)->enext = NULL;
	(*p)->pass = 0;
}

void addenode(int a,int b,int w) {
	e *q, *p;
	getenode(&q);
	q->a = a;
	q->b = b;
	q->weight = w;
	for (p = H_edge;p->enext != NULL;p = p->enext);
	p->enext = q;
}

int *A;
void graph() {
	e *p, *q = NULL;
	int i = S, j, flag = 0, k, next_num, F, min;
	V[S - 1]->print = 0;
	V[S - 1]->flag = 1;
	A[S - 1] = 1;
	while (1) {
		flag = 0;F = 0;min = 1000;
		for (p = H_edge->enext;p != NULL;p = p->enext) {
			if (p->pass == 1)
				continue;
			if (p->a == i || p->b == i) {
				if (p->a == i) {
					j = p->b;
					k = (V[i - 1]->print) + (p->weight);
				}
				else {
					j = p->a;
					k = (V[i - 1]->print) + (p->weight);
				}
				if (V[j - 1]->flag == 1) {
					continue;
				}
				if ((V[j-1]->print==0)||(V[j - 1]->print > k)) {
					V[j - 1]->print = k;
					V[j - 1]->pre = i;
					p->pass = 1;
					if (min > k) {
						min = k;
						flag = 1;
						next_num = j;
						q = p;
					}
				}
				
			}
		}
		
		if (flag == 1) {
			for (F = 0;F < N;F++) {
				if (V[F]->flag == 0) {
					if (min > V[F]->print && V[F]->print != 0) {
						min = V[F]->print;
						next_num = F + 1;
						flag = 1;
					}
				}
			}
			V[next_num- 1]->flag = 1;
			i = next_num;
		}
		else if (flag == 0) {
			min = 1000;
			for (F = 0;F < N;F++) {
				if (V[F]->flag == 0) {
					if (min > V[F]->print && V[F]->print!=0) {
						min = V[F]->print;
						i = F+1;j = V[F]->pre;
						flag = 1;
					}
				}
			}
			if (flag == 0)
				break;
			else {
				V[i-1]->flag = 1;
			}
		}
	}
}

void main() {
	int i;
	int n, m, l;
	v *p;
	scanf("%d %d %d", &N, &M, &S);
	V=(v **)malloc(sizeof(v *)*N);
	A = (int*)malloc(sizeof(int)*N);
	getenode(&H_edge);
	for (i = 0;i < N;i++) {
		getvnode(&V[i]);
		V[i]->num = i + 1;
		A[i] = -1;
	}
	for (i = 0;i < M;i++) {
		scanf("%d %d %d",&n,&m,&l);
		addenode(n, m, l);
	}
	graph();
	for (i = 0;i < N;i++) {
		if (i == S - 1)
			continue;
		if (V[i]->print == 0)
			continue;
		printf("%d %d\n", V[i]->num, V[i]->print);
	}
}

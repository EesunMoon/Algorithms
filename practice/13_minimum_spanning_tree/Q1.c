#pragma warning(disable:4996)
#define MAX 2147483647
#include<stdio.h>
#include<stdlib.h>
//prim_jarnik 하려면 visit 배열 하나 만들고
//거기서 방문하지 않은 정점에서 거리를 바꿔줘야함

typedef struct node {
	struct node *next;
	int elem;
	int weight;
}node;

node *getnode() {
	node *p = NULL;
	p = (node *)malloc(sizeof(node));
	p->next = NULL;
	return p;
}

typedef struct vertex {
	node *arr;
	int elem;
	int distance;
}vertex;

vertex *getvertex(int i) {
	vertex *p = NULL;
	p = (vertex *)malloc(sizeof(vertex));
	p->arr = getnode();
	p->elem = i;
	p->distance = MAX;
	return p;
}

void make_graph(vertex *u, vertex *v, int w) {
	node *tmp = u->arr->next, *tmp_prev = u->arr;
	node *q = getnode();
	q->elem = v->elem;
	q->weight = w;
	while (tmp != NULL&&tmp->elem < v->elem) {
		tmp = tmp->next;
		tmp_prev = tmp_prev->next;
	}
	tmp_prev->next = q;
	q->next = tmp;
}

void print_graph(vertex **p, int n) {
	node *tmp = p[0]->arr->next;
	for (int i = 0; i < n; i++) {
		tmp = p[i]->arr->next;
		while (tmp != NULL) {
			printf("e %d w %d //", tmp->elem, tmp->weight);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

int min_vertex(int *visit, int n, vertex **p) {
	int *tmp = NULL;
	int a = 0;
	tmp = (int *)malloc(sizeof(int)*n);
	int min;
	for (int i = 1; i <= n; i++) {
		if (visit[i] == 0) {
			tmp[a++] = i;
		}
	}
	int k;
	min = tmp[0] - 1;
	for (int i = 1; i < a; i++) {
		k = tmp[i] - 1;
		if (p[k]->distance < p[min]->distance) {
			min = k;
		}
	}
	return min;// distance가 가장 작은 정점의 index 반환
}

void prim(vertex **p, int n) {
	int *visit = NULL;
	int cnt = 0;
	int u;
	node *e;
	visit = (int *)malloc(sizeof(int)*(n + 1));
	for (int i = 0; i <= n; i++) {
		visit[i] = 0;
	}
	p[0]->distance = 0;
	while (cnt < n) {
		u = min_vertex(visit, n, p);
		visit[u + 1] = 1;
		printf(" %d", u + 1);
		cnt++;
		for (node *e = p[u]->arr->next; e != NULL; e = e->next) {
			if (visit[e->elem] == 0 && p[e->elem - 1]->distance > e->weight) {
				p[e->elem - 1]->distance = e->weight;
			}
		}
	}
}

int main() {
	int n, m, u, v, w;
	scanf("%d %d", &n, &m);
	vertex **p = NULL;
	p = (vertex **)malloc(sizeof(vertex)*n);
	for (int i = 0; i < n; i++) {
		p[i] = getvertex(i + 1);
	}
	for (int i = 0; i < m; i++) {// 간선받기
		scanf("%d %d %d", &u, &v, &w);
		make_graph(p[u - 1], p[v - 1], w);
		if (u != v) {
			make_graph(p[v - 1], p[u - 1], w);
		}
	}
	prim(p, n);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += p[i]->distance;
	}
	printf("\n%d", sum);
}

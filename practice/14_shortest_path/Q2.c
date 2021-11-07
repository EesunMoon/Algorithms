#pragma warning(disable:4996)
#define MAX 2147483647
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int u, v, weight;
	struct  node *next;
}node;

node *getnode() {
	node *p = NULL;
	p = (node *)malloc(sizeof(node));
	p->next = NULL;
	return p;
}

void make_graph(node *p, int u, int v, int w) {
	node *q = getnode();
	node *tmp = p;
	q->u = u;
	q->v = v;
	q->weight = w;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = q;
}

void bellman(node *p, int n, int m, int s) {
	node *tmp;
	int *dist = NULL;
	dist = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		dist[i] = MAX;
	}
	dist[s] = 0;
	for (int i = 0; i < n; i++) {
		tmp = p->next;
		while (tmp != NULL) {
			if (dist[tmp->u - 1] != MAX) {
				if (dist[tmp->v - 1] > dist[tmp->u - 1] + tmp->weight) {
					dist[tmp->v - 1] = dist[tmp->u - 1] + tmp->weight;
				}
			}
			tmp = tmp->next;
		}
	}
	for (int i = 0; i < n; i++) {
		if (i != s && dist[i] != MAX) {
			printf("%d %d\n", i + 1, dist[i]);
		}
	}
}

void print_node(node *p) {
	node *tmp = p->next;
	while (tmp != NULL) {
		printf("%d %d %d\n", tmp->u, tmp->v, tmp->weight);
		tmp = tmp->next;
	}
	printf("\n");
}

int main() {
	int n, m, w, u, v, s;
	node *p = getnode();
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		make_graph(p, u, v, w);
	}
	bellman(p, n, m, s - 1);
}

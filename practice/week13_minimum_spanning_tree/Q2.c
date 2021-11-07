#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	struct node *next;
	int u, v;
	int weight;
}node;

node *getnode() {
	node *p = NULL;
	p = (node *)malloc(sizeof(node));
	p->next = 0;
	return p;
}

void make_graph(node *p, int u, int v, int w) {
	node *tmp = p->next, *tmp_prev = p;
	node *q = getnode();
	q->u = u;
	q->v = v;
	q->weight = w;
	while (tmp != NULL&&tmp->weight<w) {
		tmp = tmp->next;
		tmp_prev = tmp_prev->next;
	}
	tmp_prev->next = q;
	q->next = tmp;
}

void print_list(node *p) {
	node *tmp = p->next;
	while (tmp != NULL) {
		printf("%d %d %d\n", tmp->u, tmp->v, tmp->weight);
		tmp = tmp->next;
	}
	printf("\n");
}

void change_setnum(int *p, int n, int ori, int x) {
	for (int i = 1; i <= n; i++) {
		if (p[i] == ori) {
			p[i] = x;
		}
	}
}

void kruskal(node *p, int n, int m) {
	node *tmp;
	node **rmp = NULL;
	rmp = (node **)malloc(sizeof(node*)*n);
	int *q = NULL;
	q = (int *)malloc(sizeof(int)*(n + 1));
	for (int i = 0; i <= n; i++) {
		q[i] = i;
	}
	int a = 0;
	tmp = p->next;
	while (tmp != NULL) {
		if (q[tmp->u] != q[tmp->v]) {
			if (q[tmp->u] < q[tmp->v]) {
				change_setnum(q, n, q[tmp->v], q[tmp->u]);
				rmp[a++] = tmp;
			}
			else {
				change_setnum(q, n, q[tmp->v], q[tmp->u]);
				rmp[a++] = tmp;
			}
		}
		tmp = tmp->next;
	}
	int sum = 0;
	for (int i = 0; i < a; i++) {
		printf(" %d", rmp[i]->weight);
		sum += rmp[i]->weight;
	}
	printf("\n%d", sum);
}

int main() {
	int n, m, w, u, v;
	scanf("%d %d", &n, &m);
	node *list = getnode();

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		make_graph(list, u, v, w);
	}
	kruskal(list, n, m);
}

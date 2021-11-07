#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct Edge {
	int start, end;
	int flag;
}Edge;

typedef struct Node {
	struct Node *next;
	Edge *pedge;
}Node;

typedef struct Vertex {
	char name;
	int in_n, out_n;
	Node *in_head, *out_head;

}Vertex;

typedef struct Graph {
	Vertex *vertex;
	Edge *edge;

	int v_n, e_n;
}Graph;

typedef struct Queue {
	int start, end;
	char *arr;
}Queue;

Node* getNode() {
	Node *new = (Node *)malloc(sizeof(Node));
	new->next = NULL;
	new->pedge = NULL;
	return new;
}

int search_ver_index(Graph g, char name) {

	int i;

	for (i = 0; i < g.v_n; i++) {
		if (g.vertex[i].name == name) {
			return i;
		}
	}

}

void enqueue(Queue *q, char data) {

	q->arr[q->end] = data;

	(q->end)++;
}

char deQueue(Queue *q) {
	char data = q->arr[q->start];
	(q->start)++;
	return data;
}

void printQueue(Queue q) {
	int i;

	for (i = 0; i < q.start; i++) {
		printf("%c ", q.arr[i]);
	}

}

void topologicalSort(Graph *g, Queue *q) {
	int i, index, index2;
	Node *now;

	q->arr = (char *)malloc(sizeof(char)*(g->v_n));

	for (i = 0; i < (g->v_n); i++) {

		if (g->vertex[i].in_n == 0) {

			enqueue(q, g->vertex[i].name);

		}

	}



	while (1) {

		if (q->start == q->end) {
			break;
		}

		index = search_ver_index(*g, deQueue(q));


		now = g->vertex[index].out_head;

		while (1) {

			now = now->next;

			if (now == NULL) {
				break;
			}

			index2 = search_ver_index(*g, now->pedge->end);

			(g->vertex[index2].in_n)--;

			if (g->vertex[index2].in_n == 0) {

				enqueue(q, g->vertex[index2].name);

			}

		}
	}

	if (q->start == g->v_n) {
		printQueue(*q);
	}
	else {
		printf("0");
	}
}

void createGraph(Graph *g, Queue *q) {
	int n, m;
	int i, index1, index2;
	char data, a, b;
	Node *New1, *New2, *now;

	scanf("%d", &n);
	q->arr = (char *)malloc(sizeof(char)*n);
	q->start = 0;
	q->end = 0;
	g->v_n = n;
	g->vertex = (Vertex *)malloc(sizeof(Vertex)*n);

	for (i = 0; i < n; i++) {
		getchar();

		scanf("%c", &data);

		g->vertex[i].name = data;

		g->vertex[i].in_head = getNode();

		g->vertex[i].out_head = getNode();

		g->vertex[i].in_n = 0;

		g->vertex[i].out_n = 0;

	}

	scanf("%d", &m);

	g->e_n = m;

	g->edge = (Edge *)malloc(sizeof(Edge)*m);

	for (i = 0; i < m; i++) {
		getchar();

		scanf("%c %c", &a, &b);

		g->edge[i].start = a;

		g->edge[i].end = b;

		g->edge[i].flag = 0;

		index1 = search_ver_index(*g, a);

		New1 = getNode();

		New1->pedge = &(g->edge[i]);

		New1->next = g->vertex[index1].out_head->next;

		g->vertex[index1].out_head->next = New1;

		(g->vertex[index1].out_n)++;



		New2 = getNode();

		New2->pedge = &(g->edge[i]);

		index2 = search_ver_index(*g, b);

		New2->next = g->vertex[index2].in_head->next;

		g->vertex[index2].in_head->next = New2;

		(g->vertex[index2].in_n)++;
	}
}


int main() {
	Graph g;
	Queue q;

	createGraph(&g, &q);

	topologicalSort(&g, &q);

	return 0;
}

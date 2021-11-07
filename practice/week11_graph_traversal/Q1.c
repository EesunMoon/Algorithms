#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct Node {
	int edgeNum, point;
	struct Node *next;
}Node;

typedef struct Vertex {
	int name, fresh;
	Node *in;
}Vertex;

typedef struct Edge {
	int start, end;
	int fresh;
}Edge;

typedef struct Graph {
	Vertex *vertex;
	Edge *edge;
}Graph;

void init_vertex(Graph *g, int key) {
	g->vertex[key - 1].name = key;
	g->vertex[key - 1].fresh = 1;
	g->vertex[key - 1].in = (Node *)malloc(sizeof(Node));
	g->vertex[key - 1].in->point = -1;
	g->vertex[key - 1].in->edgeNum = -1;
	g->vertex[key - 1].in->next = NULL;
}

int find_edge_num(Graph *g, int pt1, int pt2, int M) {
	int i;

	for (i = 0; i<M; i++) {
		if (g->edge[i].start == pt1 && g->edge[i].end == pt2) {
			return i;
		}
	}
}

void init_list(Graph *g, int pt1, int pt2, int M) {
	Node *node1, *node2, *insert1, *insert2;
	int edgeNum;

	edgeNum = find_edge_num(g, pt1, pt2, M);

	node1 = g->vertex[pt1 - 1].in;

	insert1 = (Node *)malloc(sizeof(Node));
	insert1->edgeNum = edgeNum;
	insert1->point = pt2;
	insert1->next = NULL;

	while (node1->next != NULL && node1->next->point < pt2) {
		node1 = node1->next;
	}

	insert1->next = node1->next;
	node1->next = insert1;

	if (pt1 != pt2) {
		node2 = g->vertex[pt2 - 1].in;

		insert2 = (Node *)malloc(sizeof(Node));
		insert2->edgeNum = edgeNum;
		insert2->point = pt1;
		insert2->next = NULL;

		while (node2->next != NULL && node2->next->point < pt1) {
			node2 = node2->next;
		}

		insert2->next = node2->next;
		node2->next = insert2;
	}
}

void rDFS(Graph *g, int index) {
	Node *now;
	printf("%d\n", g->vertex[index].name);
	g->vertex[index].fresh = 0;

	now = g->vertex[index].in->next;

	while (now != NULL) {
		if (g->edge[now->edgeNum].fresh == 1) {
			g->edge[now->edgeNum].fresh = 0;
			if (g->vertex[now->point - 1].fresh == 1) {
				rDFS(g, now->point - 1);
			}
		}
		now = now->next;
	}
}

void DFS(Graph *g, int S, int N) {
	int i;

	for (i = 0; i<N; i++) {
		if (g->vertex[(i + S) % N].fresh == 1) {
			rDFS(g, (i + S) % N);
		}
	}
}

int main() {
	int N, M, S;
	int i, j, a, b, pt1, pt2;
	Graph *g = (Graph *)malloc(sizeof(Graph));

	scanf("%d %d %d", &N, &M, &S);
	g->edge = (Edge *)malloc(sizeof(Edge)*M);
	g->vertex = (Vertex *)malloc(sizeof(Vertex)*N);

	for (i = 0; i<N; i++) {
		init_vertex(g, i + 1);
	}

	for (i = 0; i<M; i++) {
		scanf("%d %d", &a, &b);
		if (a<b) {
			pt1 = a;
			pt2 = b;
		}
		else {
			pt1 = b;
			pt2 = a;
		}
		g->edge[i].fresh = 1;
		g->edge[i].start = pt1;
		g->edge[i].end = pt2;

		init_list(g, pt1, pt2, M);
	}

	DFS(g, S - 1, N);

	return 0;
}

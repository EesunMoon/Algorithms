#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct Vertex {
	int name;
}Vertex;

typedef struct Edge {
	int weight;
	int start, end;
}Edge;

typedef struct Graph {
	Vertex *vertex;
	Edge *edge;
	int **matrix;
}Graph;

int findEdgeNum(Graph *g, int a, int b) {
	int i;
	for (i = 0; i<21; i++) {
		if (g->edge[i].start == a && g->edge[i].end == b) {
			return i;
		}
	}
}

void initMatrix(Graph *g, int a, int b, int weight) {
	int n1, n2, edgeNum;

	if (a<b) {
		n1 = a;
		n2 = b;
	}
	else {
		n1 = b;
		n2 = a;
	}

	edgeNum = findEdgeNum(g, n1, n2);
	g->edge[edgeNum].weight = weight;
	g->matrix[a - 1][b - 1] = edgeNum;
	g->matrix[b - 1][a - 1] = edgeNum;

}

void search(Graph *g, int n) {
	int edgeNum, i;

	if (n>6 || n <= 0) {
		printf("-1");
		return;
	}

	for (i = 0; i<6; i++) {
		edgeNum = g->matrix[n - 1][i];

		if (edgeNum == -1) continue;
		if (g->edge[edgeNum].start == n) {
			printf("%d %d ", g->edge[edgeNum].end, g->edge[edgeNum].weight);
		}
		else if (g->edge[edgeNum].end == n) {
			printf("%d %d ", g->edge[edgeNum].start, g->edge[edgeNum].weight);
		}
	}
}

void modify(Graph *g, int a, int b, int weight) {
	int edgeNum, n1, n2;

	if ((a>6 || a <= 0) || (b>6 || b <= 0)) {
		printf("-1\n");
		return;
	}


	if (a<b) {
		n1 = a;
		n2 = b;
	}
	else {
		n1 = b;
		n2 = a;
	}

	edgeNum = findEdgeNum(g, n1, n2);
	if (weight == 0) {
		weight = -1;
		g->matrix[a - 1][b - 1] = -1;
		g->matrix[b - 1][a - 1] = -1;
	}
	else {
		g->matrix[a - 1][b - 1] = edgeNum;
		g->matrix[b - 1][a - 1] = edgeNum;
	}
	g->edge[edgeNum].weight = weight;


}


int main() {
	int i, j, tmp = 0, n1, n2, weight;
	char operation;
	Graph *g = (Graph *)malloc(sizeof(Graph));

	g->vertex = (Vertex *)malloc(sizeof(Vertex) * 6);
	g->edge = (Edge *)malloc(sizeof(Edge) * 21);

	g->matrix = (int **)malloc(sizeof(int *) * 21); //matrix 동적 할당

	for (i = 0; i<6; i++) {
		g->matrix[i] = (int *)malloc(sizeof(int) * 6);
		for (j = 0; j<6; j++) {
			g->matrix[i][j] = -1;
		}
	}

	//vertex 초기값 설정
	for (i = 0; i<6; i++) {
		g->vertex[i].name = i + 1;
	}

	//edge 초기 설정
	for (i = 0; i<6; i++) {
		for (j = i; j<6; j++) {
			g->edge[tmp].start = i + 1;
			g->edge[tmp].end = j + 1;
			tmp++;
		}
	}

	initMatrix(g, 1, 2, 1);
	initMatrix(g, 1, 3, 1);
	initMatrix(g, 1, 4, 1);
	initMatrix(g, 1, 6, 2);
	initMatrix(g, 2, 3, 1);
	initMatrix(g, 3, 5, 4);
	initMatrix(g, 5, 5, 4);
	initMatrix(g, 5, 6, 3);

	while (1) {
		scanf("%c", &operation);

		if (operation == 'a') {
			scanf("%d", &n1);
			getchar();
			search(g, n1);
			printf("\n");
		}
		else if (operation == 'm') {
			scanf("%d %d %d", &n1, &n2, &weight);
			getchar();

			modify(g, n1, n2, weight);
		}
		else if (operation == 'q') {
			return 0;
		}
	}
}

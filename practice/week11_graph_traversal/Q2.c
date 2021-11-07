#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAX 1001

int metrix[MAX][MAX];
int visited[MAX * MAX];

void BFS(int v, int N) {
	int front = -1, rear = -1;
	int queue[MAX * MAX] = { 0 };

	// 첫번째 추가
	rear++;
	queue[rear] = v;

	// 방문 표시
	visited[v] = 1;

	// 일단 출력
	printf("%d ", v);

	// 너비 우선 탐색
	while (front < rear) {
		// 큐에서 꺼내기
		front++;
		int nextV = queue[front];

		// 인접 정점 체크
		for (int d = 1; d <= N; d++) {
			// 방문하지 않았고, 이동이 가능하다면
			if (!visited[d] && metrix[nextV][d]) {
				rear++;
				visited[d] = 1;
				queue[rear] = d;

				printf("%d ", d);
			}
		}
	}
}

void init(int N) {
	printf("\n");
	for (int i = 1; i <= N; i++) {
		visited[i] = 0;
	}
}

int main(void) {
	int N = 0;
	int M = 0;
	int V = 0;

	scanf("%d %d %d", &N, &M, &V);

	for (int i = 0; i < M; i++) {
		int s = 0, d = 0;

		scanf("%d %d", &s, &d);

		metrix[s][d] = 1;
		metrix[d][s] = 1;
	}

	init(N);

	BFS(V, N);

	return 0;
}

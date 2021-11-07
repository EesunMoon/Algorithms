#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int H[101], n; // 힙과 힙의 크기 전역변수로 선언

void downHeap(int N)
{
	int tmp, i = N, j = i * 2; //i는 처음 것, j는 루트의 자식노드
	while (j <= n)
	{
		if ((j < n) && (H[j + 1] > H[j]))
			j++; //자식노드 중에 더 큰 인덱스를 j에다가 넣음

		if (H[i] < H[j]) //부모와 자식을 비교해서 더 큰 것으로 바꾸기
		{
			tmp = H[i];
			H[i] = H[j];
			H[j] = tmp; //swap
			i = j;
			j = 2 * j;
		}
		else break;
	}
}

void printHeap() //인쇄
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}


void rBuildHeap(int i)
{
	if (i > n) return;
	rBuildHeap(2 * i); //좌 subtree 힙 생성
	rBuildHeap(2 * i + 1); //우 subtree 힙 생성
	downHeap(i); //합친 힙 생성
}

void buildHeap()
{
	for (int i = (int)(n / 2); i >= 1; i--)
		downHeap(i);
}

void main() {
	int x;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		H[i] = x;
	} //초기 배열에 입력값 저장

    rBuildHeap(1);
//	buildHeap();
	printHeap();

}

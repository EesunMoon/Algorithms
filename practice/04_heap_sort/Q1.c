#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int H[101], n = 0; // 힙과 힙의 크기 전역변수로 선언

void upHeap(int N)
{
	int i = N, tmp = H[i];
	while (i > 1 && tmp > H[i / 2])
	{
		H[i] = H[i / 2];
		i = i / 2;
	}
	H[i] = tmp;
}

void insertItem(int key, int k) //삽입
{
	H[k] = key; //leaf에 key추가
	upHeap(k);
}

void downHeap(int N, int size)
{
	int tmp, i = N, j = i * 2; //i는 처음 것, j는 루트의 자식노드
	while (j <= size)
	{
		if ((j < size) && (H[j + 1] > H[j]))
			j++; //자식노드 중에 더 큰 인덱스를 j에다가 넣음

		if (H[i] < H[j])
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

void rBuildHeap(int i)
{
	if (i > n) return;
	rBuildHeap(2 * i); //좌 subtree 힙 생성
	rBuildHeap(2 * i + 1); //우 subtree 힙 생성
	downHeap(i, n); //합친 힙 생성
}
void buildHeap()
{
	for (int i = (int)(n / 2); i >= 1; i--)
		downHeap(i, n);
}

void inPlaceHeapSort()
{
	int tmp;
	for (int i = n; i >= 2; i--)
	{
		tmp = H[1];
		H[1] = H[i];
		H[i] = tmp; //swap
		downHeap(1, i-1);
	}
}

void printArray()
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}


void main() {
	int x;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		insertItem(x, i); // 삽입식 힙 이용
		//H[i] = x; buildHeap(); //상향식 힙 이용
	} //1단계 : 힙생성 단계 - max-heap 완성

	inPlaceHeapSort(); //2단계 : root<->last바꿔서 정렬

	printArray();
}

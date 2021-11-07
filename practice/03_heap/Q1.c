#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int H[101], n=0; // 힙과 힙의 크기 전역변수로 선언

void upHeap(int N)
{
	int i=N, tmp=H[i];
	while (i > 1 && tmp > H[i / 2])
	{
		H[i] = H[i / 2];
		i = i / 2;
	}
	H[i] = tmp;
}

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

void insertItem(int key) //삽입
{
	n++;
	H[n] = key; //leaf에 key추가
	upHeap(n);
}

int removeMax()  //삭제
{
	int x = H[1];
	H[1] = H[n]; //루트와 맨 아래에 있는 원소와 바꾸기
	n--;
	downHeap(1);
	return x;
}

void printHeap() //인쇄
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}


void main() {
	char cm;
	int x;

	while (1)
	{
		scanf("%c", &cm); getchar(); //명령어 입력

		if (cm == 'i') //삽입
		{
			scanf("%d", &x); getchar();
			insertItem(x);
			printf("0\n");
		}
		else if (cm == 'd')	printf("%d\n", removeMax()); //삭제
		else if (cm == 'p') printHeap(); //인쇄
		else if (cm == 'q')	break; //종료
	}
}

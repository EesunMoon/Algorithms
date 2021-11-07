#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> //난수를 구하기 위해

void swap(int Q[], int a, int b)
{
	int tmp;
	tmp = Q[a];
	Q[a] = Q[b];
	Q[b] = tmp;
}

int median(int Q[], int a, int b, int c) 
{
	int max = Q[a], min = Q[a];
	if (max < Q[b]) max = Q[b];
	if (max < Q[c]) max = Q[c];
	if (min > Q[b]) min = Q[b];
	if (min > Q[c]) min = Q[c];
	if (max == Q[a]) {
		if (min == Q[b]) return c;
		else return b;
	}
	else if (max == Q[b]) {
		if (min == Q[a]) return c;
		else return c;
	}
	else {
		if (min == Q[a]) return b;
		else return a;
	}
}

int find_pivot_index(int Q[], int l, int r)
{
	int pivot_index, p1, p2, p3;
	srand(time(NULL)); //현재의 초 수로 기준점 초기화
	p1 = rand() % (r - l) + l; 
	p2 = rand() % (r - l) + l;
	p3 = rand() % (r - l) + l; //l번째 index~r번째 index 사이의 무작위 index 지정

	pivot_index = median(Q, p1, p2, p3); //중간값 구하기
	return pivot_index;
}

int inPlacePartition(int Q[], int l, int r, int k)
{
	int i, j, p;
	p = Q[k];
	swap(Q, k, r); //pivot을 마지막 원소로 옮기기
	i = l; j = r - 1;

	//pivot보다 크거나 같으면 pivot의 오른쪽에, 작으면 pivot의 왼쪽에 정렬
	while (i <= j)
	{
		while (i <= j && Q[i] <= p) i++;
		while (j >= i && Q[j] >= p) j--; 
		if (i < j) swap(Q, i, j);
	}
	swap(Q, i, r); //i와 j가 역행하면 pivot바꾸기

	return i;
}

void inPlaceQuickSort(int Q[], int l, int r)
{
	int pivot, a, b, tmp;
	
	if (l >= r) return; //l이 r을 역행하면 종료

	pivot = find_pivot_index(Q, l, r); //피봇 인덱스

	b = inPlacePartition(Q, l, r, pivot); //같은 원소 인덱스 중 가장 뒤에 있는 인덱스

	tmp = b; //a를 찾기 위해 tmp사용
	while (1)
	{
		if (Q[tmp] != Q[b]) {
			a = tmp + 1;
			break;
		}
		tmp--;
	}

	inPlaceQuickSort(Q, l, a - 1);
	inPlaceQuickSort(Q, b + 1, r);
}

void main() 
{
	int N, *Q, x, i, a, b;
	scanf("%d", &N); //배열 크기 입력
	Q = (int*)malloc(sizeof(int)*N); //크기N인 배열 동적할당
	for (i = 0; i < N; i++)
	{
		scanf("%d", &x);
		Q[i] = x;
	} //입력받은 원소 배열에 저장

	inPlaceQuickSort(Q, 0, N - 1);

	for (i = 0; i < N; i++)
		printf(" %d", Q[i]); //정렬 결과 출력
}

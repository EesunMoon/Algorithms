#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <time.h> //time() 함수를 쓰기 위한 헤더
//#include <Windows.h> //cpu시간 측정을 위한 헤더

int biggest(int k, int *arr)
{
	int pos = k, big = *(arr + k); //pos:가장 큰 원소의 위치
	for (int i = k - 1; i >= 0; i--)
	{
		if (big < *(arr + i))
		{
			big = *(arr + i);
			pos = i;
		}
	}

	return pos;
}

void swap(int pos, int k, int *arr)
{
	int tmp;
	tmp = *(arr + pos);
	*(arr + pos) = *(arr + k);
	*(arr + k) = tmp;
} //교환 함수

void Selection_Sort(int *arr, int n) // 인자 : 배열, 배열크기
{
	int pos; //가장 큰 원소의 위치
	for (int i = n - 1; i >= 0; i--)
	{
		pos = biggest(i, arr); //가장 큰 원소 찾기

		if (pos != i) 
			swap(pos, i, arr);
	}
}


int main() {
	int n, i, x, *arr;
	scanf("%d", &n); //크기 입력
	arr = (int *)malloc(sizeof(int)*n); //배열 동적할당

	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		*(arr+i) = x; 
	} //입력된 값 저장

	Selection_Sort(arr, n); //선택 정렬 시작

	for (i = 0; i < n; i++)
		printf(" %d", *(arr + i)); //정렬 결과 출력
	free(arr); //해제

	return 0;
}

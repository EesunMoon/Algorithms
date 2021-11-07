#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <time.h> //time() 함수를 쓰기 위한 헤더
//#include <Windows.h> //cpu시간 측정을 위한 헤더

void Insertion_Sort(int *arr, int n)
{
	int tmp, k; 
	for (int i = 1; i < n; i++) 
	{
		tmp = *(arr + i); //i번째 배열값 저장
		k = i - 1; //i번째 전부터 0까지 비교
		while ((tmp < *(arr + k)) && (k >= 0)) //i-1부터 0까지는 이미 정렬이 되어 있는 형태
		{
			*(arr + k + 1) = *(arr + k); //정렬이 안된 위치 찾기 위해 옮겨줌
			k--;
		}
		*(arr + k + 1) = tmp; //그 위치에 tmp 저장
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

	Insertion_Sort(arr, n); //삽입 정렬

	for (i = 0; i < n; i++)
		printf(" %d", *(arr + i)); //정렬 결과 출력
	free(arr); //해제

	return 0;
}

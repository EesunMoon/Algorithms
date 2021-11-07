#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int binary_search(int *d, int k, int l, int r)
{
	int mid;
	int index = -1;
	while (l <= r)
	{
		mid = (l + r) / 2; //중간값
		if (d[mid] == k) return mid;
		else if (d[mid] < k)  //중간값보다 key가 큰 경우
			l = mid + 1;
		else if (d[mid] > k) { //중간값보다 key가 작은 경우
			//사전의 키 x 중 가장 작은 값의 위치를 출력하기 위해
			if (index == -1) index = mid;
			else if (index > mid) index = mid; 
			r = mid - 1;
		}
			
	}
	return index;
}


void main()
{
	int N, k, *d, i, x;
	scanf("%d %d", &N, &k); //배열 크기, 키 입력
	d = (int*)malloc(sizeof(int)*N);
	for (i = 0; i < N; i++)
		scanf("%d", &d[i]); //배열 원소 입력
	x = binary_search(d, k, 0, N - 1);
	if (x != -1)
		printf(" %d", x);
	else
		printf(" %d", N);
}

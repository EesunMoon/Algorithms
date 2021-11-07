#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int index = -1;

int binary_search(int *d, int k, int l, int r)
{
	int mid = (l + r) / 2;
	if (l > r) return index; //k가 존재하지 않는 경우 k보다 작으면서 가장 큰 수의 위치 출력
	if (d[mid] == k) return mid;
	else if (d[mid] < k) { //찾고자 하는 k가 중간값보다 큰 경우
		//k보다 작으면서 가장 큰 수의 위치를 출력하기 위해
		if (index==-1) index = mid;
		else if (index < mid) index = mid;
		binary_search(d, k, mid + 1, r); 
	}
	else if (d[mid] > k)	//찾고자 하는 k가 중간값보다 작은 경우
		binary_search(d, k, l, mid - 1);	
}


void main() 
{
	int N, k,*d, i, x;
	scanf("%d %d", &N, &k); //배열 크기, 키 입력
	d = (int*)malloc(sizeof(int)*N);
	for (i = 0; i < N; i++)
		scanf("%d", &d[i]); //배열 원소 입력
	x = binary_search(d, k, 0, N - 1);
	printf(" %d", x);
}

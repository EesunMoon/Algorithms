#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int HashFunc(int x, int M)
{
	return x%M;
} // 해시 함수

int HashBucket(int M, int y, int i)
{
	return (y + i) % M;
} // 다음 해시 함수

void insert(int x, int *H, int M)
{
	int y=HashFunc(x, M), i = 0, j, index;
	while (i < M)
	{
		index = HashBucket(M, y, i);
		if (H[index] == 0)
		{
			H[index] = x;
			for (j = 0; j < i; j++)
				printf("C");
			printf("%d\n", index);
			return;
		}
		else i++;
	}
} // 추가

void search(int x, int *H, int M)
{
	int y = HashFunc(x, M), i=0, index;
	while (i < M)
	{
		index = HashBucket(M, y, i);
		if (H[index] == 0)
		{
			printf("-1\n");
			return;
		}
		else if (H[index] == x)
		{
			printf("%d %d\n", index, H[index]);
			return;
		}
		else i++;
	}
	printf("-1\n");
} // 탐색

int main()
{
	int *H, M, N, x, i;
	char anl;

	scanf("%d %d", &M, &N);
	H = (int*)malloc(sizeof(int)*M);

	for (i = 0; i < M; i++)
		*(H + i) = 0;

	while (1)
	{
		scanf("%c", &anl);
		if (anl == 'i')
		{
			scanf("%d", &x);	getchar();
			insert(x, H, M);
		}
		else if (anl == 's')
		{
			scanf("%d", &x);	getchar();
			search(x, H, M);
		}

		else if (anl == 'e')
			break;
	}
	free(H);
}

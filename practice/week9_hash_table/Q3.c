#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int HashFunc1(int x, int M)
{
	return x%M;
}

int HashFunc2(int x, int q)
{
	return q - (x%q);
}

int HashBucket(int M, int y, int i, int x, int q)
{
	return (y + i*HashFunc2(x, q) % M) % M;
}

void insert(int x, int *H, int M, int q)
{
	int y = HashFunc1(x, M), i = 0, j, index;
	while (i < M)
	{
		index = HashBucket(M, y, i, x, q);
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

void search(int x, int *H, int M, int q)
{
	int y = HashFunc1(x, M), i = 0, index;
	while (i < M)
	{
		index = HashBucket(M, y, i, x, q);
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

void print(int *H, int M)
{
	for (int i = 0; i < M; i++)
		printf(" %d", H[i]);
	printf("\n");
}

int main()
{
	int *H, M, N, x, i, q;
	char anl;

	scanf("%d %d %d", &M, &N, &q);
	H = (int*)malloc(sizeof(int)*M);

	for (i = 0; i < M; i++)
		*(H + i) = 0;

	while (1)
	{
		scanf("%c", &anl);
		if (anl == 'i')
		{
			scanf("%d", &x);	getchar();
			insert(x, H, M, q);
		}
		else if (anl == 's')
		{
			scanf("%d", &x);	getchar();
			search(x, H, M, q);
		}
		else if (anl == 'p')
			print(H, M);
		else if (anl == 'e')
		{
			print(H, M);
			break;
		}
	}
	free(H);
}

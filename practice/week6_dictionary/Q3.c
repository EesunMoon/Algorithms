#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
	int a, b, N;
	char hint;
	scanf("%d %d %d", &a, &b, &N); getchar();
	for (int i=0;i<N;i++) 
	{
		scanf("%c", &hint);

		if (a == b) break;
		if (hint == 'N') b = (a + b) / 2;
		else if (hint == 'Y') a = (a + b) / 2 + 1;
	}
	printf("%d", a);

}

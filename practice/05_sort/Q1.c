#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
}node;

void getNode(node **p)
{
	(*p) = (node*)malloc(sizeof(node));
	(*p)->next = NULL;
}

void addNode(node **H, int x)
{
	node *p = (*H); //p는 리스트를 이동하는 포인터
	node *k; getNode(&k); k->data = x; //새 노드 생성
	
	if ((*H) == NULL) //리스트가 비었을 때
		(*H) = k;
	else 
	{
		while (p->next != NULL) p = p->next;
		p->next = k;
	}
}

void mg_partition(node *H, node **L1, node **L2, int N)
{
	node *p = H;
	(*L1) = H; //L1은 H의 처음부터 담음
	for (int i = 0; i < (N / 2) - 1; i++)
		p = p->next; //H를 K-1번째까지 옮겨주기
	(*L2) = p->next; 
	p->next = NULL; //이 조건 없으면 끝맺음이 없어서 계속 무한루프 돌게 됨
}

node* merge(node **L1, node **L2)
{
	node *SH, *p; //SH는 정렬된 리스트의 헤더, p는 SH를 이어줌
	node *l1=*L1, *l2=*L2; 

	//헤더 결정
	if (l1->data <= l2->data)
	{
		SH = l1;
		l1 = l1->next;
		p = SH;
	}
	else
	{
		SH = l2;
		l2 = l2->next;
		p = SH;
	}

	//SH에 오름차순으로 정렬하기
	while ((l1 != NULL) && (l2 != NULL))
	{
		if (l1->data <= l2->data)
		{
			p->next = l1;
			l1 = l1->next;
			p = p->next;
		}
		else
		{
			p->next = l2;
			l2 = l2->next;
			p = p->next;
		}
	}

	while (l1 != NULL)
	{
		p->next = l1;
		p = l1; //p에 l1넣고 그 다음에 넣어지도록 옮겨주는 역할
		l1 = l1->next;
	}
	while (l2 != NULL)
	{
		p->next = l2;
		p = l2;
		l2 = l2->next;
	}

	return SH;
}


void mergeSort(node **H, int N)
{
	node *L1, *L2; //L1, L2는 H를 분할한 것의 주소를 담음
	node *p = (*H);

	if (N > 1) //리스트의 개수가 1개면 최소 단위이기 때문에 이 조건 꼭 써줘야 함
	{
		mg_partition(p, &L1, &L2, N); //리스트 분할

		if (N % 2 == 0) //N이 짝수인 경우
		{
			mergeSort(&L1, N / 2);
			mergeSort(&L2, N / 2);
		}
		else //N이 홀수인 경우
		{
			mergeSort(&L1, N / 2);
			mergeSort(&L2, (N / 2) + 1);
		}

		(*H) = merge(&L1, &L2);
	}
	
}

void main() {
	node *H=NULL; //헤더
	node *p;

	int N, x;
	scanf("%d", &N); //노드 개수 입력

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &x); //데이터 입력
		addNode(&H, x);
	}

	mergeSort(&H, N);

	p = H;
	while(p!=NULL)
	{
		printf(" %d", p->data);
		p = p->next;
	}
}

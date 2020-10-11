#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Node {
	char elem;
	struct Node *prev;
	struct Node *next;
}node; //연결리스트 노드 구조체 정의

void getNode(node **p) {
	(*p) = (node*)malloc(sizeof(node));
	(*p)->prev = NULL;
	(*p)->next = NULL;
} //노드 생성

int isValid(node *H, node *T) {
	node *p; p = H->next; int cnt = 0;
	while (p != T) {
		cnt++;
		p = p->next;
	}
	return cnt;
}

void add(node **H, node **T, int pos, char ch) {
	node *p = *H;
	node *q;

	if (isValid(*H, *T) + 1<pos)
		printf("invalid position\n");
	else {
		for (int i = 0; i < pos; i++)
			p = p->next;
		getNode(&q); q->elem = ch;

		q->prev = p->prev;	q->next = p;
		p->prev->next = q;	p->prev = q;
	}
}

void del(node **H, node **T, int pos) {
	node *tmp;
	node *p; p = *H;
	if (isValid(*H, *T) < pos)
		printf("invalid position\n");
	else {
		for (int i = 0; i < pos; i++)
			p = p->next;
		tmp = p;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(tmp);
	}
}

void get(node *H, node *T, int pos) {
	node *p = H;
	if (isValid(H, T) < pos)
		printf("invalid position\n");
	else {
		for (int i = 0; i < pos; i++)
			p = p->next;
		printf("%c\n", p->elem);
	}
}

void print(node *H, node *T) {
	node *p; p = H->next;
	while (p != T) {
		printf("%c", p->elem);
		p = p->next;
	}
	printf("\n");
}

int main() {
	node *H, *T; getNode(&H); getNode(&T); //헤더, 테일러
	H->next = T; H->prev = NULL;
	T->next = NULL; T->prev = H;

	int n, pos;
	char anl, ch;

	scanf("%d", &n); getchar(); //연산의 개수 입력

	for (int i = 0; i < n; i++) {
		scanf("%c", &anl); getchar(); //연산의 종류 입력

		if (anl == 'A') { //추가
			scanf("%d %c", &pos, &ch); getchar();
			add(&H, &T, pos, ch);
		}
		else if (anl == 'D') { //삭제
			scanf("%d", &pos); getchar();
			del(&H, &T, pos);
		}
		else if (anl == 'G') { //반환
			scanf("%d", &pos); getchar();
			get(H, T, pos);
		}
		else if (anl == 'P') //출력
			print(H, T);
	}

	return 0;
}
//분리연쇄법
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node *next;
}node ;
void getnode(node **p, int k) {
	(*p) = (node *)malloc(sizeof(node));
	(*p)->key = k;
	(*p)->next = NULL;
}

void addlink(node *H, node *p) {
	if (H->next == NULL)
		H->next = p;
	else {
		p->next = H->next;
		H->next = p;
	}
}
void insertitem(node **H, int k, int M) {
	int index = k%M;
	node *p; getnode(&p, k);
	
	addlink(H[index], p);
}
//item 추가 

void selectitem(node **H, int k, int M) {
	int index = k %M;
	if (H[index]->next == NULL) {
		printf("0\n");
		return;
	}
	node *tmp = H[index]->next;
	int cnt = 1;
	while (1) {
		if (tmp == NULL) {
			printf("0\n");
			return;
		}
		if (tmp->key == k) {
			printf("%d\n", cnt);
			return;
		}
		tmp = tmp->next;
		cnt++;
	}
}
//item 여부 확인 

void deletelink(node *tmp, node *before) {
	if (tmp->next == NULL)
		before->next = NULL;
	else
		before->next = tmp->next;
	free(tmp);
}
void deleteitem(node **H, int k, int M) {
	int index = k%M;
	if (H[index]->next == NULL) {
		printf("0\n");
		return;
	}
	node *tmp = H[index]->next;
	node *before = H[index];
	int cnt = 1;

	while (1) {
		if (tmp == NULL) {
			printf("0\n");
			return;
		}
		if (tmp->key == k) {
			printf("%d\n", cnt);
			deletelink(tmp, before);
			return;
		}
		tmp = tmp->next;
		before = before->next;
		cnt++;
	}
}
//item 삭제 

void printitem(node **H, int M) {
	for (int i = 0; i < M; i++) {
		if (H[i]->next != NULL) {
			node *tmp = H[i]->next;
			while (1) {
				if (tmp == NULL) break;
				printf(" %d", tmp->key);
				tmp = tmp->next;
			}
		}
	}
	printf("\n");
}
//출력함수 

void main() {
	node **H;
	int M, k;
	char order;

	scanf("%d", &M);
	getchar();
	H = (node **)malloc(sizeof(node)*M);
	for (int i = 0; i < M; i++)
		getnode(&H[i], i);
	
	while (1) {
		scanf("%c", &order);
		if (order == 'i') {
			scanf(" %d", &k); getchar();
			insertitem(H, k, M);
		}
		else if (order == 's') {
			scanf(" %d", &k); getchar();
			selectitem(H, k, M);
		}
		else if (order == 'd') {
			scanf(" %d", &k); getchar();
			deleteitem(H, k, M);
		}
		else if (order == 'p') {
			printitem(H, M);
		}
		else if (order == 'e')
			return;
	}

}

#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	struct Node* lchild;
	struct Node* parent;
	int key;
	struct Node* rchild;
}node;
void getnode(node **p) {
	(*p) = (node *)malloc(sizeof(node));
	(*p)->lchild = NULL;
	(*p)->rchild = NULL;
	(*p)->parent = NULL;
}
int isExternal(node *p) {
	if (p->lchild == NULL && p->rchild == NULL)
		return 1;
	else
		return 0;
}
void expandExternal(node *p) {
	node *lc; node *rc;
	getnode(&lc); getnode(&rc);
	p->lchild = lc;
	p->rchild = rc;
	lc->parent = p;
	rc->parent = p;
}
node *treeSearch(node *R, int k ) {
	if (isExternal(R) == 1)
		return R;
	if (R->key == k)
		return R;
	else if (R->key > k)
		return treeSearch(R->lchild, k);
	else
		return treeSearch(R->rchild, k);
}
void insertkey(node *R, int k) {
	node *w = treeSearch(R, k);
	if (isExternal(w) == 0)
		return;
	w->key = k;
	expandExternal(w);
}
void findElement(node *R, int k) {
	node *w = treeSearch(R, k);
	if (isExternal(w) == 0)
		printf("%d\n", k);
	else
		printf("X\n");
}
void print(node *R) {
	if (isExternal(R) == 1)
		return;
	printf(" %d", R->key);
	print(R->lchild);
	print(R->rchild);
}
node *sibling(node *R, node *w) {
	if (R == w)
		return R;
	else if (w->parent->lchild == w)
		return w->parent->rchild;
	else
		return w->parent->lchild;

}
node* inOrderSucc(node *p) {
	node *w = p->rchild;
	if (isExternal(w) == 1)
		return w;
	while (isExternal(w->lchild) == 0)
		w = w->lchild;
	return w;
}
void reduceExternal(node **R, node *z) {
	node *w = z->parent;
	node *zs = sibling(*R, z);
	if (w == *R) {		////부모가 루트
		zs->parent = NULL;
		*R = zs;
	}
	else {
		node *g = w->parent;
		zs->parent = g;
		if (g->lchild == w)
			g->lchild = zs;
		else
			g->rchild = zs;
	}
	free(w); free(z);
}
void removeElement(node **R, int k) {
	node *w = treeSearch(*R, k);
	if (isExternal(w) == 1) {
		printf("X\n");
		return;			////외부노드이면, 값이 없는 거니까 종료 
	}
	
	node *z = w->lchild;
	if (isExternal(z) == 0)
		z = w->rchild;		////둘 다 내부노드이면, 오른쪽 자식으로 이동

	if (isExternal(z) == 1)
		reduceExternal(R, z);
	else {
		node *y = inOrderSucc(w);
		z = y->lchild;
		w->key = y->key;
		reduceExternal(R, z);
	}
	printf("%d\n", k);
}

void main() {
	int *R; getnode(&R);
	int key; char order;
	
	while (1) {
		scanf("%c", &order);
		if (order == 'i') {
			scanf("%d", &key);
			getchar();
			insertkey(R, key);
		}
		else if (order == 'd') {
			scanf("%d", &key);
			getchar();
			removeElement(&R, key);
		}
		else if (order == 's') {
			scanf("%d", &key);
			getchar();
			findElement(R, key);
		}
		else if (order == 'p') {
			print(R);
			printf("\n");
		}
		else if (order == 'q')
			return;
	}
}

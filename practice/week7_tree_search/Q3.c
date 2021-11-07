#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct node {
	int key;
	int height;
	struct node *lchild;
	struct node *rchild;
	struct node *parent;
}Node;

Node *root;

int isExternal(Node *w)
{
	if ((w->lchild == NULL) && (w->rchild == NULL))
		return 1;
	else
		return 0;
}

int isInternal(Node *w)
{
	if ((w->lchild != NULL) && (w->rchild != NULL))
		return 1;
	else
		return 0;
}

Node *sibling(Node *w)
{
	if (w->parent == NULL)
		return;
	if (w->parent->lchild == w)
		return w->parent->rchild;
	else
		return w->parent->lchild;
}

Node *inOrderSucc(Node *w)
{
	w = w->rchild;
	if (isExternal(w))
		return;
	while (isInternal(w->lchild))
		w = w->lchild;
	return w;
}

void expandExternal(Node *w)
{
	Node *leftnode = (Node*)malloc(sizeof(Node));
	Node *rightnode = (Node*)malloc(sizeof(Node));

	leftnode->lchild = NULL;
	leftnode->rchild = NULL;
	leftnode->height = 0;
	leftnode->parent = w;

	rightnode->lchild = NULL;
	rightnode->rchild = NULL;
	rightnode->height = 0;
	rightnode->parent = w;

	w->lchild = leftnode;
	w->rchild = rightnode;
	w->height = 1;
}

Node *reduceExternal(Node *z)
{
	Node *p, *zs, *g;
	p = z->parent;
	zs = sibling(z);
	if (p->parent == NULL)
	{
		root = zs;
		zs->parent = NULL;
	}
	else
	{
		g = p->parent;
		zs -> parent = g;
		if (p == g->lchild)
			g->lchild = zs;
		else if (p == g->rchild)
			g->rchild = zs;
	}
	free(z);
	free(p);
	return zs;
}

Node* treeSearch(Node *w, int k) 
{
	if (isExternal(w))
		return w;

	if (w->key == k)
		return w;
	else if (w->key > k)
		return treeSearch(w->lchild, k);
	else
		return treeSearch(w->rchild, k);
}

int updateHeight(Node *w) 
{
	int height;

	if ((w->lchild->height) > (w->rchild->height))
		height = w->lchild->height + 1;
	else 
		height = w->rchild->height + 1;
	
	if (height != w->height) {
		w->height = height;
		return 1;
	}
	else 
		return 0;
}

int isBalanced(Node *w) 
{
	if ((-1 <= (w->lchild->height - w->rchild->height)) && ((w->lchild->height - w->rchild->height) <= 1))
		return 1;
	else 
		return 0;
}

Node* restructure(Node *x, Node *y, Node *z) 
{
	Node *a, *b, *c;
	Node *T0, *T1, *T2, *T3;

	if ((z->key < y->key) && (y->key < x->key)) 
	{
		a = z;
		b = y;
		c = x;

		T0 = a->lchild;
		T1 = b->lchild;
		T2 = c->lchild;
		T3 = c->rchild;
	}
	else if ((x->key < y->key) && (y->key < z->key)) 
	{
		a = x;
		b = y;
		c = z;

		T0 = a->lchild;
		T1 = a->rchild;
		T2 = b->rchild;
		T3 = c->rchild;
	}
	else if ((z->key < x->key) && (x->key < y->key)) 
	{
		a = z;
		b = x;
		c = y;

		T0 = a->lchild;
		T1 = b->lchild;
		T2 = b->rchild;
		T3 = c->rchild;
	}
	else 
	{
		a = y;
		b = x;
		c = z;

		T0 = a->lchild;
		T1 = b->lchild;
		T2 = b->rchild;
		T3 = c->rchild;
	}

	if (z->parent == NULL) 
	{
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->lchild == z) 
	{
		z->parent->lchild = b;
		b->parent = z->parent;
	}
	else if (z->parent->rchild == z) 
	{
		z->parent->rchild = b;
		b->parent = z->parent;
	}

	a->lchild = T0;
	T0->parent = a;
	a->rchild = T1;
	T1->parent = a;
	updateHeight(a);

	c->lchild = T2;
	T2->parent = c;
	c->rchild = T3;
	T3->parent = c;
	updateHeight(c);

	b->lchild = a;
	a->parent = b;
	b->rchild = c;
	c->parent = b;
	updateHeight(b);

	return b;
}

void searchAndFixAfterInsertion(Node *w) 
{
	Node *x, *y, *z;
	w->lchild->height = 0;
	w->rchild->height = 0;
	w->height = 1;

	if (w->parent == NULL)
		return NULL;
	z = w->parent;

	while (updateHeight(z) && isBalanced(z)) 
	{
		if (z->parent == NULL) 
			return;
		z = z->parent;
	}

	if (isBalanced(z))
		return;

	if (z->lchild->height > z->rchild->height) 
		y = z->lchild;
	else 
		y = z->rchild;

	if (y->lchild->height > y->rchild->height) 
		x = y->lchild;
	else 
		x = y->rchild;

	restructure(x, y, z);

	return;
}

void insertItem(Node *w, int k) 
{
	Node *p = treeSearch(w, k);

	if (isInternal(p)) 
		return;
	else 
	{
		p->key = k;
		expandExternal(p);
		searchAndFixAfterInsertion(p);
	}
}

void searchAndFixAfterRemoval(Node *w) {
	Node *x, *y, *z, *b;
	if (w == NULL) 
		return;
	z = w;
	while (updateHeight(z) && isBalanced(z)) 
	{
		if (z->parent == NULL) 
			return;
		z = z->parent;
	}

	if (isBalanced(z)) 
		return;

	if (z->lchild->height > z->rchild->height)
		y = z->lchild;
	else 
		y = z->rchild;

	if (y->lchild->height > y->rchild->height) 
		x = y->lchild;
	else if (y->lchild->height < y->rchild->height)
		x = y->rchild;
	else 
	{
		if (z->lchild == y) 
			x = y->lchild;
		else if (z->rchild == y)
			x = y->rchild;
	}
	b = restructure(x, y, z);
	searchAndFixAfterRemoval(b->parent);
}

int removeElement(Node *w, int k) {
	Node *p = treeSearch(w, k);
	Node *z, *zs, *y;
	int e;

	if (isExternal(p))
		return -1;
	e = p->key;
	z = p->lchild;
	if (!isExternal(z))
		z = p->rchild;

	if (isExternal(z)) 
		zs = reduceExternal(z);
	else 
	{
		y = inOrderSucc(p);
		z = y->lchild;
		p->key = y->key;
		zs = reduceExternal(z);
	}
	searchAndFixAfterRemoval(zs->parent);

	return e;
}

void printTree(Node *w) 
{
	if (isExternal(w))
		return;
	else 
	{
		printf(" %d", w->key);
		printTree(w->lchild);
		printTree(w->rchild);
	}
}

void freeTree(Node *w) 
{
	if (isExternal(w)) return;
	else 
	{
		freeTree(w->lchild);
		freeTree(w->rchild);
		free(w);
	}
}

int main() {
	char text;
	int key, value;

	root = (struct node*)malloc(sizeof(struct node));
	root->parent = NULL;
	root->lchild = NULL;
	root->rchild = NULL;

	while (1) 
	{
		scanf("%c", &text);
		if (text == 'i') 
		{
			scanf("%d", &key); getchar();
			insertItem(root, key);	
		}
		else if (text == 'd') 
		{
			scanf("%d", &key);
			value = removeElement(root, key);
			if (value == key) 
				printf("%d\n", value);
			else 
				printf("X\n");
			getchar();
		}
		else if (text == 's') 
		{
			scanf("%d", &key);
			if (treeSearch(root, key)->key != key) 
				printf("X\n");
			else 
				printf("%d\n", treeSearch(root, key)->key);
			getchar();
		}
		else if (text == 'p') 
		{
			printTree(root);
			printf("\n");
		}
		else if (text == 'q') break;
	}
	freeTree(root);
	return 0;
}

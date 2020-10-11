#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Treenode {
	int num;
	struct Node *lchild;
	struct Node *rchild;
}node; //���Ḯ��Ʈ ��� ����ü ����

void getNode(node **p) {
	(*p) = (node*)malloc(sizeof(node));
	(*p)->lchild = NULL;
	(*p)->rchild = NULL;
} //��� ����

void initTree(node **R, int rootnum, int l_num, int r_num) {
	(*R)->num = rootnum;

	node *lnode; getNode(&lnode); lnode->num = l_num;
	node *rnode; getNode(&rnode); rnode->num = r_num;

	(*R)->lchild = lnode;
	(*R)->rchild = rnode;
} //Ʈ���� root����


void addTree(node **R, int root_num, int l_num, int r_num) {
	if ((*R) == NULL) return;

	if ((*R)->num == root_num) {
		if (l_num != 0) {
			node *lnode; getNode(&lnode); lnode->num = l_num; //��� ����
			(*R)->lchild = lnode;
		}
		if (r_num != 0) {
			node *rnode; getNode(&rnode); rnode->num = r_num; //��� ����
			(*R)->rchild = rnode;
		}
	}

	addTree(&((*R)->lchild), root_num, l_num, r_num);
	addTree(&((*R)->rchild), root_num, l_num, r_num); //��ͷ� ��ȸ
}

void print(node *R, char tra[]) {
	char newtra[100] = "";

	if (R == NULL) return;
	else {
		printf(" %d", R->num);
		strcpy(newtra, tra + 1);

		if (tra[0] == 'L')
			print(R->lchild, newtra);
		if (tra[0] == 'R')
			print(R->rchild, newtra);
	}
}

int main() {
	int n, x, y, z;
	char tra[100] = "";
	node *R; getNode(&R);

	scanf("%d", &n); //��� ����

	scanf("%d %d %d", &x, &y, &z); //root���� ����
	initTree(&R, x, y, z);

	for (int i = 0; i < n - 1; i++) { //Ʈ�� ��� ����
		scanf("%d %d %d", &x, &y, &z);
		addTree(&R, x, y, z);
	}

	scanf("%d", &n); getchar();//Ž�� Ƚ��

	for (int i = 0; i < n; i++) {
		scanf("%s", tra); getchar();
		print(R, tra);
		printf("\n");
	}

	return 0;
}
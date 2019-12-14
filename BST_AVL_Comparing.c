#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct TreeNode {
	int data;
	struct TreeNode *leftChild, *rightChild;
}TreeNode;

TreeNode* rotate_LL(TreeNode *parent);
TreeNode* rotate_RR(TreeNode *parent);
TreeNode* rotate_RL(TreeNode *parent);
TreeNode* rotate_LR(TreeNode *parent);
TreeNode* rebalance(TreeNode **node);
TreeNode* BST_insert(TreeNode**, int);
TreeNode* avl_add(TreeNode **, int);
int get_height_diff(TreeNode *node);
int* makeRandNum(int, unsigned char);
int get_height(TreeNode *root);
int Tree_search(TreeNode* root, int value);

int main() {

	int i, j, nodeNum = 100;
	int *randArr;
	TreeNode *AVLroot = NULL, *BSTroot = NULL;
	unsigned char seed = 1;
	double bstAverSearch = 0.0, avlAverSearch = 0.0;
	double bstAverHeight = 0.0, avlAverHeight = 0.0;

	printf("-----------------------------------------------�ùķ��̼� ���---------------------------------------------\n\n\n");
	printf("����\t|\tBSt��ճ���\t|\tAvl��ճ���\t|\tBST���Ž���ð�\t|\tavl���Ž���ð�\n");
	printf("\t|\t\t\t|\t\t\t|\t\t\t|\n");
	printf("-----------------------------------------------------------------------------------------------------------\n");


	while (1) { 
		for (i = 0; i < 100; i++) {
			randArr = makeRandNum(nodeNum, seed);
			for (j = 0; j < nodeNum; j++) {
				avl_add(&AVLroot, randArr[j]);
				BST_insert(&BSTroot, randArr[j]);
			}
			bstAverHeight += get_height(BSTroot);
			avlAverHeight += get_height(AVLroot);
			bstAverSearch += Tree_search(BSTroot, randArr[77]);
			avlAverSearch += Tree_search(AVLroot, randArr[77]);
			BSTroot = NULL;
			AVLroot = NULL;
			seed++;
		}
		printf("\t|\t\t\t|\t\t\t|\t\t\t|\n");
		printf("%d\t|\t%f\t|\t%f\t|\t%f\t|\t%f\n", nodeNum,bstAverHeight / 100, avlAverHeight / 100, bstAverSearch / 100, avlAverSearch / 100);
		printf("-----------------------------------------------------------------------------------------------------------\n");
		avlAverHeight = 0, bstAverHeight = 0, avlAverSearch = 0, avlAverSearch = 0;
		if (nodeNum == 100)nodeNum = 1000;
		else if (nodeNum == 1000)nodeNum = 2000;
		else if (nodeNum == 2000) nodeNum = 5000;
		else if (nodeNum = 5000) nodeNum = 10000;
		else break;
	}
}

int* makeRandNum(int range, unsigned char seed) {
	int i, j, flag;
	static int a[10000] = { 0 };
	srand(seed);
//	printf("time is : %d", time(0));
	for (i = 0; i < range; ++i)
	{
		while (1)
		{
			a[i] = rand() % 10000 + 1;
			flag = 0;																	// �̹��ִ°�����Ȯ���ϱ������÷��׼���
			
			for (j = 0; j < i; ++j) {													// ���������ִ���Ȯ���Ѵ�
				if (a[j] == a[i]) {														// ��������������
					flag = 1;
					break;
				}
			}
			
			if (!flag)	break;															// �������̾�����while��Ż��		
		}
	}
	return a;
}

TreeNode* rotate_LL(TreeNode *parent) {

	TreeNode *child = parent->leftChild;
	parent->leftChild = child->rightChild;
	child->rightChild = parent;
	return child;
}

TreeNode* rotate_RR(TreeNode *parent) {

	TreeNode *child = parent->rightChild;
	parent->rightChild = child->leftChild;
	child->leftChild = parent;
	return child;

}

TreeNode* rotate_RL(TreeNode *parent) {

	TreeNode *child = parent->rightChild;
	parent->rightChild = rotate_LL(child);
	return rotate_RR(parent);
}

TreeNode* rotate_LR(TreeNode *parent) {

	TreeNode *child = parent->leftChild;
	parent->leftChild = rotate_RR(child);
	return rotate_LL(parent);

}

TreeNode* rebalance(TreeNode **node) {

	int height_diff = get_height_diff(*node);
	if (height_diff > 1) {
		if (get_height_diff((*node)->leftChild) > 0)
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}
	else if (height_diff < -1) {
		if (get_height_diff((*node)->rightChild) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}
	return *node;
}



int get_height(TreeNode *root) {
	if (!root)
		return 0;
	else {
		int left_h = get_height(root->leftChild); // ���� ����Ʈ���� ���̸� ��ȯȣ���� ���� ��´�.
		int right_h = get_height(root->rightChild); // ���� ������� ������ ����Ʈ���� ���̸� ��´�.
		return 1 + (left_h > right_h ? left_h : right_h); // �� �� ū ���� 1�� ���� ��ȯ�Ѵ�.
	}
}
int get_height_bst(TreeNode *root) {
	if (!root)
		return 0;
	else {
		int left_h = get_height_bst(root->leftChild); // ���� ����Ʈ���� ���̸� ��ȯȣ���� ���� ��´�.
		int right_h = get_height_bst(root->rightChild); // ���� ������� ������ ����Ʈ���� ���̸� ��´�.
		return 1 + (left_h > right_h ? left_h : right_h); // �� �� ū ���� 1�� ���� ��ȯ�Ѵ�.
	}
}

int get_height_diff(TreeNode *node) {
	if (node == NULL) return 0;
	return get_height(node->leftChild) - get_height(node->rightChild);
}

TreeNode * avl_add(TreeNode **root, int new_key) {
	if (*root == NULL) {
		*root = (TreeNode *)malloc(sizeof(TreeNode));
		if (*root == NULL) {
			printf("�޸� �Ҵ� ����\n");
			exit(1);
		}
		(*root)->data = new_key;
		(*root)->leftChild = (*root)->rightChild = NULL;
	}
	else if (new_key < (*root)->data) {
		(*root)->leftChild = avl_add(&((*root)->leftChild), new_key);
		*root = rebalance(root);

	}
	else if (new_key >(*root)->data) {
		(*root)->rightChild = avl_add(&((*root)->rightChild), new_key);
		*root = rebalance(root);
	}
	else {
		printf("�ߺ��� Ű ����\n");
		exit(1);
	}
	return *root;
}


TreeNode* BST_insert(TreeNode **root, int key){

	TreeNode *p, *t = *root;
	TreeNode *n;
	p = NULL;

	while (t != NULL) {
		if (key == t->data) return;
		p = t;
		if (key < p->data)
			t = p->leftChild;
		else
			t = p->rightChild;
 	}
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL)return;

	n->data = key;
	n->leftChild = n->rightChild = NULL;
	if (p != NULL) {
		if (key < p->data)
			p->leftChild = n;
		else p->rightChild = n;
	}
	else *root = n;

}

int Tree_search(TreeNode* root, int value)
{
	int time = 0;
	while (root != NULL) {
		time++;
		if (value == root->data) return time;
		else if (value < root->data)
			root = root->leftChild;
		else
			root = root->rightChild;
	}	
	//Ž�� ����
	return 0;
}

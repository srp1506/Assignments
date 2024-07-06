#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct node {

	int data;
	struct node* left;
	struct node* right;
}node;

node* Create_node (int val) {

	node* new;
	new = (node*)malloc(sizeof(node));
	new->data = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

node* Insert_left (int val, node* root) {

	node* left;
	left = Create_node(val);
	root->left = left;
	return left;
}

node* Insert_right (int val, node* root) {

	node* right;
	right = Create_node(val);
	root->right = right;
	return right;
}

void Preorder (node* root) {

	if (root == NULL) return;
	
	else {
	
		printf(" %d ", root->data);
		Preorder(root->left);
		Preorder(root->right);
	}
}

void Inorder (node* root) {

	if (root == NULL) return;

	else {
	
		Inorder(root->left);
		printf(" %d ", root->data);
		Inorder(root->right);
	}
}

void Postorder (node* root) {

	if (root == NULL) return;

	else {
	
		Postorder(root->left);
		Postorder(root->right);
		printf(" %d ", root->data);
	}
}

int main() {

	node* root;
	node* new;
	root = Create_node(1);
	new = Insert_left(2, root);
	Insert_left(4, new);
	new = Insert_right(3, root);
	new->left = Insert_left(5, new);
	new->right = Insert_right(6, new);
	new->left->left = Insert_left(7, new->left);
	new->left->right = Insert_right(8, new->left);
	printf("Preorder Sequence :");
	Preorder(root);
	printf("\nInorder Sequence :");
	Inorder(root);
	printf("\nPostorder Sequence :");
	Postorder(root);
	printf("\n");
	return 0;
}

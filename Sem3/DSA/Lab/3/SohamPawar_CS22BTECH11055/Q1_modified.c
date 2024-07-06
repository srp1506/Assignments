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

	int size;
	node* root;
	printf("Enter The Number Of Nodes In The Tree : ");
	scanf("%d", &size);

	if (size <= 0) {
	
		printf("Enter Valid Input\n");
		return 0;
	}
	
	int nodes[size][3];
	node* lookup[1000];

	printf("Enter The Node Value And It's Left Children And Right Children Value(-1 If Not Present) Respectively : \n");

	for (int i = 0 ; i < size ; i++) {
	
		for (int j = 0 ; j < 3 ; j++) {
		
			scanf("%d", &nodes[i][j]);
		}
		printf("\n");
	}
	
	for (int i = 0 ; i < size ; i++) {
		
		lookup[nodes[i][0]] = Create_node(nodes[i][0]);
		
		if (i == 0) root = lookup[nodes[0][0]];
	}

	for (int i = 0 ; i < size ; i++) {
	
		for (int j = 1 ; j < 3; j++) {
		
			node* temp;
			temp = lookup[nodes[i][0]];
			
			if (j == 1) if (nodes[i][1] != -1) temp->left = lookup[nodes[i][1]];
			if (j == 2) if (nodes[i][2] != -1) temp->right = lookup[nodes[i][2]];

		}
	}

	printf("Preorder Sequence :");
	Preorder(root);
	printf("\nInorder Sequence :");
	Inorder(root);
	printf("\nPostorder Sequence :");
	Postorder(root);
	printf("\n");
	return 0;
}

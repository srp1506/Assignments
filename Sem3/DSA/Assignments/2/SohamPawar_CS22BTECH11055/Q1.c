#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// Define a node structure for the binary tree
typedef struct node {

	int data;
	struct node* left;
	struct node* right;
}node;

// Function to create a node with the given value
node* Create_node(int val) {

	node* new;
	new = (node*)malloc(sizeof(node));
	new->data = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

node* stack1[256]; // Stack to store nodes
node* stack2[256]; // Stack to store nodes
int counter1 = 0; // Counter to keep track of the stack size
int counter2 = 0; // Counter to keep track of the stack size

// Function to pop an element from stack1
node* Pop_stack1() {

	if (counter1 == 0) return NULL;

	counter1--;
	return stack1[counter1];
}

// Function to push an element onto stack1
void Push_stack1(node* node) {

	stack1[counter1] = node;
	counter1++;
}

// Function to pop an element from stack2
node* Pop_stack2() {

	if (counter2 == 0) return NULL;

	counter2--;
	return stack2[counter2];
}

// Function to push an element onto stack2
void Push_stack2(node* node) {

	stack2[counter2] = node;
	counter2++;
}

// Function to print the tree in preorder
void Preorder(node* root) {

	printf("Preorder : \n");
	Push_stack1(root);

	while (counter1 != 0) {

		root = Pop_stack1();

		if (root == NULL) continue;

		printf("%d ", root->data);
		Push_stack1(root->right);
		Push_stack1(root->left);
	}
	printf("\n");
}

// Function to print the tree in inorder
void Inorder(node* root) {

	printf("Inorder : \n");
	Push_stack1(root);

	while (counter1 != 0) {

		while (root != NULL) {

			root = root->left;

			if (root != NULL) Push_stack1(root);
		}

		if (root == NULL && counter1 != 0) {

			root = Pop_stack1();
			printf("%d ", root->data);
			root = root->right;
		
			if (root != NULL) Push_stack1(root);
		}
	}
	printf("\n");
}

// Function to print the tree in postorder
void Postorder(node* root) {

	printf("Postorder : \n");
	Push_stack1(root);
	
	while (counter1 != 0) {
	
		root = Pop_stack1();
		
		if (root != NULL) Push_stack2(root);
		if (root->left != NULL) Push_stack1(root->left);
		if (root->right != NULL) Push_stack1(root->right);
	}

	while (counter2 != 0) printf("%d ", Pop_stack2()->data);
	printf("\n");
}

int main() {

	int size; // Size of the tree
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

	Preorder(root);
	counter1 = 0; // Resetting stack
	Inorder(root);
	counter1 = 0; // Resetting stack
	Postorder(root);
	counter1 = 0; // Resetting stack
	return 0;
}

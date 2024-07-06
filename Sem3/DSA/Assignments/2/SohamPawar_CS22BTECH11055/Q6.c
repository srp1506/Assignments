#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// Define a node structure for the binary tree
typedef struct node {

	int data;
	int counter;
	struct node* left;
	struct node* right;
	struct node* next;
}node;

// Function to create a node with the given value
node* Create_node(int val) {

	node* new;
	new = (node*)malloc(sizeof(node));
	new->data = val;
	new->counter = 0;
	new->left = NULL;
	new->right = NULL;
	new->next = NULL;
	return new;
}

// Function to enqueue
void Enqueue(node* new, node* head) {

	if (head->next == NULL) head->next = NULL;

	node* trav;
	trav = head;

	while (trav->next != NULL) trav = trav->next;

	trav->next = new;
}

// Function to dequeue
node* Dequeue(node* head) {

	if (head->next == NULL) return NULL;

	node* temp;
	temp = head->next;
	head->next = temp->next;

	return temp;
}

// Function to rank each of the nodes in the tree
void Rank(node* root, int rank) {

	if (root == NULL) return;
	
	else {
	
		root->counter = rank;
		
		Rank(root->left, rank - 1);
		Rank(root->right, rank + 1);
	}
}

// Function to print the tree in vertical order
void Print(node* root, int val) {

	if (root == NULL) return;
	
	else {
	
		if (root->counter == val) printf(" %d ", root->data);
		
		Print(root->left, val);
		Print(root->right, val);
	}
}

int main() {

	int size; // Size of the tree
	node* head; // Head of the queue
	node* root; 
	head = Create_node(-1); // Initialising the head with a dummy value
	printf("Enter The Number Of Nodes In The Tree : ");
	scanf("%d", &size);

	if (size <= 0) {

		printf("Enter Valid Input\n");
		return 0;
	}
	
	int nodes[size][3];

	printf("Enter The Node Value And It's Left Children And Right Children Value(-1 If Not Present) Respectively in BFS order: \n");

	for (int i = 0 ; i < size ; i++) {

		for (int j = 0 ; j < 3 ; j++) {

			scanf("%d", &nodes[i][j]);
		}
		printf("\n");
	}
	
	root = Create_node(nodes[0][0]);
	Enqueue(root, head);
	
	for (int i = 0 ; i < size ; i++) {
	
		node* current;
		node* left;
		node* right;
		current = Dequeue(head);
		
		if (nodes[i][1] != -1) left = Create_node(nodes[i][1]);
		else left = NULL;
		if (nodes[i][2] != -1) right = Create_node(nodes[i][2]);
		else right = NULL;
		
		current->left = left;
		current->right = right;

		if (left != NULL) Enqueue(left, head);
		if (right != NULL) Enqueue(right, head);
	}
	
	Rank(root, 0);
	printf("Vertical Order Traversal(root is considered 0) :\n");
	
	for (int i = -size + 1; i < size ; i++){
	
	 	printf("%4d : ", i);	
		Print(root, i);
		printf("\n");
	}		
	return 0;
}

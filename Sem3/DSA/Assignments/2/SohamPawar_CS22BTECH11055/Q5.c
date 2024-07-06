#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// Define a node structure for the binary tree
typedef struct node {

	int data;
	struct node* left;
	struct node* right;
	struct node* next;
}node;

// Function to create a node with the given value
node* Create_node(int val) {

	node* new;
	new = (node*)malloc(sizeof(node));
	new->data = val;
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

// Function to evaluate the arithmetic tree
int Evaluate(node* root) {

	if (root->left == NULL) return root->data;
	
	switch(root->data) {
	
		case 43:
			root->data = Evaluate(root->left) + Evaluate(root->right);
			break;
		case 42:
			root->data = Evaluate(root->left) * Evaluate(root->right);
			break;
		case 47:
			root->data = Evaluate(root->left) / Evaluate(root->right);
			break;
		case 45:
			root->data = Evaluate(root->left) - Evaluate(root->right);
			break;
		case 37:
			root->data = Evaluate(root->left) % Evaluate(root->right);
			break;
		default:
			printf("Operation not supported\n");
			exit(0);
	}
	return root->data;
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
	
	printf("Please refer the following for the ascii values of the operations you would like to perform :\n1) + : 43\n2) - : 45\n3) * : 42\n4) / : 47\n5) % : 37\n");
	printf("\nEnter The Node Value And It's Left Children And Right Children Value(-1 If Not Present) Respectively in BFS order: \n");

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
	
	printf("Result : %d\n", Evaluate(root));
	return 0;
}

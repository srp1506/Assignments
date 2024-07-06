#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

int root_index;
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

node* queue[100]; // Initialising an array for queue
int head = 0; // Head of the queue
int tail = 0; // Tail of the queue

// Function to enqueue
void Enqueue(node* array[], node* val) {

	array[tail++] = val;
}

// Function to dequeue
node* Dequeue(node* array[]) {

	if (head == tail) {

		printf("Error : Queue Underflow!\n");
		exit(0);
	}

	return array[head++];
}

// Function to peek i.e check the element at the head
node* Peek(node* queue[]) {

	return queue[head];
}

// Function to get the size of the queue
int Size() {

	return tail - head;
}

// Function to check if the queue is empty
bool Check_empty(node* array[]) {

	if (head == tail) return true;
	else return false;
}

// Function to print the tree in BFS order
void BFS(node* root) {

	if (root == NULL) return;
	Enqueue(queue, root);

	while (!Check_empty(queue)) {

		int count = Size();

		while (count > 0) {

			node* temp;
			temp = Peek(queue);
			printf("%d ", temp->data);
			Dequeue(queue);
			
			if (temp->left != NULL) Enqueue(queue, temp->left);
			if (temp->right != NULL) Enqueue(queue, temp->right);
			
			count--;
		}
		printf("\n");
	}
}

// Function to search for a character in the traversal within specified bounds
int Search(int array[], int key, int lower, int upper) {

	for (int i = lower ; i <= upper ; i++) if (array[i] == key) return i;

	return -1;
}

// Function to build tree using the given traversals
node* Make_tree(int post[], int in[], int lower, int upper) {

	int index;

	if (lower > upper) return NULL;

	node* root;
	root = Create_node(post[root_index]);
	index = Search(in, root->data, lower, upper);
	root_index--;

	if (lower == upper && index != -1) return root;


	if (index == -1) {
	
		printf("Tree doesn't exit");
		exit(0);
	}

	root->right = Make_tree(post, in, index + 1, upper);
	root->left = Make_tree(post, in, lower, index - 1);

	return root;
}

int main() {

	int size; // Size of the tree
	node* root;
	printf("Enter the number of nodes in the tree :\n");
	scanf("%d", &size);
	
	if (size <= 0) {

		printf("Enter Valid Input\n");
		return 0;
	}
	
	int postorder[size];
	int inorder[size];

	printf("Enter the inorder traversal of the tree :\n");
	for (int i = 0 ; i < size ; i++) scanf("%d", &inorder[i]);

	printf("Enter the postorder traversal of the tree :\n");
	for (int i = 0 ; i < size ; i++) scanf("%d", &postorder[i]);

	root_index = size - 1;
	root = Make_tree(postorder, inorder, 0, size - 1);
	printf("\nBreadth First Search traversal of the tree :\n");
	BFS(root);
	return 0;
}

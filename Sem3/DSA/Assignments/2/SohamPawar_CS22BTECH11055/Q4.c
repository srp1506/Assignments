#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

int pre_index = 0;
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
node* Make_tree(int pre[], int post[], int post_start, int post_end, int size) {
    
    if (pre_index >= size || post_start > post_end) return NULL;

    node* root = Create_node(pre[pre_index]);
    pre_index++;

    if (pre_index < size) {
        
        int post_index;
        post_index = post_start;
        
        while (post_index <= post_end && post[post_index] != pre[pre_index]) post_index++;

        if (post_index <= post_end) {

            root->left = Make_tree(pre, post, post_start, post_index, size);
            root->right = Make_tree(pre, post, post_index + 1, post_end - 1, size);
        }
    }
    return root;
}

int main() {

	node* root;
	int size; // Size of the tree
	printf("Enter the number of nodes in the tree :\n");
	scanf("%d", &size);
	
	if (size <= 0) {

		printf("Enter Valid Input\n");
		return 0;
	}
	
	int preorder[size];
	
	int postorder[size];
	
	printf("Enter the preorder traversal of the tree :\n");
	for (int i = 0 ; i < size ; i++) scanf("%d", &preorder[i]);
	
	printf("Enter the postorder traversal of the tree :\n");
	for (int i = 0 ; i < size ; i++) scanf("%d", &postorder[i]);
	

	root = Make_tree(preorder, postorder, 0, size - 1, size);
	printf("\nBreadth First Search traversal of the tree :\n");
	BFS(root);
	return 0;
}

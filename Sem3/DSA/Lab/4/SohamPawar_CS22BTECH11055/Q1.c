#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

typedef struct node {

	int data;
	struct node* left;
	struct node* right;
}node;

node* Create_node(int val) {

	node* new;
	new = (node*)malloc(sizeof(node));
	new->data = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

node* stack[256];
int counter = 0;

node* Pop_stack() {

	if (counter == 0) return NULL;

	counter--;
	return stack[counter];
}

void Push_stack(node* node) {

	stack[counter] = node;
	counter++;
}

node* queue[100];
int head = 0;
int tail = 0;

void Enqueue(node* array[], node* val) {

	array[tail++] = val;
}

node* Dequeue(node* array[]) {

	if (head == tail) {

		printf("Error : Queue Underflow!\n");
		exit(0);
	}

	return array[head++];
}

node* Front(node* queue[]) {

	return queue[head];
}

int Size() {

	return tail - head;
}

bool Check_empty(node* array[]) {

	if (head == tail) return true;
	else return false;
}

void BFS(node* root) {

	if (root == NULL) return;
	Enqueue(queue, root);

	while (!Check_empty(queue)) {

		int count = Size();

		while (count > 0){

			node* temp;
			temp = Front(queue);
			printf("%d ", temp->data);
			Dequeue(queue);
			if (temp->left != NULL) Enqueue(queue, temp->left);
			if (temp->right != NULL) Enqueue(queue, temp->right);
			count--;
		}
		printf("\n");
	}
}

void Insert(node* root, int key) {

	while (root->left != NULL || root->right != NULL) {

		if (root->data >= key) {
			if (root->left != NULL) root = root->left;
			else break;
		}

		else {
			if (root->right != NULL) root = root->right;
			else break;
		}
	}

	node* new = Create_node(key);
	if (root->data >= key) root->left = new;
	else root->right = new;
}

node* Search(node* root, int key) {

	while (root->data != key) {

		if (root->data >= key) {
			if (root->left != NULL) root = root->left;
			else break;
		}

		else {
			if (root->right != NULL) root = root->right;
			else break;
		}
	}
	if (root->data == key) return root;
	else return NULL;	
}

node* Successor(node* root, int key) {

	if (Search(root, key) == NULL) {

		printf("Key not present\n");
		return NULL;
	}

	node* temp;
	temp = Search(root, key);

	if (root->right != NULL) {

		while (root->data != key) {

			if (root->data > key) {

				temp = root;
				root = root->left;
			}
			else if (root->data < key) root = root->right;
		}
		return temp;
	}
	else {
		temp = temp->right;
		while (temp->left != NULL) temp = temp->left;
		return temp;
	}
}

void Delete(node* root, int key) {

	if (Search(root, key) == NULL) {

		printf("%d not present\n", key);
		return;
	}

	node* parent;

	while (root->data != key) {

		if (root->data >= key) {

			if (root->left != NULL) {

				Push_stack(root);
				root = root->left;
			}
			else break;
		}
		else {

			if (root->right != NULL){

				Push_stack(root);
				root = root->right;
			}
			else break;
		}
	}

	if (root->left == NULL && root->right == NULL) {

		parent = Pop_stack();
		if (parent->left != NULL) if ((parent->left)->data == key) parent->left = NULL;
		else parent->right = NULL;
		root = NULL;
	}	
	else if (root->left == NULL && root->right != NULL) {

		parent = Pop_stack();
		if (parent->left != NULL) if ((parent->left)->data == key) parent->left = root->right;
		else parent->right = root->right;
		root = NULL;
	}
	else if (root->right == NULL && root->left != NULL) {

		parent = Pop_stack();
		if (parent->left != NULL) if ((parent->left)->data == key) parent->left = root->left;
		else parent->right = root->left;
		root = NULL;
	}
	else {
		node* temp;
		temp = root->right;

		while (temp->left != NULL) {

			Push_stack(temp);
			temp = temp->left;
		}

		root->data = temp->data;

		if (temp->right != NULL) {

			parent = Pop_stack();
			parent->left = temp->right;
			temp = NULL;
		}
		else temp = NULL;
	}
	printf("%d deleted\n", key);
	counter = 0;
}

int main() {

	int size;
	int val;
	node* root;
	printf("Enter the size of the input space : ");
	scanf("%d", &size);

	if (size <= 0) {

		printf("Enter Valid Input\n");
		return 0;
	}

	printf("Enter The elements to be inserted :\n");
	scanf("%d", &val);
	root = Create_node(val);
	for (int i = 1 ; i < size ; i++) {

		scanf("%d", &val);
		Insert(root, val);
	}
	printf("\nLevel By Level Traversal(before alteration) :\n");
	BFS(root);
	Insert(root, 32);
	Insert(root, 56);
	Insert(root, 21);
	Insert(root, 90);
	printf("\nInsertion Implementation :\n");
	BFS(root);
	printf("\nSearch Implementation :\n");
	Search(root, 32) == NULL ? printf("32 not found\n") : printf("32 found\n");
	Search(root, 56) == NULL ? printf("56 not found\n") : printf("56 found\n");
	Search(root, 90) == NULL ? printf("90 not found\n") : printf("90 found\n");
	printf("\nSuccessor Implementation :\n");
	if (Search(root, 32) != NULL) printf("Successor of 32 : %d\n", Successor(root, 32)->data);
	if (Search(root, 56) != NULL) printf("Successor of 56 : %d\n", Successor(root, 56)->data);
	if (Search(root, 90) != NULL) printf("Successor of 90 : %d\n", Successor(root, 90)->data);
	if (Search(root, 21) != NULL) printf("Successor of 21 : %d\n", Successor(root, 21)->data);
	printf("\nDeletion Implementation :\n");
	Delete(root, 51);
	Delete(root, 332);
	Delete(root, 71);
	Delete(root, 67);
	Delete(root, 21);
	Delete(root, 12);
	printf("\n");
	printf("Level By Level Traversal(after alteration) :\n");
	BFS(root);
	return 0;
}

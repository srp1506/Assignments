#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<ctype.h>
#include<math.h>
#include<unistd.h>

typedef struct node {

	int data;
	int color; // 1 for red, 0 for black
	struct node* left;
	struct node* right;
	struct node* parent;
}node;

node* Tree_root;

node* Create_node(int val) {

	node* new = (node*)malloc(sizeof(node));
	new->data = val;
	new->color = 1;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	return new;
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

node* Peek(node* queue[]) {

	return queue[head];
}

int Size() {

	return tail - head;
}

bool Check_empty(node* array[]) {

	if (head == tail) return true;
	else return false;
}

void Clear_queue(){
    
	head = 0;
    tail = 0;
}

void Left_rotation(node* root) {

	node* parent;
	node* right;
	right = root->right;
	parent = root->parent;
	root->right = right->left;

	if (right->left != NULL) right->left->parent = root;

	right->left = root;
	root->parent = right;
	right->parent = parent;

	if (parent != NULL) {

		if (parent->left == root) parent->left = right;
		else parent->right = right;
	}

	else Tree_root = right;
	return;
}

void Right_rotation(node* root) {

	node* parent;
	node* left;
	left = root->left;
	parent = root->parent;
	root->left = left->right;

	if (left->right != NULL) left->right->parent = root;

	left->right = root;
	root->parent = left;
	left->parent = parent;

	if (parent != NULL) {

		if (parent->left == root) parent->left = left;
		else parent->right = left;
	}

	else Tree_root = left;
	return;
}

node* Search(node* root, int key) {

	if (root == NULL) return NULL;

	while (root->data != key) {

		if (root->data > key) {
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

void Insert_fix(node* root) {

	while (root->parent != NULL && root->parent->parent != NULL && root->parent->color == 1) {
		
		node* uncle;

		if (root->parent == root->parent->parent->left) {
			
			uncle = root->parent->parent->right;

			if (uncle != NULL && uncle->color == 1) {
				
				root->parent->color = 0;
				uncle->color = 0;
				root->parent->parent->color = 1;
				root = root->parent->parent;
			} 
			else {
				if (root == root->parent->right) {
					
					root = root->parent;
					Left_rotation(root);
				}
			
				root->parent->color = 0;
			
				if (root->parent->parent != NULL) {
					
					root->parent->parent->color = 1;
					Right_rotation(root->parent->parent);
				}
			}
		} 
		else {
			
			uncle = root->parent->parent->left;

			if (uncle != NULL && uncle->color == 1) {
				
				root->parent->color = 0;
				uncle->color = 0;
				root->parent->parent->color = 1;
				root = root->parent->parent;
			} 
			else {
				if (root == root->parent->left) {
					
					root = root->parent;
					Right_rotation(root);
				}
				
				root->parent->color = 0;
				
				if (root->parent->parent != NULL) {
				
					root->parent->parent->color = 1;
					Left_rotation(root->parent->parent);
				}
			}
		}
	}
	if (Tree_root != NULL) Tree_root->color = 0;
}

int Insert(node* root, int key) {

	if (Search(root, key) != NULL) return 0;

	while (root->left != NULL || root->right != NULL) {

		if (root->data > key) {

			if (root->left != NULL) root = root->left;
			else break;
		}
		else {
			if (root->right != NULL) root = root->right;
			else break;
		}
	}

	node* new = Create_node(key);
	if (root->data > key) root->left = new;
	else root->right = new;
	new->parent = root;
	Insert_fix(new);
	return 1;
}

void Enumerate(node* root, int min, int max) {

	if (root->data >= min && root->data <= max) {
		
		printf("%d ", root->data);
		if (root->left != NULL) Enumerate(root->left, min, max);
		if (root->right != NULL) Enumerate(root->right, min, max);
	}
	else if (root->data < min) {
	
		if (root->right != NULL) Enumerate(root->right, min, max);
		else return;
	} 
	else {
		if (root->left != NULL) Enumerate(root->left, min, max);
		else return;
	}
	return;
}

int main (int argc, char *argv[]) {

	int size;
	int val;
    int max;
    int min;
	scanf("%d", &size);

	if (size <= 0) {

		printf("Invalid size\n");
		exit(0);
	}

	scanf("%d", &val);
	Tree_root = Create_node(val);

	for (int i = 1 ; i < size ; i++) {


		scanf("%d", &val);
		Insert(Tree_root, val);
	}

    scanf("%d%d", &min, &max);
    Enumerate(Tree_root, min, max);
    return 0;
}

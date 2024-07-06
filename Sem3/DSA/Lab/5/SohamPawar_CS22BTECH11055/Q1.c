#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>
#include<stdbool.h>
#include<ctype.h>

typedef struct node {

	int data;
	struct node* left;
	struct node* right;
	struct node* parent;
	int height;
}node;

node* Create_node(int val) {

	node* new = (node*)malloc(sizeof(node));
	new->data = val;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	new->height = 0;
	return new;
}

node* Tree_root;

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

int Update(node* root) {

	if (root == NULL) return -1;

	int left = Update(root->left);
	int right = Update(root->right);

	root->height = (left >= right ? left : right ) + 1;
	
	return root->height;
}

void Balance_tree(node* root) {

	int rheight = (root->right != NULL ? (root->right)->height : -1);
	int lheight = (root->left != NULL ? (root->left)->height : -1);
	int balance = rheight - lheight;
	node* parent;
	parent = root;

	while (1) {
	
		if (root == NULL) break;
		
		int rheight = (root->right != NULL ? (root->right)->height : -1);
		int lheight = (root->left != NULL ? (root->left)->height : -1);
		balance = rheight - lheight;
		
		if (balance == -2 || balance == 2) break;
		
		parent = root->parent;
		root = root->parent;
	}

	root = parent;

	if (balance == -2) {
		
		int rheight = (root->left->right != NULL ? (root->left->right)->height : -1);
		int lheight = (root->left->left != NULL ? (root->left->left)->height : -1);
		balance = rheight - lheight;
		
		if (balance < 0) Right_rotation(root);
		else {
			Left_rotation(root->left);
			Right_rotation(root);
		}
	}
	else if (balance == 2) {

		int rheight = (root->right->right != NULL ? (root->right->right)->height : -1);
		int lheight = (root->right->left != NULL ? (root->right->left)->height : -1);
		balance = rheight - lheight;		

		if (balance > 0) Left_rotation(root);
		else {
			Right_rotation(root->right);
			Left_rotation(root);
		}
	}
	else return;
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
	new->parent = root;

	Update(Tree_root);
	
	if (root != Tree_root) Balance_tree(root->parent);
	else Balance_tree(Tree_root);
}

void Delete(node* root, int key) {

	if (Search(root, key) == NULL) {

		printf("%d not present\n", key);
		return;
	}

	node* parent;

	while (root->data != key) {

		if (root->data >= key) {

			if (root->left != NULL) root = root->left;
			else break;
		}
		else {

			if (root->right != NULL) root = root->right;
			else break;
		}
		Push_stack(root);
	}

	if (root->left == NULL && root->right == NULL) {

		parent = Pop_stack();
		if (parent->left != NULL && (parent->left)->data == key) parent->left = NULL;
		else parent->right = NULL;
		root = NULL;
	}	
	else if (root->left == NULL && root->right != NULL) {

		parent = Pop_stack();
		root->right->parent = parent;
		if (parent->left != NULL && (parent->left)->data == key) parent->left = root->right;
		else parent->right = root->right;
		root = NULL;
	}
	else if (root->right == NULL && root->left != NULL) {

		parent = Pop_stack();
		root->left->parent = parent;
		if (parent->left != NULL && (parent->left)->data == key) parent->left = root->left;
		else parent->right = root->left;
		root = NULL;
	}
	else {
		
		node* temp;
		temp = root->right;
		Push_stack(temp);

		while (temp->left != NULL) {

			Push_stack(temp);
			temp = temp->left;
		}

		root->data = temp->data;

		// if (temp->right != NULL) {

		// 	parent = Pop_stack();
		// 	parent->left = temp->right;
		// 	if (parent == temp) temp->right->parent = temp->parent;
		// 	else temp->right->parent = parent;
		// 	temp = NULL;
		// }
		parent = temp->parent;
		if (temp->parent->left == temp) temp->parent->left = NULL;
		else temp->parent->right = NULL;
	}
	printf("%d deleted\n", key);
	Update(Tree_root);
	if (parent != NULL) Balance_tree(parent);
	
	while (counter) {
		
		root = Pop_stack();
		Update(Tree_root);
		if (root != NULL) Balance_tree(root);
	}
	counter = 0;
}

int main() {

	int size;
	int val;
	printf("Enter the size of the input space : ");
	scanf("%d", &size);

	if (size <= 0) {

		printf("Enter Valid Input\n");
		return 0;
	}

	printf("Enter The elements to be inserted :\n");
	scanf("%d", &val);
	Tree_root = Create_node(val);
	
	for (int i = 1 ; i < size ; i++) {

		scanf("%d", &val);
		Insert(Tree_root, val);
	}

	printf("\nBFS of original AVL tree :\n");
	BFS(Tree_root);
	printf("\n");
	Insert(Tree_root, 32);
	Insert(Tree_root, 56);
	Insert(Tree_root, 21);
	Insert(Tree_root, 90);
	printf("BFS of AVL tree after insertion:\n");
	BFS(Tree_root);
	printf("\n");
	printf("Search Implementation :\n");
	Search(Tree_root, 32) == NULL ? printf("32 not found\n") : printf("32 found\n");
	Search(Tree_root, 56) == NULL ? printf("56 not found\n") : printf("56 found\n");
	Search(Tree_root, 90) == NULL ? printf("90 not found\n") : printf("90 found\n");
	printf("\n");
	Delete(Tree_root, 32);
	Delete(Tree_root, 51);
	Delete(Tree_root, 71);
	Delete(Tree_root, 67);
	//Delete(Tree_root, Tree_root->data);
	printf("\nBFS of AVL tree after deletion:\n");
	BFS(Tree_root);
	printf("\n");
	return 0;
}

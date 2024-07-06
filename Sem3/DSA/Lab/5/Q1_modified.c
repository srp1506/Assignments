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
	int height;
	int balance;
}node;

node* Create_node(int val) {

	node* new = (node*)malloc(sizeof(node));
	new->data = val;
	new->left = NULL;
	new->right = NULL;
	new->height = 0;
	new->balance = 0;
	return new;
}

node* Tree_root;

node* stack1[256];
int counter1 = 0;
node* stack2[256];
int counter2 = 0;

node* Pop_stack1() {

	if (counter1 == 0) return NULL;

	counter1--;
	return stack1[counter1];
}

void Push_stack1(node* node) {

	stack1[counter1] = node;
	counter1++;
}

node* Pop_stack2() {

	if (counter2 == 0) return NULL;

	counter2--;
	return stack2[counter2];
}

void Push_stack2(node* node) {

	stack2[counter2] = node;
	counter2++;
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
	parent = Pop_stack1();
	node* right;
	right = root->right;
	root->right = right->left;
	right->left = root;
	
	if (parent != NULL) {
	
		if (parent->left == root) parent->left = right;
		else parent->right = right;
	}
	else Tree_root = right;
	return;
}

void Right_rotation(node* root) {

	node* parent;
	parent = Pop_stack1();
	node* left;
	left = root->left;
	root->left = left->right;
	left->right = root;
	
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
	root->balance = right - left;
	
	return root->height;
}

void Balance_tree() {

	node* root;

	while (counter1) {
	
		root = Pop_stack1();

		if (root->balance == -2 || root->balance == 2) break;
	}

	if (root->balance == -2) {
	
		if (root->left->balance < 0) Right_rotation(root);
		else {
			Push_stack1(root);
			Left_rotation(root->left);
			Right_rotation(root);
		}
	}
	else if (root->balance == 2) {
		
		if (root->right->balance > 0) Left_rotation(root);
		else {
			Push_stack1(root);
			Right_rotation(root->right);
			Left_rotation(root);
		}
	}
	else return;
}

void Insert(node* root, int key) {

	Push_stack1(root);

	while (root->left != NULL || root->right != NULL) {

		if (root->data >= key) {

			if (root->left != NULL) root = root->left;
			else break;
		}

		else {
			if (root->right != NULL) root = root->right;
			else break;
		}
		Push_stack1(root);
	}

	node* new = Create_node(key);
	if (root->data >= key) root->left = new;
	else root->right = new;
	Update(Tree_root);
	Balance_tree();
	counter1 = 0;
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
		Push_stack1(root);
		Push_stack2(root);
	}

	if (root->left == NULL && root->right == NULL) {

		parent = Pop_stack2();
		if (parent->left != NULL && (parent->left)->data == key) parent->left = NULL;
		else parent->right = NULL;
		root = NULL;
	}	
	else if (root->left == NULL && root->right != NULL) {

		parent = Pop_stack2();
		if (parent->left != NULL && (parent->left)->data == key) parent->left = root->right;
		else parent->right = root->right;
		root = NULL;
	}
	else if (root->right == NULL && root->left != NULL) {

		parent = Pop_stack2();
		if (parent->left != NULL && (parent->left)->data == key) parent->left = root->left;
		else parent->right = root->left;
		root = NULL;
	}
	else {
		
		node* temp;
		temp = root->right;

		while (temp->left != NULL) {

			Push_stack2(temp);
			temp = temp->left;
		}

		root->data = temp->data;

		if (temp->right != NULL) {

			parent = Pop_stack2();
			parent->left = temp->right;
			temp = NULL;
		}
		else temp = NULL;
	}
	printf("%d deleted\n", key);
	Update(Tree_root);
	Balance_tree();
	counter1 = 0;
	counter2 = 0;
}

void Preorder (node* root) {

	if (root == NULL) return;
	
	else {
	
		printf("%d ", root->data);
		Preorder(root->left);
		Preorder(root->right);
	}
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

	printf("Preorder of original AVL tree :\n");
	Preorder(Tree_root);
	printf("\n");
	Insert(Tree_root, 15);
	Insert(Tree_root, 78);
	Insert(Tree_root, 89);
	Insert(Tree_root, 45);
	Insert(Tree_root, 32);
	Insert(Tree_root, 21);
	printf("Preorder of AVL tree after insertion:\n");
	Preorder(Tree_root);
	printf("\n");
	Delete(Tree_root, 5);
	Delete(Tree_root, 78);
	Delete(Tree_root, 69);
	Delete(Tree_root, 21);
	//Delete(Tree_root, Tree_root->data);
	printf("Preorder of AVL tree after deletion:\n");
	Preorder(Tree_root);
	printf("\n");
	return 0;
}

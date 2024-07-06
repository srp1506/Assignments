typedef struct node {

	int data;
	struct node* left;
	struct node* right;
	int height;
}node;

#include"Header.h"

node* Create_node(int val) {

	node* new = (node*)malloc(sizeof(node));
	new->data = val;
	new->left = NULL;
	new->right = NULL;
	new->height = 0;
	return new;
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
	
	return root->height;
}

void Balance_node(node* root) {

	int balance;
	int rheight;
	int lheight;		
	rheight = (root->right != NULL ? (root->right)->height : -1);
	lheight = (root->left != NULL ? (root->left)->height : -1);
	balance = rheight - lheight;

	if (balance == -2) {
		
		rheight = (root->left->right != NULL ? (root->left->right)->height : -1);
		lheight = (root->left->left != NULL ? (root->left->left)->height : -1);
		balance = rheight - lheight;
		
		if (balance < 0) Right_rotation(root);
		else {
			Push_stack1(root);
			Left_rotation(root->left);
			Right_rotation(root);
		}
	}
	else if (balance == 2) {
		
		rheight = (root->right->right != NULL ? (root->right->right)->height : -1);
		lheight = (root->right->left != NULL ? (root->right->left)->height : -1);
		balance = rheight - lheight;
		
		if (balance > 0) Left_rotation(root);
		else {
			Push_stack1(root);
			Right_rotation(root->right);
			Left_rotation(root);
		}
	}
	else return;
}

node* Search(node* root, int key) {

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

int Insert(node* root, int key) {

	if (Tree_root == NULL) {
		
		Tree_root = Create_node(key);
		return 1;
	}

	if (Search(root, key) != NULL) return 0;

	while (root->left != NULL || root->right != NULL) {

		Push_stack1(root);
		
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
	Update(Tree_root);
	
	while (counter1) {
		
		root = Pop_stack1();
		Update(Tree_root);
		Balance_node(root);
	}
	
	counter1 = 0;
	return 1;
}

int Delete(node* root, int key) {
	
	if (Search(root, key) == NULL) return 0;

	node* parent;

	while (root->data != key) {

		Push_stack1(root);
		Push_stack2(root);
		
		if (root->data > key) {

			if (root->left != NULL) root = root->left;
			else break;
		}
		else {

			if (root->right != NULL) root = root->right;
			else break;
		}
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
		Push_stack2(root);

		while (temp->left != NULL) {

			Push_stack2(temp);
			temp = temp->left;
		}

		root->data = temp->data;
		parent = Pop_stack2();
		
		if (parent != NULL) {
			
			if (temp->right != NULL) {
				
				if (parent->left == temp) parent->left = temp->right;
				else parent->right = temp->right;
			}

			if (parent->left == temp) parent->left = NULL;
			else if (parent->right == temp) parent->right = NULL;
		}
		temp = NULL;
	}
	
	Update(Tree_root);

	while (counter1) {
		
		root = Pop_stack1();
		Update(Tree_root);
		Balance_node(root);
	}
	
	counter1 = 0;
	counter2 = 0;
	return 1;
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
	head = 0;
	tail = 0;
}

int main (int argc, char *argv[]) {
	
	int size;
	int val;
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

	while(1) {

		int query;
		int val;
		scanf("%d", &query);
		query == 4 ? BFS(Tree_root) : scanf("%d", &val);
		
		switch (query) {
		
			case 1 :
				printf(Search(Tree_root, val) == NULL ? "%d not present\n" : "%d present\n", val);
				break;
			case 2 :
				printf(Insert(Tree_root, val) == 0 ? "%d already present. So no need to insert\n" : "%d inserted\n", val);
				break;
			case 3 :
				printf(Delete(Tree_root, val) == 0 ? "%d not present. So it cannot be deleted\n" : "%d deleted\n", val);
				break;
			case 4 :
				break;
			default :
				printf("Unidentified Query\n");
				exit(0);	
		}
	}
	return 0;
}

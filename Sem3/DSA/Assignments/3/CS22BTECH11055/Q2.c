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

void Delete_fix(node*, node*);

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

node* Successor(node* root) {

    while (root->left != NULL) root = root->left;
    return root;
}

void Transplant(node* a, node* b) {

	if (a->parent == NULL) Tree_root = b;
	else if (a == a->parent->left) a->parent->left = b;
	else a->parent->right = b;
	b->parent = a->parent;
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

void Case_1(node* a, node* b) {

    if (b->left == NULL && b->right == NULL) {
        //both null
        a->color = 0;
        b->color = 1;
    }
    else if (b->left == NULL) {
        //left is null
        Left_rotation(b);
        Right_rotation(a);

        a->color = 0;
    }
    else if (b->right == NULL) {
        //right is null
        node* c = b->left;
        Right_rotation(a);

        b->color = 1;
        a->color = c->color = 0;
    }
    else{

        if (b->left->color == 0 && b->right->color == 0) {
            //both black
            a->color = 0;
            b->color = 1;
        }
        else if (b->left->color == 0) {
            //left is black
            Left_rotation(b);
            Right_rotation(a);

            a->color = 0;
        }
        else{
            //right is black or both red
            node* c = b->left;
            Right_rotation(a);

            b->color = 1;
            a->color = c->color = 0;
        }
    }
}

void Mirror_case_1(node* a, node* b) {

    if (b->right == NULL && b->left == NULL) {
        //both null
        a->color = 0;
        b->color = 1;
    }
    else if (b->right == NULL) {
        //right is null
        Right_rotation(b);
        Left_rotation(a);

        a->color = 0;
    }
    else if (b->left == NULL) {
        //left is null
        node* c = b->right;
        Left_rotation(a);

        b->color = 1;
        a->color = c->color = 0;
    }
    else{

        if (b->right->color == 0 && b->left->color == 0) {
            //both black
            a->color = 0;
            b->color = 1;
        }
        else if (b->right->color == 0) {
            //right is black
            Right_rotation(b);
            Left_rotation(a);

            a->color = 0;
        }
        else{
            //left is black or both red
            node* c = b->right;
            Left_rotation(a);

            b->color = 1;
            a->color = c->color = 0;
        }
    }
}

void Case_2_1(node* a, node* b, node* c) {

    if (c->left == NULL && c->right == NULL) {
        //both null
        Right_rotation(a);

        b->color = 0;
        c->color = 1;
    }
    else if (c->left == NULL) {
        //left is null
        node* d = c->right;
        Right_rotation(a);
        Right_rotation(a);
        Right_rotation(a);
        Left_rotation(c);
        Left_rotation(b);
        
        d->color = 0;
    }
    else if (c->right == NULL) {
        //right is null
        node* d = c->left;
        Left_rotation(b);
        Right_rotation(a);

        d->color = 0;
    }
    else{

        if (c->left->color == 0 && c->right->color == 0) {
            //both black
            Right_rotation(a);

            b->color = 0;
            c->color = 1;
        }
        else if (c->left->color == 0) {
            //left is black
            node* d = c->right;
            Right_rotation(a);
            Right_rotation(a);
            Right_rotation(a);
            Left_rotation(c);
            Left_rotation(b);
            
            d->color = 0;
        }
        else{
            //right is black or both red
            node* d = c->left;
            Left_rotation(b);
            Right_rotation(a);

            d->color = 0;
        }
    }
}

void Mirror_case2_1(node* a, node* b, node* c) {

    if (c->right == NULL && c->left == NULL) {
        //both null
        Left_rotation(a);

        b->color = 0;
        c->color = 1;
    }
    else if (c->right == NULL) {
        //right is null
        node* d = c->left;
        Left_rotation(a);
        Left_rotation(a);
        Left_rotation(a);
        Right_rotation(c);
        Right_rotation(b);
        
        d->color = 0;
    }
    else if (c->left == NULL) {
        //left is null
        node* d = c->right;
        Right_rotation(b);
        Left_rotation(a);

        d->color = 0;
    }
    else{

        if (c->right->color == 0 && c->left->color == 0) {
            //both black
            Left_rotation(a);

            b->color = 0;
            c->color = 1;
        }
        else if (c->right->color == 0) {
            //right is black
            node* d = c->left;
            Left_rotation(a);
            Left_rotation(a);
            Left_rotation(a);
            Right_rotation(c);
            Right_rotation(b);
            
            d->color = 0;
        }
        else{
            //left is black or both red
            node* d = c->right;
            Right_rotation(b);
            Left_rotation(a);

            d->color = 0;
        }
    }
}

void Case_2_2(node* a, node* b) {

    if (b->left == NULL && b->right == NULL) {
        //both null
        b->color = 1;

        Delete_fix(a->parent, a);
    }
    else if (b->left == NULL) {
        //left is null
        node* c = b->right;
        Left_rotation(b);
        Right_rotation(a);

        c->color = 0;
    }
    else if (b->right == NULL) {
        //right is null
        node* c = b->left;
        Right_rotation(a);

        c->color = 0;
    }
    else{

        if (b->left->color == 0 && b->right->color == 0) {
            //both black
            b->color = 1;

            Delete_fix(a->parent, a);
        }
        else if (b->left->color == 0) {
            //left is black
            node* c = b->right;
            Left_rotation(b);
            Right_rotation(a);

            c->color = 0;
        }
        else{
            //right is black or both red
            node* c = b->left;
            Right_rotation(a);

            c->color = 0;
        }
    }
}

void Mirror_case_2_2(node* a, node* b) {

    if (b->right == NULL && b->left == NULL) {
        //both null
        b->color = 1;

        Delete_fix(a->parent, a);
    }
    else if (b->right == NULL) {
        //right is null
        node* c = b->left;
        Right_rotation(b);
        Left_rotation(a);

        c->color = 0;
    }
    else if (b->left == NULL) {
        //left is null
        node* c = b->right;
        Left_rotation(a);

        c->color = 0;
    }
    else{

        if (b->right->color == 0 && b->left->color == 0) {
            //both black
            b->color = 1;

            Delete_fix(a->parent, a);
        }
        else if (b->right->color == 0) {
            //right is black
            node* c = b->left;
            Right_rotation(b);
            Left_rotation(a);

            c->color = 0;
        }
        else{
            //left is black or both red
            node* c = b->right;
            Left_rotation(a);

            c->color = 0;
        }
    }
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

void Delete_fix(node* parent, node* heightReducedSubtree){
   
    if (parent == NULL) return;
    
    node* a = parent;

    if (a->right == heightReducedSubtree) {//right subtrees height was reduced
        
        node* b = a->left;

        if (a->color == 1) {//a is red 
            //b will be black
            Case_1(a, b);
        }
        else {//a is black

            if (b->color == 1) {//b is red 
                
                node* c = b->right;
                Case_2_1(a, b, c);
            }
            else Case_2_2(a, b);
        }
    }
    else {//left subtree height reduced
        
        node* b = a->right;

        if (a->color == 1) {
            //b will be black
            Mirror_case_1(a, b);
        }
        else {
            
            if (b->color == 1) {//b is red 
                
                node* c = b->left;
                Mirror_case2_1(a, b, c);
            }
            else Mirror_case_2_2(a, b);
        }
    }
}

void Delete_leaf(node* toBeDeleted) {

    int deletedColor = toBeDeleted->color;

    node* parent = toBeDeleted->parent;
    node* heightReducedSubtree = toBeDeleted->right;

    if (toBeDeleted->parent->left == toBeDeleted) {//if deleting node is left child
        
        toBeDeleted->parent->left = NULL;
    }
    else {
        //if it was right child
        toBeDeleted->parent->right = NULL;
    }
    free(toBeDeleted);
    
    if (parent == NULL) {//deleted root with no child
        
        Tree_root = NULL;
        return;
    }

    if ( deletedColor == 0) {
        //need to balance
        Delete_fix(parent, heightReducedSubtree);
    }
}

int Insert(node* root, int key) {

	if (Tree_root == NULL) {

			Tree_root = Create_node(key);
			Tree_root->color = 0;
			return 1;
	}
	
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

// int Delete(node* root, int key) {


// 	if (Search(root, key) == NULL) return 0;

// 	node* parent;

// 	while (root->data != key) {


// 		if (root->data > key) {

// 			if (root->left != NULL) root = root->left;
// 			else break;
// 		}
// 		else {

// 			if (root->right != NULL) root = root->right;
// 			else break;
// 		}
// 	}

// 	parent = root->parent;
	
// 	if (root->left == NULL && root->right == NULL) {
		
// 		if (parent->left != NULL && (parent->left)->data == key) parent->left = NULL;
// 		else parent->right = NULL;
		
// 		root = NULL;
// 	}	
// 	else if (root->left == NULL && root->right != NULL) {
		
// 		if (parent->left != NULL && (parent->left)->data == key) parent->left = root->right;
// 		else parent->right = root->right;
		
// 		root = NULL;
// 	}
// 	else if (root->right == NULL && root->left != NULL) {
		
// 		if (parent->left != NULL && (parent->left)->data == key) parent->left = root->left;
// 		else parent->right = root->left;
		
// 		root = NULL;
// 	}
// 	else {
		
// 		node* temp;
// 		temp = root->right;

// 		while (temp->left != NULL) temp = temp->left;

// 		root->data = temp->data;
// 		parent = temp->parent;
		
// 		if (parent != NULL) {
			
// 			if (temp->right != NULL) {
				
// 				if (parent->left == temp) parent->left = temp->right;
// 				else parent->right = temp->right;
// 			}

// 			if (parent->left == temp) parent->left = NULL;
// 			else parent->right = NULL;
// 		}
// 		temp = NULL;
// 	}
// 	Delete_fix(Tree_root);
// 	return 1;
// }

int Delete(node* root, int key) {
    
    Tree_root = root;

    node *toBeDeleted;

    toBeDeleted = Search(root, key);

    if (toBeDeleted == NULL) return 0;

    if (toBeDeleted->left != NULL && toBeDeleted->right != NULL) {//has both children
        //find succesor
        node *newToBeDeleted = Successor(toBeDeleted->right);//find succesor of z
        toBeDeleted->data = newToBeDeleted->data;//store value of succesor to prev Delete candidate

        toBeDeleted = newToBeDeleted;//store address of new Delete candidate
    }

    if (toBeDeleted->left == NULL && toBeDeleted->right == NULL) {//leaf node
       
        Delete_leaf(toBeDeleted);
    }
    else {//when only has one child(as we got succesor in case 2 child)
        
        if (toBeDeleted->left != NULL) {//left child is non NULL
            
            toBeDeleted->data = toBeDeleted->left->data;
            free(toBeDeleted->left);
            toBeDeleted->left = NULL;
        }
        else {
            
            toBeDeleted->data = toBeDeleted->right->data;
            free(toBeDeleted->right);
            toBeDeleted->right = NULL;
        }
    }
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
			printf(temp->color == 1 ? "%dr " : "%db ", temp->data);
			Dequeue(queue);
			
			if (temp->left != NULL) Enqueue(queue, temp->left);
			if (temp->right != NULL) Enqueue(queue, temp->right);
			
			count--;
		}
		printf("\n");
	}
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

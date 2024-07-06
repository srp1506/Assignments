#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<ctype.h>
#include<math.h>
#include<unistd.h>

#define degree 2
#define MAX 3
#define MIN 1

typedef struct node {
	
	int key[MAX + 1];
	int count;
	struct node* children[MAX + 1];
}node;

node* Tree_root;

node* Create_node() {

	node* new = (node*)malloc(sizeof(node));
	
	for (int i = 0 ; i < MAX + 1 ; i++) {
		
		new->key[i] = 0;
		new->children[i] = NULL;
		
	}
	
	new->count = 0;
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

int Leaf(node* root) {
	
	for (int i = 0 ; i < root->count ; i += 1) if (root->children[i] != NULL) return 0;
	
	return 1;
}

int Predecessor(node* root) {

	while (!Leaf(root)) root = root->children[root->count];

	return root->key[root->count - 1];
}

int Successor(node* root) {

	while (!Leaf(root)) root = root->children[0];

	return root->key[0];
}

void Split_child(node* root, int pos) {
    
	node* sibling1 = root->children[pos];
    node* sibling2 = Create_node();
    sibling2->count = MIN;

    for (int i = 0 ; i < MIN ; i += 1) sibling2->key[i] = sibling1->key[i + degree];
    

    if (!Leaf(sibling1)) for (int i = 0 ; i < degree ; i += 1) sibling2->children[i] = sibling1->children[i + degree];

    sibling1->count = MIN;

    for (int i = root->count ; i > pos ; i -= 1) root->children[i + 1] = root->children[i];

    root->children[pos + 1] = sibling2;

    for (int i = root->count - 1 ; i >= pos ; i -= 1) root->key[i + 1] = root->key[i];

    root->key[pos] = sibling1->key[MIN];
    root->count++;
}

node* Split_root() {
	
	node* root;
	root = Create_node();
	root->children[0] = Tree_root;
	Tree_root = root;
	Split_child(root, 0);
	return root;
}

node* Search(node* root, int key) {
	
	int i;
	i = 0;
	
	while (i < root->count && key > root->key[i]) i++;
	
	if (i < root->count && key == root->key[i]) return root;
	else if (Leaf(root)) return NULL;
	else return Search(root->children[i], key);
}

void Insert_Actual(node* root, int key) {
	
	int i;
	i = root->count;
	
	if (Leaf(root)) {
		
		while (i > 0 && key < root->key[i - 1]) {
			
			root->key[i] = root->key[i - 1];
			i--;
		}
		
		root->key[i] = key;
		root->count++;
	}
	else {
		
		while (i > 0 && key < root->key[i - 1]) i--;
		
		if (root->children[i]->count == MAX) {
			
			Split_child(root, i);
			
			if (key > root->key[i]) i++;
		}
		Insert_Actual(root->children[i], key);
	}
}

int Insert(node* root, int key) {
	
	if (Search(root, key) != NULL) return 0;
	
	if (root->count == MAX) {
		
		node* temp;
		temp = Split_root();
		Insert_Actual(temp, key);
	}
	else Insert_Actual(root, key);
	
	return 1;
}

int Delete(node* root, int key) {

	int i;
	i = 0;

	while (i < root->count && key > root->key[i]) i++;

	if (i < root->count && key == root->key[i] ) {

		if (Leaf(root)) {
			
				while (i < root->count - 1) {
					
					root->key[i] = root->key[i+1];
					i++;
				}

				root->count--;
		}
		else {
			
			node* prev = root->children[i];
			node* next = root->children[i + 1];

			if (prev->count >= degree) {
				
				int pre;
				pre = Predecessor(prev);
				Delete(Tree_root, pre);
				root->key[i] = pre;
			}
			else {

				if (next->count >= degree) {

					int succ;
					succ = Successor(next);
					Delete(Tree_root, succ);
					root->key[i] = succ;
				}
				else {
					
					prev->key[prev->count++] = root->key[i];

					int j;
					j = 0;

					while (j < next->count)	prev->key[prev->count++] = next->key[j++];
					
					while (i < root->count - 1) {

						root->key[i] = root->key[i + 1];
						root->children[i + 1] = root->children[i + 2];
						i++;
					}

					root->count--;
					free(next);
					Delete(prev, key);
				}
			}
		}
	}
	else {

		node* current = root->children[i];
		node* prev = i > 0 ? root->children[i - 1] : NULL;
		node* next = i < MAX ? root->children[i + 1] : NULL;

		if (current->count == MIN) {

			if ((prev != NULL && prev->count >= degree) || (next != NULL && next->count >= degree)) {

				if (prev != NULL && prev->count >= degree) {

					int k;
					k = MIN - 1;

					while (k >= 0) {

						current->key[k + 1] = current->key[k];
						current->children[k + 2] = current->children[k + 1];
						k--;
					}
					current->children[1] = current->children[0];
					current->key[0] = root->key[i - 1];
					current->children[0] = prev->children[prev->count];
					root->key[i - 1] = prev->key[prev->count - 1];
					current->count++;
					prev->count--;
				}
				else {

					int k;
					k = 0;
					current->key[MIN] = root->key[i];
					current->children[MIN + 1] = next->children[0];
					root->key[i] = next->key[0];

					while (k < next->count - 1) {
						
						next->key[k] = next->key[k + 1];
						next->children[k] = next->children[k + 1];
						k++;
					}
					next->children[k] = next->children[k + 1];
					current->count++;
					next->count--;
				}
				
			}
			else {

				if (prev != NULL) {
					
					prev->key[MIN] = root->key[i - 1];

					int k;
					k = 0;

					while (k < MIN) {

						prev->key[k + MIN + 1] = current->key[k];
						k++;
					}

					while (i < root->count) {

						root->key[i - 1] = root->key[i];
						root->children[i] = root->children[i + 1];
						i++;
					}
					root->count--;
					prev->count = MAX;
				}
				else {
					
					current->key[MIN] = root->key[i];

					int k;
					k = 0;

					while (k < MIN) {

						current->key[k + MIN + 1] = next->key[k];
						k++;
					}

					while (i < root->count - 1) {

						root->key[i] = root->key[i + 1];
						root->children[i + 1] = root->children[i + 2];
						i++;
					}
					root->count--;
					current->count = MAX;
				}
			}
			Delete(Tree_root, key);
		}
		else Delete(current, key);
	}

	if (Tree_root->count == 0) Tree_root = Tree_root->children[0];

	return 1;
}

void BFS(struct node* root) {

    if(root == NULL) return;

    Enqueue(queue, root);

    int lvl = 0;

    while(!Check_empty(queue)) {
     
        int count = Size();

        printf("Level %d : ", lvl);
        
        while(count > 0) {

            node* temp = Peek(queue);
            for (int i = 0 ; i < temp->count ; i++) printf("%d ",temp->key[i]);
            
            printf("   ");
            Dequeue(queue);
            
			for( int i = 0 ; i <= temp->count ; i++) if (temp->children[i] != NULL) Enqueue(queue, temp->children[i]);
            count--;
        }
        lvl++;
        printf("\n");
    }
    Clear_queue();
}

int main (int argc, char *argv[]) {
	
	int size;
	int val;
	scanf("%d", &size);
	
	if (size <= 0) {
	
		printf("Invalid size\n");
		exit(0);
	}
	
	Tree_root = Create_node();
	
	for (int i = 0 ; i < size ; i++) {

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


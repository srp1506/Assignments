#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int base = 13;

// Define a node structure for the singly linked list
typedef struct node {

	int data;
	struct node* next;
}node;

// Initialize a new node with the given data
node* Init_node (int data) {

	node* new = (node*)malloc(sizeof(node));
	new->data = data;
	new->next = NULL;
	return new;
}

// Insert a key into a set represented as an array of singly linked lists
void Insert (int key, node** set) {

	int pos;
	pos = key % base;
	node* new = Init_node(key);
	node* trav;
	node* prev;
	trav = set[pos];
	prev = NULL;

    	// Check if the key is already in the set
	while (trav != NULL) {

		if (trav->data == key) {

			free(new);
			return;
		}

		prev = trav;
		trav = trav->next;
	}
	
	if (prev == NULL) set[pos] = new;
	
	else prev->next = new;
}

// Perform the intersection operation on two sets
void Intersection (node** set1, node** set2) {

	for (int i = 0 ; i < base ; i++) {

		if (set1[i] == NULL) continue;

		node* trav1;
		node* prev1;
		prev1 = NULL;
		node* trav2;
		node* prev2;
		prev2 = NULL;
		node* temp;
		trav1 = set1[i];

		while (trav1 != NULL) {

			int key;
			int pos;
			int found;
			found = 0;
			key = trav1->data;
			pos = key % base;

			if (set2[pos] == NULL) {

				if (prev1 == NULL) set1[i] = trav1->next;

				else prev1->next = trav1->next;

				temp = trav1;
				trav1 = trav1->next;
				free(temp);
				continue;
			}

			else {

				trav2 = set2[pos];

				while (trav2 != NULL) {

					if (trav2->data == key) {

						found = 1;
                    				// Remove the element from set2
						if (prev2 == NULL) set2[pos] = trav2->next;

						else prev2->next = trav2->next;

						temp = trav2;
						trav2 = trav2->next;
						free(temp);
						break;
					}
					prev2 = trav2;

					if (trav2 != NULL) trav2 = trav2->next;
				}

				if (found == 0) {
                			// Remove the element from set1
					if (prev1 == NULL) set1[i] = trav1->next;

					else prev1->next = trav1->next;

					temp = trav1;
					trav1 = trav1->next;
					free(temp);
				}

				else {

					prev1 = trav1;
					if (trav1 != NULL) trav1 = trav1->next;
				}
			}
		}
	}
}

// Print the elements in a set represented as an array of singly linked lists
void Print_set (node** set) {

	for (int i = 0 ; i < base ; i++) {

		node* current;
		current	= set[i];

		if (current == NULL) 0;

		else {
			while (current != NULL) {

				printf("%d\n", current->data);
				current = current->next;
			}

		}
	}
	printf("\n");
}


int main() {

	node* set1[base];
	node* set2[base];

    	// Initialize the sets
	for (int i = 0 ; i < base ; i++) {

		set1[i] = NULL;
		set2[i] = NULL;
	}

	int size; // Size of the set
	printf("Enter the number of elements in set1 :\n");
	scanf("%d", &size);
	
	if (size <= 0) {
	
		printf("Enter valid input size\n");
		return 1;
	}
	
	printf("Inputs :\n");

	for (int i = 0 ; i < size ; i++) {

		int val;
		scanf("%d", &val);
		Insert(val, set1);
	}

	printf("Enter the number of elements in set2 :\n");
	scanf("%d", &size);
	
	if (size <= 0) {
	
		printf("Enter valid input size\n");
		return 1;
	}
	
	printf("Inputs :\n");

	for (int i = 0 ; i < size ; i++) {

		int val;
		scanf("%d", &val);
		Insert(val, set2);
	}
	printf("Set1 before intersection :\n");
	Print_set(set1);
	printf("Set2 before intersection :\n");
	Print_set(set2);
	printf("\nIntersection Set :\n");
	Intersection(set1, set2);	
	Print_set(set1);
	return 0;
}

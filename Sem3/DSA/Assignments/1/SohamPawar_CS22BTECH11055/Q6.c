#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdint.h>

// Define a node structure for the doubly linked list
typedef struct node {

	int data;
	struct node* np; // XOR pointer
}node;

// XOR operation to combine pointers
node* XOR (node* next, node* prev) {

	return (node*)((uintptr_t)next ^ (uintptr_t)prev);
}

// Initialize an empty doubly linked list and return the head
node* Init_list () {

	node* head = (node*)malloc(sizeof(node));
	head->np = NULL;
	return head;
}

// Insert a new node with the given value
node* Insert (int val, node* head) {

	node* new = (node*)malloc(sizeof(node));
	new->data = val;

	if (head->np == NULL) {

		// If the list is empty, set the XOR pointer to itself
		head->np = XOR(NULL, new);
		new->np = XOR(head, NULL);
	}

	else {
		// Traverse the list to find the last node
		node* trav1;
		node* trav2;
		trav1 = head;
		trav2 = NULL;

		while (trav1->np != trav2) {

			node* temp;
			temp = XOR(trav1->np, trav2);
			trav2 = trav1;
			trav1 = temp;
		}

		// Set the XOR pointers to insert the new node
		trav1->np = XOR(trav2, new);
		new->np = XOR(trav1, NULL);
	}	
	return new;
}

// Search for a value in the list
int Search (int val, node* head) {

	if (head->np == NULL) return 0; 

	else {
		// Traverse the list to find the value
		node* trav1;
		node* trav2;
		trav1 = head;
		trav2 = NULL;

		while (trav1->np != trav2) {

			node* temp;
			temp = XOR(trav1->np, trav2);
			trav2 = trav1;
			trav1 = temp;

			if (trav1->data == val) return 1; // Found
		}

		return 0; // Not found
	}
}

// Delete a node with the given value
int Delete (int val, node* head, node** tail) {

	if (head->np == NULL) {

		printf("Empty List\n");
		exit(0); 
	}

	else {
		// Traverse the list to find and delete the node
		node* trav1;
		node* trav2;
		trav1 = head;
		trav2 = NULL;

		while (trav1->np != trav2) {

			node* temp;
			temp = XOR(trav1->np, trav2);
			trav2 = trav1;
			trav1 = temp;

			if (trav1->data == val) {

				int data;
				data = trav1->data;

				if (trav1->np == head) {

					printf("\n%d Deleted\n", data);
					head->np = NULL;
					free(trav1);
					return 1;
				}

				node* temp1;
				node* temp2;

				temp1 = XOR(trav1->np, trav2);
				temp2 = XOR(trav2->np, trav1);
				trav2->np = XOR(temp1, temp2);

				if (temp1 != NULL) temp1->np = XOR(trav2, XOR(temp1->np, trav1));

				if (temp2 != NULL) temp2->np = XOR(trav2, XOR(temp2->np, trav2));

				printf("\n%d Deleted\n", data);

				if (trav1 == *tail) *tail = trav2;

				free(trav1);
				return 1;
			}
		}
		printf("\n%d absent from the list\n", val);
		return 0;
	}
}

// Reverse the doubly linked list
void Reverse (node* head, node* tail) {

	if(head->np == NULL) exit(0);

	if (head->np == tail) return; // List is empty or has only one node

	// Swap the head and tail pointers to reverse the list
	node* first;
	first = head->np;
	first->np = XOR(NULL, XOR(first->np, head));
	tail->np = XOR(head, tail->np);
	head->np = tail;
	tail = first;
}

// Print the elements in the doubly linked list
void Print_list (node* head) {

	if (head->np == NULL) {

		printf("Empty List\n");
		return;
	}

	else {
		// Traverse and print the list
		node* trav1;
		node* trav2;
		trav1 = head;
		trav2 = NULL;

		while (trav1->np != trav2) {

			node* temp;
			temp = XOR(trav1->np, trav2);
			trav2 = trav1;
			trav1 = temp;
			printf("%d\n", trav1->data);
		}
		printf("\n");
	}
}

int main() {

	int size; // Size of the XOR list
	node* head = Init_list();
	node* tail = NULL;
	printf("Enter the number of elements in the list :\n");
	scanf("%d", &size);

	if (size <= 0) {

		printf("Enter valid input size\n");
		return 1;
	}

	printf("Elements :\n");

	for (int i = 0 ; i < size ; i++) {

		int val;
		scanf("%d", &val);
		tail = Insert(val, head);
	}

	Delete(15, head, &tail);
	printf("\nList :\n");
	Print_list(head);
	Reverse(head, tail);
	printf("\nReversed List :\n");
	Print_list(head);
}

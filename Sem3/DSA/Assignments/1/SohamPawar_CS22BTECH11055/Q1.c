#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Define a node structure for the singly linked list
typedef struct node {

	struct node* next;
	int data;
}node;

// Initialize an empty linked list and return the head
node* Init_List () {

	node* head = (node*)malloc(sizeof(node));
	head->data = -1;
	head->next = NULL;
	return head;
}

// Add a new node with the given value to the end of the list
void Add (int val, node* head) {

	node* trav;
	trav = head;
	
	while (trav->next != NULL) trav = trav->next;

	node* new = (node*)malloc(sizeof(node));
	trav->next = new;
	new->data = val;
	new->next = NULL;
}

// Reorder the linked list
void Reorder (node* head) {

	node* trav1;
	node* trav2;
	node* temp1;
	node* temp2;
	node* head2;

	if (head->next == NULL) return;

	trav1 = head->next;
	temp1 = trav1;

	if ((head->next)->next == NULL) return ;

	trav2 = (head->next)->next;
	temp2 = trav2;
	head2 = trav2;

	while (trav1->next != NULL && trav2->next != NULL) {
	
		trav1 = trav2->next;
		temp1->next = trav1;
		temp1 = trav1;
		trav2 = trav1->next;
		temp2->next = trav2;
		temp2 = trav2;
	}

	trav1->next = head2;
}

// Print the linked list
void Print_List (node* head) {

	node* trav;
	trav = head;
	
	if (head->next == NULL) return;
	
	trav = trav->next;
	printf("\n");

	while (trav->next != NULL) {
		
		printf("%d\n",trav->data);
		trav = trav->next;
	}

	printf("%d\n",trav->data);
}

// Free the memory allocated for the linked list
void Free_List (node* head) {

	node* trav;
	trav = head;
	
	while (trav->next != NULL) {
	
		node* current;
		current = trav;
		trav = trav->next;
		free(current);
	}
	
	free(trav);
}

int main() {

	node* head;
	head = Init_List();
	int size; // Size of the linked list
	printf("Enter the number of inputs in the linked list : ");
	scanf("%d", &size);
	
	if (size <= 0) {
	
		printf("Enter valid input size\n");
		return 1;
	}
	
	printf("Enter the elements of the list :\n");
	
	for (int i = 0 ; i < size ; i++) {
		
		int val;
		scanf("%d", &val);
		Add(val, head);
	}
	
	Reorder(head);
	printf("\nReordered list :");
	Print_List(head);
	printf("\n");
	Free_List(head);
	return 0;
}

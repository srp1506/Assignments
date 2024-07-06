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

// Check if the linked list is a palindrome by reversing half the list and comparing it with the remaining half 
int Pal_Check (node* head, int size) {

	if (size == 0) return 1;

	node* trav1;
	node* trav2;
	node* temp;

	if (head->next == NULL) return 0;

	trav1 = head->next;

	if ((head->next)->next == NULL) return 0;

	trav2 = (head->next)->next;

	for (int i = 1 ; i < size / 2 ; i++) {
	
		temp = trav2;
		trav2 = trav2->next;
		temp->next = trav1;
		trav1 = temp;
	}
	
	if (trav1->data != trav2->data) return 0;	
	
	while (trav2->next != NULL && trav2 != NULL) {
	
		if (trav1->data != trav2->data) return 0;
		trav1 = trav1->next;
		trav2 = trav2->next;
	}

	return 1;
}

int main() {

	node* head;
	head = Init_List();
	int size; // Size of the linkd list
	int n;
	printf("Enter the number of inputs in the linked list : ");
	scanf("%d", &size);
	
	if (size <= 0) {
	
		printf("Enter valid input size\n");
		return 1;
	}

	n = size;
	printf("Enter the elements of the list :\n");
	
	for (int i = 0 ; i < n ; i++) {
	
		int val;
		scanf("%d", &val);
		
		// If the size is odd, skip adding the middle element to the list
		if (size % 2 == 1 && i == (size - 1) / 2) {
		
			size--;
			continue;
		}
			Add(val, head);
	}
	
	Pal_Check(head, size) == 1 ? printf("True\n") : printf("False\n");	
	return 0;
}

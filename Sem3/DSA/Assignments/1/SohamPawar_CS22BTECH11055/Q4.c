#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Define a node structure for the circular linked list
typedef struct node {

	struct node* next;
	int data;
}node;

// Initialize an empty circular linked list and return the head
node* Init_List() {

	node* head = (node*)malloc(sizeof(node));
	head->data = -1;
	head->next = head;
	return head;
}

// Add a new node with the given value to the end of the circular list
void Add (int val, node* head) {

	node* trav;
	trav = head;

	while (trav->next != head) trav = trav->next;

	node* new = (node*)malloc(sizeof(node));
	trav->next = new;
	new->data = val;
	new->next = head; // Maintaining circular behaviour
}

// Perform the union operation by connecting the second list to the end of the first list
void Union (node* head1, node* head2) {

	node* temp1;
	node* temp2;

	if (head1->next == head1) return;

	temp1 = head1->next;

	if (head2->next == head2) return;

	temp2 = head2->next;

	head1->next = temp2;
	head2->next = temp1;
}

// Print the elements in the circular linked list
void Print_List (node* head) {

	node* trav;
	trav = head;
	printf("\n");

	if (head->next == head) return;

	trav = trav->next;
	printf("\n");

	while (trav->next != head && trav != head) {

		if (trav->data != -1) printf("%d\n",trav->data);
		trav = trav->next;
	}

	printf("%d\n",trav->data);
}

int main() {

	node* head1;
	node* head2;
	head1 = Init_List();
	head2 = Init_List();
	int size; // Size of the circular linked list
	printf("Enter the number of inputs in the first linked list : ");
	scanf("%d", &size);
	
	if (size <= 0) {
	
		printf("Enter valid input size\n");
		return 1;
	}
	
	printf("Enter the elements of the first list :\n");

	for (int i = 0 ; i < size ; i++) {

		int val;
		scanf("%d", &val);
		Add(val, head1);
	}

	printf("Enter the number of inputs in the second linked list : ");
	scanf("%d", &size);
	
	if (size <= 0) {
	
		printf("Enter valid input size\n");
		return 1;
	}
	
	printf("Enter the elements of the second list :\n");

	for (int i = 0 ; i < size ; i++) {

		int val;
		scanf("%d", &val);
		Add(val, head2);
	}

	Union(head1, head2);
	printf("\nSet Union : ");
	Print_List(head1);
	return 0;
}

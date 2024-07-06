#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Define a node structure for the singly linked list
typedef struct node {

	int data;
	struct node* next;
}node;

// Function to initialize an empty set and return the head
node* Init_list () {

	node* head = (node*)malloc(sizeof(node));
	head->next = NULL;
	return head;
}

// Function to insert an element into the set if it doesn't exist already
void Insert (int val, node* head) {

	node* trav;
	node* new = (node*)malloc(sizeof(node));
	new->data = val;
	new->next = NULL;
	trav = head;

	while (trav->next != NULL) {
		
		trav = trav->next;
		if (trav->data == val) {

			free(new);
			return; // Element already exists in the set
		}
	}

	trav->next = new;
}

// Function to merge two sorted linked lists into one sorted linked list
node* Merge (node* node1, node* node2) {

	node* merged = (node*)malloc(sizeof(node));
	node* temp = (node*)malloc(sizeof(node));
	merged = temp;

	while (node1 != NULL && node2 != NULL) {

		if (node1->data <= node2->data) {

			temp->next = node1;
			node1 = node1->next;
		}

		else {

			temp->next = node2;
			node2 = node2->next;
		}
		temp = temp->next;
	}
	while (node1 != NULL) {
		temp->next = node1;
		node1 = node1->next;
		temp = temp->next;
	}

	while (node2 != NULL) {
		temp->next = node2;
		node2 = node2->next;
		temp = temp->next;
	}
	return merged->next;
}

// Function to find the middle node of a linked list (used in merge sort)
node* Middle (node* head) {

	node* slow = head;
	node* fast = head->next;

	while (!slow->next && !fast && !fast->next) {

		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

// Function to perform merge sort on a linked list
node* Sort (node* head) {

	if (head->next == NULL) return head;

	node* mid = (node*)malloc(sizeof(node));
	node* head2 = (node*)malloc(sizeof(node));
	mid = Middle(head);
	head2 = mid->next;
	mid->next = NULL;
	node* head3 = Merge(Sort(head), Sort(head2));
	return head3;
}

// Function to find the intersection of two sets and print the result
void Intersection (node* set1, node* set2) {
	
	node* trav1;
	node* trav2;
	if (set1->next != NULL) trav1 = set1->next;
	if (set2->next != NULL) trav2 = set2->next;

	while (trav1 != NULL && trav2 != NULL) {
	
		if (trav1->data > trav2->data) trav2 = trav2->next;

		else if (trav2->data > trav1->data) trav1 = trav1->next;

		else {
		
			printf("%d\n", trav1->data);
			trav1 = trav1->next;
			trav2 = trav2->next;
		}
	}
}

// Function to print the elements of a linked list
void Print_set (node* head) {

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


int main() {

	node* set1;
	node* set2;
	
	set1 = Init_list();
	set2 = Init_list();
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
	printf("\nSet1 before intersection :\n");
	Print_set(set1);
	printf("\nSet2 before intersection :\n");
	Print_set(set2);
	Sort(set1);
	Sort(set2);
	printf("\nIntersection Set :\n");
	Intersection(set1, set2);	
	return 0;
}

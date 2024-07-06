#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

// int source;
// int flag = 0;
int num_var;
int num_clause;
int component[1000];
int assignment[1000];
int counter = 0;

typedef struct node {
	
	int data;
	struct node* next;
}node;

node* Create_node(int val) {
	
	node* new = (node*)malloc(sizeof(node));
	new->data = val;
	new->next = NULL;
	return new;
}

int top = -1;
int stack[1000];

void Push(int val) {
	
	stack[++top] = val;
}

bool Check_empty() {

	if (top == -1) return true;
	else return false;
}

int Pop() {
	
	if (!Check_empty()) return stack[top--];
	else exit(0);	
}

int Peek() {
	
	return stack[top];
}

void Insert(int pos, node* new, node* list[]) {
	
	if (list[pos] == NULL) {
		
		list[pos] = new;
		return;
	}
	else {
		
		node* trav;
		trav = list[pos];
		
		while (trav->next != NULL) trav = trav->next;
		
		trav->next = new;
		return;
	}
}

// void DFS(int current, node* list[], int status[]) {
	
// 	node* trav;
// 	trav = list[current];
// 	status[current] = 1;
	
// 	while (trav != NULL) {
		
// 		int input = trav->data > 0 ? trav->data : 2 * num_var + trav->data + 1;
		
// 		if (status[input] == 0) {
			
// 			if (trav->data == -source) {
			
// 				flag++;
// 				assignment[abs(source)] = (source > 0) ? 1 : 0;
// 				return;	
// 			}
// 			DFS(input, list, status);
// 		}
// 		trav = trav->next;
// 	}
// }

void DFS1(int current, node* list[], int index) {
	
	component[current] = index;

	node* trav;
	trav = list[current];

	while (trav != NULL) {

		int input = trav->data > 0 ? trav->data : 2 * num_var + trav->data + 1;

		if (component[input] == -1) DFS1(input, list, index);

		trav = trav->next;
	}
}

void DFS2(int current, node* list[], int status[]) {

	status[current] = 1;

	node* trav;
	trav = list[current];

	while (trav != NULL) {

		int input = trav->data > 0 ? trav->data : 2 * num_var + trav->data + 1;

			if (status[input] == 0) DFS2(input, list, status);

			trav = trav->next;
	}

	Push(current);
}

int main (int argc, char *argv[]) {
	
	printf("Enter the number of variables and the number of clauses for the 2 - CNF :\n");
	scanf("%d%d", &num_var, &num_clause);
	
	if (num_var <= 0 || num_clause <= 0) {
		
		printf("Invalid Input\n");
		exit(0);
	}
	
	node* adj_list[(2 * num_var) + 1];
	node* reverse_adj_list[(2 * num_var) + 1];
	int status[(2 * num_var) + 1];
	
	for (int i = 0 ; i < 1000 ; i++) component[i] = -1;
	for (int i = 0 ; i <= 2 * num_var ; i++) {
		
		adj_list[i] = NULL;
		reverse_adj_list[i] = NULL;
		status[i] = 0;
	}
	
	printf("Enter the literal in each clause (x1 as 1 and ~x1 as -1) :\n");
	
	for (int i = 0 ; i < num_clause ; i++) {
		
		int vertex1;
		int vertex2; 
		scanf("%d%d", &vertex1, &vertex2);
		
		Insert(vertex1 < 0 ? -vertex1 : 2 * num_var - vertex1 + 1, Create_node(vertex2), adj_list);
		Insert(vertex2 < 0 ? -vertex2 : 2 * num_var - vertex2 + 1, Create_node(vertex1), adj_list);
		
		vertex1 *= -1;
		vertex2 *= -1;

		Insert(vertex1 < 0 ? -vertex1 : 2 * num_var - vertex1 + 1, Create_node(vertex2), reverse_adj_list);
		Insert(vertex2 < 0 ? -vertex2 : 2 * num_var - vertex2 + 1, Create_node(vertex1), reverse_adj_list);
	}
	
	// for (int i = 1 ; i <= num_var ; i++) {
		
	// 	if (flag == 2) break;
		
	// 	for (int i = 0 ; i <= 2 * num_var ; i++) status[i] = 0;
	// 	flag = 0;
	// 	source = i;
		
	// 	DFS(i, adj_list, status);
		
	// 	if (flag) {
			
	// 		source *= -1;
	// 		DFS(2 * num_var - i + 1, adj_list, status);
	// 	}
	// }
	
	// if (flag == 2) printf("Unsatisfiable\n" );
	// else {
		
	// 	printf("Satisfiable\nSatisfying Assignment:\n");
    //     	for (int i = 1; i <= num_var; i++) printf("x%d = %d\n", i, assignment[i]);
	// }

	for (int i = 1 ; i <= 2 * num_var ; i++) if (status[i] == 0) DFS2(i, adj_list, status);

	while (!Check_empty()) {
		
		int input = Pop();
		//int input = current > 0 ? current : 2 * num_var + current + 1;

		if (component[input] == -1) DFS1(input, reverse_adj_list, counter++);
	}

	for (int i = 1 ; i <= num_var ; i++) {
		
		int complement = 2 * num_var - i + 1;

		if (component[i] == component[complement]) {
			
			printf("Unsatisfiable\n");
			return 0;
		}
		else if (component[i] < component[complement]) assignment[i] = 0;
		else assignment[i] = 1;
	}

	printf("Satisfiable\nSatisfying Assignment:\n");
	for (int i = 1; i <= num_var; i++) printf("x%d = %d\n", i, assignment[i]);
	printf("\n");
	return 0;
}

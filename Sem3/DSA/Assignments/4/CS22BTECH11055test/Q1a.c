#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

int num_vertices;
int num_edges;
int start;
int timer = 0;
int timestamp[1000][2];

int top = -1;
int stack[10000];

void Push(int val) {
	
	stack[++top] = val;
}

int Pop() {
	
	return stack[top--];	
}

int Peek() {
	
	return stack[top];
}

bool Check_empty() {

	if (top == -1) return true;
	else return false;
}

typedef struct node {

	int data;
	int weight;
	struct node* next;
}node;

node* Create_node(int val, int weight) {

	node* new = (node*)malloc(sizeof(node));
	new->data = val;
	new->weight = weight;
	new->next = NULL;
	return new;
}

void Insert(int pos, node* new, node* adj_list[]) {

	if (adj_list[pos] == NULL) {

		adj_list[pos] = new;
		return;
	}
	else {

		node* trav;
		trav = adj_list[pos];

		while (trav->next != NULL) trav = trav->next;

		trav->next = new;
		return;
	}
}

void Print() {
	
	int distance = -1;
	
	for (int i = 0 ; i <= top ; i++) {
		
		printf("%d ", stack[i]);
		distance++;
	}
	
	printf("%d\n", distance);
}

void DFS(node* list[], int status[]) {
	
	Push(start);
	int current = start;
	
	while (!Check_empty()) {
		
		status[current] = 1;
		int flag = 0;
		
		node* trav;
		trav = list[current];
		
		while (trav != NULL) {
			
			if (status[trav->data] == 0) {
				
				Push(trav->data);
				Print();
				current = trav->data;
				flag = 1;
				break;				
			}
			trav = trav->next; 
		}
		
		if (flag == 0) {
			
			Pop();
			current = Peek();
		}		
	}
}

int main () {

	while (1) {	
		
		scanf("%d%d%d", &num_vertices, &num_edges, &start);

		if (num_vertices <= 0 || num_edges <= 0 || start < 0) {

			printf("Invalid Inputs\n");
			exit(0);
		}

		int status[num_vertices];
		node* adj_list[num_vertices];
		for (int i = 0 ; i < num_vertices ; i++) {

			adj_list[i] = NULL;
			status[i] = 0;
		}
		
		for (int i = 0 ; i < num_edges ; i++) {

			int vertex1;
			int vertex2;
			//printf("Edge %d : ", i + 1);
			scanf("%d%d", &vertex1, &vertex2);

			if (vertex1 < 0 || vertex2 < 0) {

				printf("Invalid Vertex\n");
				exit(0);
			}
	
			Insert(vertex1, Create_node(vertex2, 0), adj_list);
			Insert(vertex2, Create_node(vertex1, 0), adj_list);
		}
		
		printf("\nDFS traversal : \n");
		DFS(adj_list, status);
		printf("\n");
		for (int i = 0 ; i < num_vertices ; i += 1) {
		
			node* trav = adj_list[i];
			while (trav != NULL) {
				
				node* temp;
				temp = trav;
				trav = trav->next;
				free(temp);
			}
		}
	}
	return 0;
}

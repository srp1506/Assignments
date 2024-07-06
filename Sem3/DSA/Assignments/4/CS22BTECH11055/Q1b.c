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

int queue[10000]; 
int head; 
int tail;

void Enqueue(int val) {

	queue[tail++] = val;
}

int Dequeue() {

	if (head == tail) {

		printf("Error : Queue Underflow!\n");
		exit(0);
	}

	return queue[head++];
}

int Size() {

	return tail - head;
}

bool Check_empty() {

	if (head == tail) return true;
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

void BFS(node* list[], int status[], int precedence[], int distance[]) {

	Enqueue(start);
	int current;

	while (!Check_empty()) {

		current = Dequeue();
		status[current] = 2;

		node* trav;
		trav = list[current];

		while (trav != NULL) {

			if (status[trav->data] == 0) {

				Enqueue(trav->data);
				status[trav->data] = 1;
				precedence[trav->data] = current;
				distance[trav->data] = distance[current] + 1;
			}
			trav = trav->next;
		}
	}
}

void Print(int current, int precedence[], int distance[]) {

	int path[num_vertices];
	int count = 0;
	int parent = current;

	while (parent != -1) {

		path[count++] = parent;
		parent = precedence[parent];
	}

	for (int i = count - 1 ; i >= 0 ; i -= 1) printf("%d ", path[i]);
	printf("%d\n", distance[current]);
}

int main () {

	while (1) {
		
		head = 0; 
 		tail = 0;
		scanf("%d%d%d", &num_vertices, &num_edges, &start);

		if (num_vertices <= 0 || num_edges <= 0 || start < 0) {

			printf("Invalid Inputs\n");
			exit(0);
		}

		int status[num_vertices];
		int precedence[num_vertices];
		int distance[num_vertices];
		node* adj_list[num_vertices];
		for (int i = 0 ; i < num_vertices ; i++) {

			adj_list[i] = NULL;
			status[i] = 0;
			precedence[i] = -1;
			distance[i] = 0;
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

		if (num_vertices > 1) BFS(adj_list, status, precedence, distance);

		printf("\nBFS traversal :\n");

		for (int i = 0 ; i < num_vertices ; i++) {
		
			if (i == start) continue;
			Print(i, precedence, distance);
		}
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

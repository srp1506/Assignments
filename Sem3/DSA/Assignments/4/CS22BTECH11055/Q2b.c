#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<time.h>

int num_vertices;
int num_edges;
int size;

typedef struct node{
	
	int weight;
	int vertex1;
	int vertex2;
	struct node* next;
}node; 

node* Create_node(int weight, int vertex1, int vertex2) {
	
	node* new = (node*)malloc(sizeof(node));
	new->weight = weight;
	new->vertex1 = vertex1;
	new->vertex2 = vertex2;
	new->next = NULL;
	return new;
}


node* Merge (node* node1, node* node2) {

	node* merged = (node*)malloc(sizeof(node));
	node* temp = (node*)malloc(sizeof(node));
	merged = temp;

	while (node1 != NULL && node2 != NULL) {

		if (node1->weight <= node2->weight) {

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

node* Middle (node* head) {

	node* slow = head;
	node* fast = head->next;

	while (!slow->next && !fast && !fast->next) {

		slow = slow->next;
		fast = fast->next->next;
	}
	
	return slow;
}

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

void Insert(node* head, node* new) {
		
	node* trav;
	trav = head;
	
	while (trav->next != NULL) trav = trav->next;
	
	trav->next = new;
}

int Find(int val, int array[]) {
	
	int root = val;
	
	while (array[root] != root) root = array[root];
	
	return root;
}

void Union(int a, int b, int array[], int rank[]) {
	
	if (rank[a] < rank[b]) array[a] = b;
	else if (rank[b] < rank[a]) array[b] = a;
	else array[a] = b, rank[b]++;
}

int main (int argc, char *argv[]) {
	
	while (1) {
		
		size = 0;
		node* head = Create_node(-1, -1, -1);	
		scanf("%d%d", &num_vertices, &num_edges);
		
		if (num_vertices <= 0 || num_edges <= 0) {

			printf("Invalid Inputs\n");
			continue;
		}
		
		int precedence[num_vertices + 1];
		node* span[num_vertices - 1];
		
		for (int i = 0 ; i <= num_vertices ; i++) precedence[i] = i;
		
		for (int i = 0 ; i < num_edges ; i += 1) {
		
			int vertex1;
			int vertex2;
			int weight;
			
			scanf("%d%d%d", &vertex1, &vertex2, &weight);
			
			Insert(head, Create_node(weight, vertex1, vertex2));	
		}
					
		Sort(head);
		
		int rank[num_vertices];
		for (int i = 0 ; i < num_vertices ; i++) rank[i] = 0;
		node* trav;
		trav = head->next;
		
		while (trav != NULL && size < num_vertices - 1) {
			
			int vertex1 = trav->vertex1;
			int vertex2 = trav->vertex2;
			int root1 = Find(vertex1, precedence);
			int root2 = Find(vertex2, precedence);
			
			if (root1 != root2) {
			
				span[size++] = trav;
				Union(root1, root2, precedence, rank);
			}

			trav = trav->next;
		}
		
		if (size != num_vertices - 1) {
			
			printf("Graph isn't connected\n");
			continue;
		}
		
		int weight_sum = 0;
		for (int i = 0 ; i < num_vertices - 1 ; i++) weight_sum += span[i]->weight;
		
		printf("Spanning tree :\n");
		for (int i = 0 ; i < num_vertices - 1 ; i++) printf("%d-%d %d\n", span[i]->vertex1, span[i]->vertex2, span[i]->weight);
		printf("Total Weight of the Tree : %d\n", weight_sum);
		
		trav = head;
		while (trav != NULL) {
			
			node* temp;
			temp = trav;
			trav = trav->next;
			free(temp);
		}
	}
	return 0;
}

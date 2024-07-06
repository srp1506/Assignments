#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<limits.h>

int num_vertices;
int num_edges;
int start;
int heap_size = 0;
int size = 0;

typedef struct node {

	int vertex1;
	int vertex2;
	int weight;
	struct node* next;
}node;

node* Create_node(int vertex1, int vertex2, int weight) {

	node* new = (node*)malloc(sizeof(node));
	new->vertex1 = vertex1;
	new->vertex2 = vertex2;
	new->weight = weight;
	new->next = NULL;
	return new;
}

void Heapify(int pos, int distance[], node* heap) {

	while (((2 * pos) + 1 <= heap_size || (2 * pos) <= heap_size) &&
           (distance[heap[pos]->vertex2] > distance[heap[2 * pos]->vertex2] || (2 * pos + 1 <= heap_size && distance[heap[pos]->vertex2] > distance[heap[2 * pos + 1]->vertex2]))) {
	
		if (distance[heap[2 * pos]->vertex2] <= distance[heap[2 * pos + 1]->vertex2]) {
        	    
        	    node* temp = heap[pos];
        	    heap[pos] = heap[2 * pos];
        	    heap[2 * pos] = temp;
        	    pos = 2 * pos;
        	} 
        	else {
        	    
        	    node* temp = heap[pos];
        	    heap[pos] = heap[2 * pos + 1];
        	    heap[2 * pos + 1] = temp;
        	    pos = 2 * pos + 1;
        	}
	}
	return;
}

void Bubble_up(int pos, int distance[], node* heap[]) {

	while (pos > 1 && distance[heap[pos / 2]->vertex2] > distance[heap[pos]->vertex2]) {

		node* temp;
		temp = heap[pos];
		heap[pos] = heap[pos / 2];
		heap[pos / 2] = temp;
		pos /= 2;
	}
	return;
}

void Insert_heap(node* key, int distance, node* heap[]) {

	if (heap_size == num_edges * num_edges) {

		printf("Heap Overflow\n");
		return;
	}
	
	heap_size++;
	heap[heap_size] = key;
	Bubble_up(heap_size, distance, heap);
	return;
}

node* Poll(int distance[], node* heap[]) {

	if (heap_size == 0) {

		printf("Heap is empty\n");
		return NULL;
	}

	node* val;
	val = heap[1];
	heap[1] = heap[heap_size--];
	Heapify(1, distance, heap);
	return val;
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

int main (int argc, char *argv[]) {
	
	while (1) {

		scanf("%d%d%d", &num_vertices, &num_edges, &start);
		
		if (num_vertices <= 0 || num_edges <= 0 || start < 0) {

			printf("Invalid Inputs\n");
			exit(0);
		}
		
		int distance[num_vertices];
		node* heap[num_edges * num_edges];
		node* adj_list[num_vertices];
		int precedence[num_vertices];
		int status[num_vertices];
		
		for (int i = 0 ; i < num_vertices ; i++) distance[i] = INT_MAX;

		for (int i = 0 ; i < num_vertices ; i++) {
			
			adj_list[i] = NULL;
			precedence[i] = start;
			status[i] = 0;
		}
		
		for (int i = 0 ; i < num_edges ; i++) {

			int vertex1;
			int vertex2;
			int weight;
			scanf("%d%d%d", &vertex1, &vertex2, &weight);

			if (vertex1 < 0 || vertex2 < 0 || weight < 0) {

				printf("Invalid Vertex\n");
				exit(0);
			}
			
			Insert(vertex1, Create_node(vertex1, vertex2, weight), adj_list);
			//Insert(vertex2, Create_node(vertex2, vertex1, weight), adj_list);
		}
		
		printf("\nSource : %d\n", start);
		status[start] = 1;
		size++;
		distance[start] = 0;
		node* trav = adj_list[start];
		
		while (trav != NULL) {
			
			distance[trav->vertex2] = trav->weight;
			Insert_heap(trav, distance, heap);
			trav = trav->next;
		}
		
		while (size < num_vertices && heap_size > 0) {
			
			trav = Poll(distance, heap);
			
			while (status[trav->vertex1] == 1 && status[trav->vertex2] == 1) trav = Poll(distance, heap);
			
			status[trav->vertex2] = 1;
			size++;
			
			trav = adj_list[trav->vertex2];
			
			while (trav != NULL) {
				
				if (distance[trav->vertex2] > distance[trav->vertex1] + trav->weight && status[trav->vertex2] == 0) {
					
					distance[trav->vertex2] = distance[trav->vertex1] + trav->weight;
					precedence[trav->vertex2] = trav->vertex1;
				}
				if (status[trav->vertex2] == 0) Insert_heap(trav);
				trav = trav->next;
			}
		}
		
		for (int i = 0 ; i < num_vertices ; i++) {
			
			if (i == start) continue;

			if (distance[i] == INT_MAX) {

				printf("No path from source to %d\n", i);
				continue;
			}
			printf("Distance of vertex %d from source : %d	Path : ", i, distance[i]);
			
			int current = i;
			
			while (current != start) {
				
				printf("%d<-", current);
				current = precedence[current];
			}
			printf("%d\n", start);
		}
	}
	return 0;
}

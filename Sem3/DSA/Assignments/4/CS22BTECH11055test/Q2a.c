#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<time.h>

int num_vertices;
int num_edges;
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

void Heapify(int pos, node* heap[]) {

	while (((2 * pos) + 1 <= heap_size || (2 * pos) <= heap_size) &&
           (heap[pos]->weight > heap[2 * pos]->weight || (2 * pos + 1 <= heap_size && heap[pos]->weight > heap[2 * pos + 1]->weight))) {
	
		if (heap[2 * pos]->weight <= heap[2 * pos + 1]->weight) {
        	    
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

void Bubble_up(int pos, node* heap[]) {

	while (pos > 1 && heap[pos / 2]->weight > heap[pos]->weight) {

		node* temp;
		temp = heap[pos];
		heap[pos] = heap[pos / 2];
		heap[pos / 2] = temp;
		pos /= 2;
	}
	return;
}

void Insert_heap(node* key, node* heap) {

	if (heap_size == num_edges * num_edges) {

		printf("Heap Overflow\n");
		return;
	}
	
	heap_size++;
	heap[heap_size] = key;
	Bubble_up(heap_size, heap);
	return;
}

node* Poll(node* heap) {

	if (heap_size == 0) {

		printf("Heap is empty\n");
		return NULL;
	}

	node* val;
	val = heap[1];
	heap[1] = heap[heap_size--];
	Heapify(1, heap);
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

		scanf("%d%d", &num_vertices, &num_edges);
		
		if (num_vertices <= 0 || num_edges <= 0) {

			printf("Invalid Inputs\n");
			continue;	
		}
		
		node* heap[num_edges * num_edges];
		node* adj_list[num_vertices];
		int status[num_vertices];
		node* span[num_vertices - 1];
		
		for (int i = 0 ; i < num_vertices ; i++) {
			
			adj_list[i] = NULL;
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
			Insert(vertex2, Create_node(vertex2, vertex1, weight), adj_list);
		}
		
		status[0] = 1;
		node* trav = adj_list[0];
		
		while (trav != NULL) {
			
			Insert_heap(trav, heap);
			trav = trav->next;
		}
		
		while (size < num_vertices - 1 && heap_size > 0) {
			
			trav = Poll(heap);
			
			while (status[trav->vertex1] == 1 && status[trav->vertex2] == 1) trav = Poll(heap);
			
			status[trav->vertex2] = 1;
			span[size++] = trav;
			
			trav = adj_list[trav->vertex2];
			
			while (trav != NULL) {
				
				Insert_heap(trav, heap);
				trav = trav->next;
			}
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
	}
	return 0;
}

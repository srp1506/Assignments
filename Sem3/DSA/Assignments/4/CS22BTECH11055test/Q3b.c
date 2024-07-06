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

typedef struct node {

	int vertex1;
	int vertex2;
	int weight;
}node;

node* Create_node(int vertex1, int vertex2, int weight) {

	node* new = (node*)malloc(sizeof(node));
	new->vertex1 = vertex1;
	new->vertex2 = vertex2;
	new->weight = weight;
	return new;
}

int main (int argc, char *argv[]) {
	
	while (1) {

		scanf("%d%d%d", &num_vertices, &num_edges, &start);
		
		if (num_vertices <= 0 || num_edges <= 0 || start < 0) {

			printf("Invalid Inputs\n");
			continue;
		}
		
		int distance[num_vertices];
		int precedence[num_vertices];
		node* edges[num_edges];
		
		for (int i = 0 ; i < num_vertices ; i++) {
			
			edges[i] = NULL;
			distance[i] = INT_MAX;
			precedence[i] = start;
		}
		
		for (int i = 0 ; i < num_edges ; i++) {

			int vertex1;
			int vertex2;
			int weight;
			scanf("%d%d%d", &vertex1, &vertex2, &weight);

			if (vertex1 < 0 || vertex2 < 0) {

				printf("Invalid Vertex\n");
				exit(0);
			}
			
			edges[i] = Create_node(vertex1, vertex2, weight);			
		}
		
		printf("\nSource : %d\n", start);
		distance[start] = 0;
		
		for (int i = 0 ; i < num_vertices - 1 ; i++) {
			
			for (int j = 0 ; j < num_edges ; j++) {
				
				node* current = edges[j];
				
				if (distance[current->vertex1] != INT_MAX && distance[current->vertex2] > distance[current->vertex1] + current->weight) {
					
					distance[current->vertex2] = distance[current->vertex1] + current->weight;
					precedence[current->vertex2] = current->vertex1;
				}
			}
		}
		
		int flag = 0;
		
		for (int i = 0 ; i < num_vertices - 1 ; i++) {
			
			for (int j = 0 ; j < num_edges ; j++) {
				
				node* current = edges[j];
				
				if (distance[current->vertex1] != INT_MAX && distance[current->vertex2] > distance[current->vertex1] + current->weight) {
					
					flag = 1;
					break;
				}
			}
		}
		
		if (flag) {
			
			printf("Graph contains a negative cycle\n");
			continue;
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

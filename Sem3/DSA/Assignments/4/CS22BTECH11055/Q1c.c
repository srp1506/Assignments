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

void DFS(int current, node* list[], int status[]) {

	node* trav;
	trav = list[current];

	while (trav != NULL) {

		if (status[trav->data] == 0) {

			status[trav->data] = -status[current];
			DFS(trav->data, list, status);
		}
		trav = trav->next;
	}
}

int main () {

	while (1) {

		start = 0;
		scanf("%d%d", &num_vertices, &num_edges);

		if (num_vertices <= 0 || num_edges <= 0) {

			printf("Invalid Inputs\n");
			exit(0);
		}
		
		int status[num_vertices];
		node* adj_list[num_vertices];
		for (int i = 0 ; i < num_vertices ; i++) {

			adj_list[i] = NULL;
			status[i] = 0;
		}

		status[start] = 1;

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

		DFS(start, adj_list, status);

		int flag = 1;

		for (int i = 0 ; i < num_vertices ; i++) {
		
			if (status[i] == 0) {

				flag = 0;
				break;
			}		
		}

		if (flag) {
			
			for (int i = 0 ; i < num_vertices ; i += 1) {
				
				if (flag == 0) break; 
				
				int color;
				color = status[i];

				node* trav;
				trav = adj_list[i];
			
				while (trav != NULL) {

					if (status[trav->data] == color) {
					
						flag = 0;
						break;
					}
					trav = trav->next;
				}
			}
		}
		printf("\nBipartite? - ");
		printf(flag == 1 ? "YES\n" : "NO\n");
		
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

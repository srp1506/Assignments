#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#define MAX_SIZE 1000

int size;
int reverse_size;
int queue[MAX_SIZE] = {0};

void Heapify(int pos) {

	while (((2 * pos) + 1 <= size || (2 * pos) <= size) &&
           (queue[pos] > queue[2 * pos] || (2 * pos + 1 <= size && queue[pos] > queue[2 * pos + 1]))) {
	
		if (queue[2 * pos] <= queue[2 * pos + 1]) {
        	    
        	    int temp = queue[pos];
        	    queue[pos] = queue[2 * pos];
        	    queue[2 * pos] = temp;
        	    pos = 2 * pos;
        	} 
        	else {
        	    
        	    int temp = queue[pos];
        	    queue[pos] = queue[2 * pos + 1];
        	    queue[2 * pos + 1] = temp;
        	    pos = 2 * pos + 1;
        	}
	}
	return;
}

void Bubble_up(int pos) {

	while (pos > 1 && queue[pos / 2] > queue[pos]) {

		int temp;
		temp = queue[pos];
		queue[pos] = queue[pos / 2];
		queue[pos / 2] = temp;
		pos /= 2;
	}
	return;
}

void Insert(int key) {

	if (size == MAX_SIZE) {

		printf("Queue Overflow\n");
		return;
	}

	//if (Search(key) != -1) {

	//	printf("%d already exits, no need to insert\n", key);
	//	return;
	//}
	
	size++;
	queue[size] = key;
	Bubble_up(size);
	//printf("%d inserted\n", key);
	return;
}

void Delete_min() {

	if (size == 0) {

		printf("Queue is empty\n");
		return;
	}

	int val;
	val = queue[1];
	queue[1] = queue[size];
	queue[reverse_size--] = val;
	size--;
	Heapify(1);
	//printf("Polled value : %d\n", val);
	return;
}

void Heapsort() {
	
	while (size >= 1) Delete_min();
} 

void Display(int index, int level) {
    
	if (index <= size) {
       
	    Display(2 * index, level + 1);

        for (int i = 0; i < level; i++) printf("    ");

        printf("%d\n", queue[index]);

        Display(2 * index + 1, level + 1);
    }
}

int main (int argc, char *argv[]) {

	int n;
	int val;
	printf("Enter the number of inputs :\n");
	scanf("%d", &n);
	reverse_size = n + 1;
	
	if (n <= 0) {
		
		printf("Invalid size\n");
		exit(0);
	}
	
	if (n >= MAX_SIZE) {
		
		printf("Heap Overflow\n");
		exit(0);
	}

	//printf("%d\n", size);
	printf("Enter the values to be inserted: \n");

	for (int i = 0 ; i < n ; i +=1) {

		scanf("%d", &val);
		Insert(val);
	}
	
	//for (int i = 1 ; i <= size ; i++) printf("%d ", queue[i]);
	
	printf("\nHeap Structure:\n");
	Display(1, 1);
	//printf("%d", size);
	Heapsort();
	
	printf("\nSorted array : ");
	for (int i = n + 1 ; i > 1 ; i--) printf("%d ", queue[i]);
	printf("\n");
	return 0;
}

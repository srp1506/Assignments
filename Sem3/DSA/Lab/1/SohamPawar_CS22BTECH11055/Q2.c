#include<stdio.h>
#include<stdlib.h>

int queue[256];
int head = 0; 
int tail = 1;

void Enqueue(int num) {

	if (head != tail) {
		
		if (tail < 255) {
			
			queue[tail] = num;
			tail++;
		}

		else {

			queue[tail];
			tail = 0;
		}
	}

	else {
	
		printf("Queue Overflow\n");
		return 0;
	}

}

int Dequeue () {

	if (head < 255) {

		head++;
		return queue[head];
	}

	else {
	
		head = 0;
		return queue[255];
	}
}

int main() {

	int size;
	int k;
	printf("Enter The Size Of The Queue : ");
	scanf("%d", &size);
	printf("k : ");
	scanf("%d", &k);

	for (int i = 0 ; i < size ; i++) {
	
		int val;
		scanf("%d", &val);
		Enqueue(val);
	}
	
	int val[size];
	
	for (int i = 0 ; i < size ; i++) val[i] = Dequeue();

	head = 0;
	tail = 1;

	for (int i = k - 1 ; i >= 0 ; --i) Enqueue(val[i]);

	for (int i = k ; i < size ; i++) Enqueue(val[i]);

	printf("Reversed Queue : \n");

	for (int i = head + 1 ; i < tail ; i++) printf("%d\n", queue[i]);

	return 0;
}

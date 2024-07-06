#include <stdio.h>
#include <stdlib.h>

int stack1[256];
int counter1 = 0;

int Pop_Stack1() {

	counter1--;
	return stack1[counter1];
}

void Push_Stack1(int num) {
	
	stack1[counter1] = num;
	counter1++;
}

int stack2[256];
int counter2 = 0;

int Pop_Stack2() {

	counter2--;
	return stack2[counter2];
}

void Push_Stack2(int num) {
	
	stack2[counter2] = num;
	counter2++;
}

void Enqueue(int num) {

	Push_Stack1(num);
}

int Dequeue() {
	
	if (counter1 == 0 && counter2 == 0) {
		
		printf("Queue is empty\n");
		return 0;
	}

	if (counter2 == 0) {
		
		while (counter1 > 0) {
			
			Push_Stack2(Pop_Stack1());
		}
	}

	int val = Pop_Stack2();

	if (counter1 == 0) {
		
		while (counter2 > 0) {
			
			Push_Stack1(Pop_Stack2());
		}
	}

	return val;
}


int main() {

	int size;
	printf("Enter the size of the Queue: ");
	scanf("%d", &size);
	printf("Enter value to enqueue:\n");	

	for (int i = 0; i < size; i++) {

		int val;
		scanf("%d", &val);
		Enqueue(val);
	}

	Dequeue();
	Dequeue();
	Dequeue();
	Dequeue();
	Enqueue(10);
	Enqueue(100);
	Enqueue(1000);
	printf("Altered Queue :\n");
	for (int i = 0 ; i < counter1 ; i++) printf("%d\n",stack1[i]);
	return 0;
}


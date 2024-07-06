#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<ctype.h>
#include<math.h>
#include<unistd.h>
#include<stdbool.h>

node* Search(node* root, int key);
int Insert(node* root, int key);
int Delete(node* root, int key);

node * Tree_root;

node* queue[100]; 
int head = 0; 
int tail = 0;

void Enqueue(node* array[], node* val) {

	array[tail++] = val;
}

node* Dequeue(node* array[]) {

	if (head == tail) {

		printf("Error : Queue Underflow!\n");
		exit(0);
	}

	return array[head++];
}

node* Peek(node* queue[]) {

	return queue[head];
}

int Size() {

	return tail - head;
}

bool Check_empty(node* array[]) {

	if (head == tail) return true;
	else return false;
}

void Clear_queue(){
    
	head = 0;
    tail = 0;
}

node* stack1[256];
int counter1 = 0;
node* stack2[256];
int counter2 = 0;

node* Pop_stack1() {

	if (counter1 == 0) return NULL;

	counter1--;
	return stack1[counter1];
}

void Push_stack1(node* node) {

	stack1[counter1++] = node;
}

node* Pop_stack2() {

	if (counter2 == 0) return NULL;

	counter2--;
	return stack2[counter2];
}

void Push_stack2(node* node) {

	stack2[counter2] = node;
	counter2++;
}

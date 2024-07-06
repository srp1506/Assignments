#include<stdio.h>
#include<stdlib.h>

int stack[256];
int counter1 = 0;
int counter2 = 255;

void Push_Stack1(int num) {

	if (counter1 != counter2) {
	
		stack[counter1] = num;
		counter1++;
	}

	else {
	
		printf("Stack Overflow\n");
		return 0;
	}
}

int Pop_Stack1() {

	counter1--;
	return stack[counter1];
}

void Push_Stack2(int num) {

	if (counter2 != counter1) {
	
		stack[counter2] = num;
		counter2--;
	}
	
	else {
	
		printf("Stack Overflow\n");
		return 0;
	}
}

int Pop_Stack2() {

	counter2++;
	return stack[counter2];
}

int main() {

	int size1;
	int size2;
	printf("Enter The Number Of Inputs In Stack1 and Stack2 Respectively : ");
	scanf("%d%d", &size1, &size2);
	printf("Enter The Members Of Stack1 :\n");
	
	for (int i = 0 ; i < size1 ; i++) {
	
		int val;
		scanf("%d", &val);
		Push_Stack1(val);
	}
	printf("Enter The Members Of Stack2 :\n");
	
	for (int i = 0 ; i < size2 ; i++) {
	
		int val;
		scanf("%d", &val);
		Push_Stack2(val);
	}

	printf("Top Of Stack1 And Stack2 Respectively - %d, %d\n", Pop_Stack1(), Pop_Stack2());
	return 0;
}

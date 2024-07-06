#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int stack[256];
int counter = 0;

int Pop_Stack() {

	counter--;
	return stack[counter];
}

void Push_Stack(int num) {

	stack[counter] = num;
	counter++;
}

int main() {

	char input[512];
	int pos;
	pos = 0;
	printf("Enter Postfix Expression : ");
	scanf("%s",input);
	while (input[pos] != '\0') {	
	
		int num;
		int a;
		int b;
		
		if (input[pos] == '0' || input[pos] == '1' || input[pos] == '2' || input[pos] == '3' || input[pos] == '4' || input[pos] == '5' || input[pos] == '6' || input[pos] == '7' || input[pos] == '8' || input[pos] == '9') {
			
			num = (int)(input[pos] - 48);
			Push_Stack(num);
		}

		else if (input[pos] == '+') {
		
			a = Pop_Stack();
			b = Pop_Stack();
			num = a + b;
			Push_Stack(num);
		}

		else if (input[pos] == '-') {
		
			a = Pop_Stack();
			b = Pop_Stack();
			num = b - a;
			Push_Stack(num);
		}

		else if (input[pos] == '*') {
		
			a = Pop_Stack();
			b = Pop_Stack();
			num = a * b;
			Push_Stack(num);
		}

		else if (input[pos] == '/') {
		
			a = Pop_Stack();
			b = Pop_Stack();
			num = b / a;
			Push_Stack(num);
		}

		pos++;
		
	}

	printf("%d\n",stack[0]);
	return 0;
}

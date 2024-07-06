#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char stack[512]; // Stack to store operators
int counter = 0; // Counter to keep track of the stack size

// Function to pop an element from the stack
char Pop_Stack () {

	if (counter <= 0) {

		printf("Stack is empty\n");
		return '\0';
	}

	counter--;
	return stack[counter];
}

// Function to push an element onto the stack
void Push_Stack (char val) {

	stack[counter] = val;
	counter++;
}

// Function to determine the precedence of an operator
int Precedence (char operator) {

	if (operator == '^') return 3;

	if (operator == '*' || operator == '/') return 2;

	if (operator == '+' || operator == '-') return 1;

	return 0;
}

// Function to convert infix expression to postfix using the Shunting Yard Algorithm
char* Infix_to_Postfix (char* input) {

	char* postfix = (char*)malloc(512 * sizeof(char));
	int pos = 0;
	int outputPos = 0;

	while (input[pos] != '\0') {

		char current = input[pos];

		if (current >= '0' && current <= '9') {

			postfix[outputPos] = current;
			outputPos++;
		}

		else if (current == '(') Push_Stack(current); 

		else if (current == ')') {

			while (counter > 0 && stack[counter - 1] != '(') {

				postfix[outputPos] = Pop_Stack();
				outputPos++;
			}

			if (counter > 0 && stack[counter - 1] == '(') Pop_Stack();
		}

		else if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') {

			while (counter > 0 && Precedence(stack[counter - 1]) >= Precedence(current)) {

				postfix[outputPos] = Pop_Stack();
				outputPos++;
			}

			Push_Stack(current);
		}

		pos++;
	}

	while (counter > 0) {

		postfix[outputPos] = Pop_Stack();
		outputPos++;
	}

	postfix[outputPos] = '\0';

	return postfix;
}

int main() {

	char input[512];
	printf("Enter Infix Expression :\n");
	scanf("%s",input);
	char* postfix;
	postfix = Infix_to_Postfix(input);
	printf("\nPostfix Expression:\n%s\n", postfix);
	free(postfix);
	return 0;
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<math.h>
#include<unistd.h>
// Above is the list of header files included in the implementation

int program_counter = 0; // Keeps track of the instruction being processed
int label_counter = 0; // Keeps track of the number of labels initialised
char* list[256]; // To store the processed instructions

// Converting hexadecimal code to binary string
char* Hexa_Bin(char* hexa) { 

	char* binary;
	binary = (char*)malloc(32 * sizeof(char));

	if (binary == NULL) {

		printf("Memory Allocation Failed\n");
		return NULL;
	}

	int i;
	int j;
	i = (hexa[1] == 'x' || hexa[1] == 'X') ? 2 : 0;
	j = 0;

	while (hexa[i]) {

		switch (hexa[i]) {

			case '0':
				strcat(binary, "0000");
				break;

			case '1':
				strcat(binary, "0001");
				break;

			case '2':
				strcat(binary, "0010");
				break;

			case '3':
				strcat(binary, "0011");
				break;

			case '4':
				strcat(binary, "0100");
				break;

			case '5':
				strcat(binary, "0101");
				break;

			case '6':
				strcat(binary, "0110");
				break;

			case '7':
				strcat(binary, "0111");
				break;

			case '8':
				strcat(binary, "1000");
				break;

			case '9':
				strcat(binary, "1001");
				break;

			case 'A':
			case 'a':
				strcat(binary, "1010");
				break;

			case 'B':
			case 'b':
				strcat(binary, "1011");
				break;

			case 'C':
			case 'c':
				strcat(binary, "1100");
				break;

			case 'D':
			case 'd':
				strcat(binary, "1101");
				break;

			case 'E':
			case 'e':
				strcat(binary, "1110");
				break;

			case 'F':
			case 'f':
				strcat(binary, "1111");
				break;

			default :
				printf("Invalid Hexadeimal Digit\n");
		}
		i++;
		j += 4; 
	}
	binary[j + 1] = '\0';
	return binary;
}

// Converting binary string to decimal based on the mode : 0 for unsigned conversion, 1 for signed conversion
int Bin_Dec(char* binary, int mode) {

	int number;
	number = 0;
	int length;
	length = strlen(binary);

	if (mode) if (binary[0] == '1') number -= pow(2, length - 1);

	int i = mode ? 1 : 0;

	while (i < length) {

		if (binary[i] == '1') number += pow(2, length - i - 1);
		i++;
	}

	return number;
}

// To get the substring based on the starting index and length of the substring to be spliced
char* Substring(const char* input, int start, int length) {

	if (start < 0 || length < 0) {

		printf("Invalid start or length\n");
		return NULL;
	}

	size_t input_length = strlen(input);

	if (start >= input_length) {

		printf("Start index is out of bounds\n");
		return NULL;
	}

	char* output = (char*)malloc((length + 1) * sizeof(char));

	if (output == NULL) {

		printf("Memory allocation failed\n");
		return NULL;
	}

	strncpy(output, input + start, length);
	output[length] = '\0';

	return output;
}

// To reverse a given string
void Reverse(char* str) {

	int length = strlen(str);
	char *start = str;
	char *end = str + length - 1;

	while (start < end) {

		char temp1;
		temp1 = *start;
		*start = *end;
		*end = temp1;
		start++;
		end--;
	}
}

// Identifies, Converts and Appends the given binary string to the list
void Add_instruction(char* opcode, char* binary) {

	//printf("Opcode : %s\n", opcode);
	int offset;
	char* rs1;
	char* rs2;
	char* rd;
	char* funct7;
	char* funct3;
	char* imm;
	char* statement;
	char temp1[5];
	char* temp2;
	char* temp3;

	if (!strcmp(opcode, "0110011")) {

		//printf("R\n");
		funct7 = Substring(binary, 0, 7);
		rs2 = Substring(binary, 7, 5);
		rs1 = Substring(binary, 12, 5);
		funct3 = Substring(binary, 17, 3);
		rd = Substring(binary, 20, 5);
		//printf("%s %s %s %s %s\n%d %d %d %d %d\n", funct7, rs2, rs1, funct3, rd, Bin_Dec(funct7, 0), Bin_Dec(rs2, 0), Bin_Dec(rs1, 0), Bin_Dec(funct3, 0), Bin_Dec(rd, 0));

		if (!strcmp(funct7, "0000000")) {

			switch (Bin_Dec(funct3, 0)) {

				case 0 :
					statement = strdup("add");
					break;
				case 4 :
					statement = strdup("xor");
					break;
				case 6 :
					statement = strdup("or");
					break;
				case 7 :
					statement = strdup("and");
					break;
				case 1 :
					statement = strdup("sll");
					break;
				case 5 :
					statement = strdup("srl");
					break;
				case 2 :
					statement = strdup("slt");
					break;
				case 3 :
					statement = strdup("sltu");
					break;
				default :
					printf("Invalid Machine Code\n");
					exit(0);		
			}

		}
		else if (!strcmp(funct7, "0100000")) {

			switch (Bin_Dec(funct3, 0)) {

				case 0 :
					statement = strdup("sub");
					break;
				case 5 :
					statement = strdup("sra");
					break;
				default : 
					printf("Invalid Machine Code\n");
					exit(0);					
			}
		}
		else {

			printf("Invalid Machine Code\n");
			exit(0);
		}

		strcat(statement, " ");
		strcat(statement, "x");
		sprintf(temp1, "%d", Bin_Dec(rd, 0));
		strcat(statement, temp1);
		strcat(statement, " ");
		strcat(statement, "x");
		sprintf(temp1, "%d", Bin_Dec(rs1, 0));
		strcat(statement, temp1);
		strcat(statement, " ");
		strcat(statement, "x");
		sprintf(temp1, "%d", Bin_Dec(rs2, 0));
		strcat(statement, temp1);
	}
	else if (!strcmp(opcode, "0010011") || !strcmp(opcode, "0000011") || !strcmp(opcode, "1100111")) {

		//printf("I\n");
		imm = Substring(binary, 0, 12);
		rs1 = Substring(binary, 12, 5);
		funct3 = Substring(binary, 17, 3);
		rd = Substring(binary, 20, 5);
		//printf("%s %s %s %s\n%d %d %d %d\n", imm, rs1, funct3, rd, Bin_Dec(imm, 1), Bin_Dec(rs1, 0), Bin_Dec(funct3, 0), Bin_Dec(rd, 0));

		if (!strcmp(opcode, "0010011")) {

			switch (Bin_Dec(funct3, 0)) {

				case 0 :
					statement = strdup("addi");
					break;
				case 4 :
					statement = strdup("xori");
					break;
				case 6 :
					statement = strdup("ori");
					break;
				case 7 :
					statement = strdup("andi");
					break;
				case 1 :
					imm = Substring(imm, 6, 6);
					statement = strdup("slli");
					break;
				case 5 :
					if (!strcmp(Substring(imm, 0, 6), "000000")) statement = strdup("srli");
					else statement = strdup("srai");
					imm = Substring(imm, 6, 6);
					break;
				case 2 :
					statement = strdup("slti");
					break;
				case 3 :
					statement = strdup("sltiu");
					break;
				default :
					printf("Invalid Machine Code\n");
					exit(0);		
			}

			strcat(statement, " ");
			strcat(statement, "x");
			sprintf(temp1, "%d", Bin_Dec(rd, 0));
			strcat(statement, temp1);
			strcat(statement, " ");
			strcat(statement, "x");
			sprintf(temp1, "%d", Bin_Dec(rs1, 0));
			strcat(statement, temp1);
			strcat(statement, " ");
			sprintf(temp1, "%d", Bin_Dec(imm, (Bin_Dec(funct3, 0) == 1 || Bin_Dec(funct3, 0) == 5 ? 0 : 1)));
			strcat(statement, temp1);
		}
		else if (!strcmp(opcode, "0000011")) {

			switch (Bin_Dec(funct3, 0)) {

				case 0 :
					statement = strdup("lb");
					break;
				case 1 :
					statement = strdup("lh");
					break;
				case 2 :
					statement = strdup("lw");
					break;
				case 3 :
					statement = strdup("ld");
					break;
				case 4 :
					statement = strdup("lbu");
					break;
				case 5 :
					statement = strdup("lhu");
					break;
				case 6 :
					statement = strdup("lwu");
					break;
				default :
					printf("Invalid Machine Code\n");
					exit(0);		
			}
			strcat(statement, " ");
			strcat(statement, "x");
			sprintf(temp1, "%d", Bin_Dec(rd, 0));
			strcat(statement, temp1);
			strcat(statement, " ");
			sprintf(temp1, "%d", Bin_Dec(imm, 1));
			strcat(statement, temp1);
			strcat(statement, "(");
			strcat(statement, "x");
			sprintf(temp1, "%d", Bin_Dec(rs1, 0));
			strcat(statement, temp1);
			strcat(statement, ")");
		}
		else if (!strcmp(opcode, "1100111")) {

			if (Bin_Dec(funct3, 0) != 0) {

				printf("Invalid Machine Code\n");
				exit(0);
			}

			statement = strdup("jalr");
			strcat(statement, " ");
			strcat(statement, "x");
			sprintf(temp1, "%d", Bin_Dec(rd, 0));
			strcat(statement, temp1);
			strcat(statement, " ");
			sprintf(temp1, "%d", Bin_Dec(imm, 1));
			strcat(statement, temp1);
			strcat(statement, "(");
			strcat(statement, "x");
			sprintf(temp1, "%d", Bin_Dec(rs1, 0));
			strcat(statement, temp1);
			strcat(statement, ")");
		}
		else {

			printf("Invalid Machine code");
			exit(0);
		}
	}
	else if (!strcmp(opcode, "0100011")) {

		//printf("S\n");
		imm = Substring(binary, 0, 7);
		strcat(imm, Substring(binary, 20, 5));
		rs2 = Substring(binary, 7, 5);
		rs1 = Substring(binary, 12, 5);
		funct3 = Substring(binary, 17, 3);
		//printf("%s %s %s %s\n%d %d %d %d\n", imm, rs2, rs1, funct3, Bin_Dec(imm, 1), Bin_Dec(rs2, 0), Bin_Dec(rs1, 0), Bin_Dec(funct3, 0));

		switch (Bin_Dec(funct3, 0)) {

			case 0 :
				statement = strdup("sb");
				break;
			case 1 :
				statement = strdup("sh");
				break;
			case 2 :
				statement = strdup("sw");
				break;
			case 3 :
				statement = strdup("sd");
				break;
			default :
				printf("Invalid Machine Code\n");
				exit(0);		
		}	

		strcat(statement, " ");
		strcat(statement, "x");
		sprintf(temp1, "%d", Bin_Dec(rs2, 0));
		strcat(statement, temp1);
		strcat(statement, " ");
		sprintf(temp1, "%d", Bin_Dec(imm, 1));
		strcat(statement, temp1);
		strcat(statement, "(");
		strcat(statement, "x");
		sprintf(temp1, "%d", Bin_Dec(rs1, 0));
		strcat(statement, temp1);
		strcat(statement, ")");			
	}
	else if (!strcmp(opcode, "1100011")) {

		//printf("B\n");
		imm = Substring(binary, 0, 1);
		strcat(imm, Substring(binary, 24, 1));
		strcat(imm, Substring(binary, 1, 6));
		strcat(imm, Substring(binary, 20, 4));
		strcat(imm, "0");
		rs1 = Substring(binary, 12, 5);
		rs2 = Substring(binary, 7, 5);
		funct3 = Substring(binary, 17, 3);
		//printf("%s %s %s %s\n%d %d %d %d\n", imm, rs2, rs1, funct3, Bin_Dec(imm, 1), Bin_Dec(rs2, 0), Bin_Dec(rs1, 0), Bin_Dec(funct3, 0));


		offset = Bin_Dec(imm, 1) / 4;
		temp2 = list[program_counter + offset];

		if (temp2[1] != 'L') {

			temp3 = strdup("\nL");
			sprintf(temp1, "%d", label_counter++);
			strcat(temp3, temp1);
			strcat(temp3, ":\n");
			strcat(temp3, temp2);
			list[program_counter + offset] = strdup(temp3);
		}

		switch (Bin_Dec(funct3, 0)) {

			case 0 :
				statement = strdup("beq");
				break;
			case 1 :
				statement = strdup("bne");
				break;
			case 4 :
				statement = strdup("blt");
				break;
			case 5 :
				statement = strdup("bge");
				break;
			case 6 :
				statement = strdup("bltu");
				break;
			case 7 :
				statement = strdup("bgeu");
				break;
			default :
				printf("Invalid Machine Code\n");
				break;
		}

		strcat(statement, " ");
		strcat(statement, "x");
		sprintf(temp1, "%d", Bin_Dec(rs1, 0));
		strcat(statement, temp1);
		strcat(statement, " ");
		strcat(statement, "x");
		sprintf(temp1, "%d", Bin_Dec(rs2, 0));
		strcat(statement, temp1);
		strcat(statement, " ");
		strcat(statement, Substring(list[program_counter + offset], 1, 2));
	}
	else if (!strcmp(opcode, "0110111") || !strcmp(opcode, "0010111")) {

		//printf("U\n");
		imm = Substring(binary, 0, 20);
		strcat(binary, "000000000000");
		rd = Substring(binary, 20, 5);
		//printf("%s %s\n%d %d\n", imm, rd, Bin_Dec(imm, 1), Bin_Dec(rd, 0));

		if (!strcmp(opcode, "0110111")) statement = strdup("lui");
		else if (!strcmp(opcode, "0010111")) statement = strdup("auipc");
		else {

			printf("Invalid Machine Code\n");
			exit(0);
		}

		strcat(statement, " ");
		strcat(statement, "x");
		sprintf(temp1, "%d", Bin_Dec(rd, 0));
		strcat(statement, temp1);
		strcat(statement, " ");
		sprintf(temp1, "%d", Bin_Dec(imm, 1));
		strcat(statement, temp1);
	}
	else if (!strcmp(opcode, "1101111")) {

		//printf("J\n");
		imm = Substring(binary, 0, 1);
		strcat(imm, Substring(binary, 12, 8));
		strcat(imm, Substring(binary, 11, 1));
		strcat(imm, Substring(binary, 1, 10));
		strcat(imm, "0");
		rd = Substring(binary, 20, 5);		
		//printf("%s %s\n%d %d\n", imm, rd, Bin_Dec(imm, 1), Bin_Dec(rd, 0));

		offset = Bin_Dec(imm, 1) / 4;
		temp2 = list[program_counter + offset];

		if (temp2[1] != 'L') {

			temp3 = strdup("\nL");
			sprintf(temp1, "%d", label_counter++);
			strcat(temp3, temp1);
			strcat(temp3, ":\n");
			strcat(temp3, temp2);
			list[program_counter + offset] = strdup(temp3);
		}

		statement = strdup("jal");
		strcat(statement, " ");
		strcat(statement, "x");
		sprintf(temp1, "%d", Bin_Dec(rd, 0));
		strcat(statement, temp1);
		strcat(statement, " ");
		strcat(statement, Substring(list[program_counter + offset], 1, 2));
	}
	else {
		printf("Invalid Assembly Instruction\n");
		exit(0);
	}
	//printf("%s\n", statement);
	strcat(list[program_counter], statement);
}

// Prints the list
void Print_list() {

	for (int i = 0 ; i < program_counter ; i += 1) printf("\n%s", list[i]);
}

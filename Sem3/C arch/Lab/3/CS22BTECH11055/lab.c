#include"Header.h" // Custon header file that contains the functions used throughout the program

int main (int argc, char *argv[]) {

	for (int i = 0 ; i < 128 ; i++) list[i] = strdup(""); // Initialising the list that will contain all the converted instructions
	char path[512]; // Path to the input file
	printf("Enter The Path To The Input File :\n");
	scanf("%s", path);
	FILE* file;
	file = fopen(path, "r");

	if (file ==  NULL) {

		printf("File Not Found\n"); 
		exit(0); 
	}

	char line[512]; // To read the input file line by line
	int count; // To terminate the heaxdecimal code read from the input file
	printf("\nGiven Machine Code :\n\n");

	while (fgets(line, sizeof(line), file) != NULL) {

		if (line[0] == '\n' || line[0] == ' ') continue;
		
		char instruction[10];
		char* binary_inst;
		char* opcode;

		for (int i = 0 ; line[i] != '\0' && line[i] != '\n' && line[i] != ' '; i++) {

			instruction[i] = line[i];
			count = i;
		}		

		instruction[count + 1] = '\0';
		binary_inst = Hexa_Bin(instruction); // Converting hexadecimal instruction to binary instruction
		printf("%s\n", instruction);
		//printf("%s\n", binary_inst);
		opcode = Substring(binary_inst, 25, 7); // Obtaining opcode from the converted instruction
		Add_instruction(opcode, binary_inst); // Converting binary instruction to assembly instruction and appening it to the list
		program_counter++; // Keeps track of current instruction
	}

	printf("\nConverted Code :\n");
	Print_list();
	printf("\n");
	return 0;
}

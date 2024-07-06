#include"Header.h"

void Detect_hazard() {
	
	for (int i = 0 ; i < count; i++) {
				
		int j;
		char* line1 = strdup(list[i]);
		char* token;
		char* argv1[4];
		char* argv2[4];
		char* argv3[4];
		int rd1;
		int rd2;
		int rs21;
		int rs22;
		int rs31;
		int rs32;	 
		
		j = 0;
		token = strtok(line1, " ");
		while (token != NULL) {
				
			argv1[j++] = strdup(token);
			token = strtok(NULL, " ");
		}
		
		if (line1[0] == 's' && strlen(argv1[0]) == 2) continue;
		
		argv1[1][strlen(argv1[1]) - 1] = '\0';
		rd1 = Reg_identify(argv1[1]);
		if (rd1 == 0) continue;
		
		if ((i + 2) < count) {	
			
			char* line2 = strdup(list[i + 1]);
			char* line3 = strdup(list[i + 2]);
			
			j = 0;
			token = strtok(line2, " ");
			while (token != NULL) {
				
				argv2[j++] = strdup(token);
				token = strtok(NULL, " ");
			
			}
			
			j = 0;
			token = strtok(line3, " ");
			while (token != NULL) {
				
				argv3[j++] = strdup(token);
				token = strtok(NULL, " ");
			}			
			
			if (line2[0] == 'l' && strlen(argv2[0]) == 2) {
				
				char* tok = strdup("");
				int k = 0;
				while (argv2[2][k] != '(') k++;
				k++;
				while (argv2[2][k] != ')') {
					
					char temp[2];
					temp[0] = argv2[2][k++];
					temp[1] = '\0';
					strcat(tok, temp);
				}
				argv2[1][strlen(argv2[1]) - 1] = '\0';
				rd2 = Reg_identify(argv2[1]);
				rs21 = Reg_identify(tok);
				rs22 = -1;
				free(tok);
			}
			else if (line2[0] == 's' && strlen(argv2[0]) == 2) {
			
				char* tok = strdup("");
				int k = 0;
				while (argv2[2][k] != '(') k++;
				k++;
				while (argv2[2][k] != ')') {
					
					char temp[2];
					temp[0] = argv2[2][k++];
					temp[1] = '\0';
					strcat(tok, temp);
				}
				rd2 = -1;
				rs22 = Reg_identify(tok);
				argv2[1][strlen(argv2[1]) - 1] = '\0';
				rs21 = Reg_identify(argv2[1]);
				free(tok);			
			}
			else {
				argv2[1][strlen(argv2[1]) - 1] = '\0';
				rd2 = Reg_identify(argv2[1]);
				argv2[2][strlen(argv2[2]) - 1] = '\0';
				rs21 = Reg_identify(argv2[2]);
				rs22 = Reg_identify(argv2[3]);
			}
			
			if (line3[0] == 'l' && strlen(argv3[0]) == 2) {
				
				char* tok = strdup("");
				int k = 0;
				while (argv3[2][k] != '(') k++;
				k++;
				while (argv3[2][k] != ')') {
					
					char temp[2];
					temp[0] = argv3[2][k++];
					temp[1] = '\0';
					strcat(tok, temp);
				}
				rs31 = Reg_identify(tok);
				rs32 = -1;
				free(tok);
			}
			else if (line3[0] == 's' && strlen(argv3[0]) == 2) {
			
				char* tok = strdup("");
				int k = 0;
				while (argv3[2][k] != '(') k++;
				k++;
				while (argv3[2][k] != ')') {
					
					char temp[2];
					temp[0] = argv3[2][k++];
					temp[1] = '\0';
					strcat(tok, temp);
				}
				rs32 = Reg_identify(tok);
				argv3[1][strlen(argv3[1]) - 1] = '\0';
				rs31 = Reg_identify(argv3[1]);
				free(tok);			
			}
			else {
				argv3[2][strlen(argv3[2]) - 1] = '\0';
				rs31 = Reg_identify(argv3[2]);
				rs32 = Reg_identify(argv3[3]);
			}
			
			if (line1[0] == 'l' && strlen(argv1[0]) == 2) if (rd1 == rs21 || rd1 == rs22) nop[i + 1] = 1;
		}
		else if ((i + 1) < count) {
			
			char* line2 = strdup(list[i + 1]);
			
			j = 0;
			token = strtok(line2, " ");
			
			while (token != NULL) {
				
				argv2[j++] = strdup(token);
				token = strtok(NULL, " ");
			
			}
			
			if (line2[0] == 'l' && strlen(argv2[0]) == 2) {
				
				char* tok = strdup("");
				int k = 0;
				while (argv2[2][k] != '(') k++;
				k++;
				while (argv2[2][k] != ')') {
					
					char temp[2];
					temp[0] = argv2[2][k++];
					temp[1] = '\0';
					strcat(tok, temp);
				}
				rs21 = Reg_identify(tok);
				rs22 = -1;
				free(tok);
			}
			else if (line2[0] == 's' && strlen(argv2[0]) == 2) {
			
				char* tok = strdup("");
				int k = 0;
				while (argv2[2][k] != '(') k++;
				k++;
				while (argv2[2][k] != ')') {
					
					char temp[2];
					temp[0] = argv2[2][k++];
					temp[1] = '\0';
					strcat(tok, temp);
				}
				rs22 = Reg_identify(tok);
				argv2[1][strlen(argv2[1]) - 1] = '\0';
				rs21 = Reg_identify(argv2[1]);
				free(tok);
			}
			else {
				argv2[2][strlen(argv2[2]) - 1] = '\0';
				rs21 = Reg_identify(argv2[2]);
				rs22 = Reg_identify(argv2[3]);
			}
			
			if (line1[0] == 'l' && strlen(argv1[0]) == 2) if (rd1 == rs21 || rd1 == rs22) nop[i + 1] = 1;
		}
	}
	return;
}

int main (int argc, char *argv[]) {

	int cycles;
	char path[512];
	printf("Enter the path to the input file :\n");
	scanf("%s", path);
    	FILE* file;
	file = fopen(path, "r");
	
	if (file == NULL) {
		
		printf("File can't be opened\n");
		exit(0);
	}	
	
	char line[512];
	
	while (fgets(line, sizeof(line), file) != NULL) {
		
		list[count] = strdup(line);
		count++;
	}
	
	printf("\nOriginal Assembly Code :\n");
	for (int i = 0 ; i < count ; i++) printf("%s", list[i]);
	
	Detect_hazard();
	
	printf("\n\nCorrected Assembly Code with Data Forwarding :\n");
	for (int i = 0 ; i < count ; i++) {
		
		if (nop[i] != 0) for (int j = 0 ; j < nop[i] ; j++) printf("NOP\n");
		printf("%s", list[i]);
	}
	
	fclose(file);
	for (int i = 0; i < count; i++) free(list[i]);
	
	for (int i = 0 ; i < count ; i++) nop_count += nop[i];
	cycles = (count + nop_count) + 5 - 1;
	printf("\n\nCycles Required : %d\n", cycles);
	
	return 0;
}

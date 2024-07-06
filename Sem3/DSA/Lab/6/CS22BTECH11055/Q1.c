#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<ctype.h>   
#define ll long long

int dataset_size;
int hash_size;
int input_size;

int* Generate_hash() {
	
	int* coeff = (int*)malloc(2 * sizeof(int));
	coeff[0] = rand() % input_size + 1;
	coeff[1] = rand() % input_size + 1;
	return coeff;
}

int* Level_generate(int size) {
	
	int* level2 = (int*)malloc(size * size * sizeof(int));
	return level2;
}

int Hash1(int a, int x, int b) {
	
	return (a * x % b) % hash_size;
}

int Hash2(int a, int x, int b, int size) {
	
	return (a * x % b) % (size * size);
}

int main () {
	
	int TP;
	TP = 0;
	int FP;
	FP = 0;
	srand(time(0));
	input_size = 0;
	int val;
	FILE* file;
	file = fopen("T10I4D100K.dat", "r");
	
	if (file == NULL) printf("File doesn't exist\n");
	
	char buffer[512];
	
	while (fgets(buffer, 512, file)) {
	
		for(int i = 0 ; i < strlen(buffer) ; i++) {
		
			if (buffer[i] == ' ') input_size++;
		}
		input_size++;
	}
	
	//printf("%d\n", input_size);
	fclose(file);
	file = fopen("T10I4D100K.dat", "r");

	dataset_size = input_size / 20;
	int input[input_size];
	int test[dataset_size * 2];
	
	for (int i = 0 ; i < input_size ; i++) fscanf(file, "%d", &input[i]);

	fclose(file);
	file = fopen("T10I4D100K.dat", "r");

	for(int i = 0 ; i < dataset_size ; i++) fscanf(file, "%d", &test[i]);
	for (int i = dataset_size ; i < dataset_size * 2 ; i++) test[i] = rand() % 1000 + 1;
	//for (int i = 0 ; i < dataset_size * 2 ; i++) printf("%d ", input[i]);
	//printf("\n");
	 
	hash_size = input_size / 100;
	int collision_table[hash_size];
	
	int* hash1;
	int hash1_trials;
	hash1_trials = 0;
	int* hash_table[hash_size];
	int c;
	c = 0.5;	
	int square_sum;
	
	while (square_sum >= c * input_size) {
		
		for (int i = 0 ; i < hash_size ; i++) collision_table[i] = 0; 
		square_sum = 0;
		hash1 = Generate_hash();
		
		for (int i = 0 ; i < input_size ; i++) {
		
			int pos;
			pos = Hash1(hash1[0], input[i], hash1[1]);
			//pos = ((hash1[0] * input[i]) % hash1[1]) % hash_size;
			collision_table[pos]++;
		}
		
		
		for (int i = 0 ; i < hash_size ; i++) square_sum += (collision_table[i] * collision_table[i]);
		
		hash1_trials++;
	}
		
	
	for (int i = 0 ; i < hash_size ; i++) hash_table[i] = Level_generate(collision_table[i]);
	
	int* hash2[hash_size];
	
	for (int i = 0 ; i < hash_size ; i++) {
		
		int elements[input_size];
		int count;
		count = 0;
		
		for (int j = 0 ; j < input_size ; j++) {
			
			if (Hash1(hash1[0], input[j], hash1[1]) == i) {
			
				elements[count] = input[j];
				count++;
			} 
		}
		
		while(1) {
			
			int flag;
			flag = 0;
			hash2[i] = Generate_hash();
			
			for (int k = 0 ; k < count ; k++) {
				
				for (int l = 0 ; l < count ; l++) {
					
					if (l != k && Hash2(hash2[i][0], elements[l], hash2[i][1], collision_table[i]) == Hash2(hash2[i][0], elements[k], hash2[i][1], collision_table[i])) flag == 1;
				}
			}
			
			if (!flag) break; 
		}
	}
	
	//for (int i = 0 ; i < hash_size ; i++) printf("%d %d\n", hash2[i][0], hash2[i][1]);
	
	for (int i = 0 ; i < input_size ; i++) {
		
		int pos1;
		int pos2;
		pos1 = Hash1(hash1[0], input[i], hash1[1]);
		pos2 = Hash2(hash2[pos1][0], input[i], hash2[pos1][1], collision_table[pos1]);
		int* lvl1;
		lvl1 = hash_table[pos1];
		lvl1[pos2] = input[i];
	}
	
	for (int i = 0 ; i < hash_size ; i++) {
		
		int* lvl;
		lvl = hash_table[i];
		printf("%d : ", i);
		
		for (int j = 0 ; j < collision_table[i] * collision_table[i] ; j++) if (lvl[j] != 0) printf("%d ", lvl[j]);
		
		printf("\n");
	}

	for (int i = 0 ; i < dataset_size * 2 ; i++) {
		
		int pos1 = Hash1(hash1[0], test[i], hash1[1]);
		int pos2 = Hash2(hash2[pos1][0], test[i], hash2[pos1][1], collision_table[pos1]);
		int* lvl = hash_table[pos1];
		
		if (lvl[pos2] == test[i]) TP++;
		else FP++;
	}
	
	
	printf("TP : %d\t FP : %d\nTN : %d\tFN : 0\n", TP, FP, input_size);	
	//printf("%d %d %d %d %d", hash1[0], hash1[1], hash1_trials, dataset_size, hash_size);
	return 0;
}




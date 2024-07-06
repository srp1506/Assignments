#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int n;
int num_threads;
int count = 0;
//pthread_mutex_t log_mutex;
FILE* log;

int Count(int num) {

	int count = 0;

	while (num != 0) {

		num /= 10;
		count++;
	}
	return count;
}

bool Vampire(int num) {

	int temp;
	int num_digits = Count(num);

	if (num_digits % 2 != 0 || num_digits <= 2) return 0;

	int original_digits[10] = {0};
	
	temp = num;
	while (temp) {
		
		original_digits[temp % 10]++;
		temp /= 10;
	}

	for (int i = 1 ; i * i <= num ; i++) {

		if (num % i == 0) {

			int factor1 = i;
			int factor2 = num / i;
			if (factor1 % 10 == 0 && factor2 % 10 == 0) continue;

			if (Count(factor1) != num_digits / 2 || Count(factor2) != num_digits / 2) continue;

			int factor_digits[10] = {0};
			
			temp = factor1;
			while (temp) {
		
				factor_digits[temp % 10]++;
				temp /= 10;
			}
			
			temp = factor2;
			while (temp) {
		
				factor_digits[temp % 10]++;
				temp /= 10;
			}
			
			int flag = 1;

			for (int i = 0 ; i < 10 ; i++) {
				
				if (original_digits[i] != factor_digits[i]) {
					
					flag = 0;
					break;
				}
			}
			
			if (flag) return 1;
		}
	}
	return 0;
}

void* Routine(void* arg) {
	
	int num = *((int*)arg);
	//pthread_mutex_lock(&log_mutex);
		
	for (int i = num + 1 ; i <= n ; i+= num_threads) if (Vampire(i)) {
			fprintf(log, "%d : Identified by %d\n", i, num + 1);
			count++;
		} 
	//pthread_mutex_unlock(&log_mutex);
	return NULL;
}

int main() {
	
	//char* path;
	char* path = "input.txt";
	FILE* file;
	//printf("Enter the path of the input file : \n");
	//scanf("%s", path);

	file = fopen(path, "r");

	if (file ==  NULL) {

		printf("File Not Found\n"); 
		exit(0); 
	}

	fscanf(file, "%d %d", &n, &num_threads);
	struct timeval start_time, end_time;	
		
	log = fopen("OutFile.log", "w");

	if (log == NULL) {

		perror("Error Opening Log File");
		exit(1);
	}
	
	pthread_t threads[num_threads];
	//pthread_mutex_init(&log_mutex, NULL);
	//printf(Vampire(1260) ? "Yes\n" : "No\n");
	
	gettimeofday(&start_time, NULL);
	
	for (int i = 0 ; i < num_threads ; i++) {
		
		int* thread_id = malloc(sizeof(int));
        	*thread_id = i;
		
		if (pthread_create(&threads[i], NULL, Routine, (void*)thread_id) != 0) {
            		
            		printf("Error creating thread %d\n", i + 1);
            		exit(1);
        	}
	}
	
	for (int i = 0 ; i < num_threads ; ++i) {
    
        	if (pthread_join(threads[i], NULL) != 0) {
            		
            		fprintf(stderr, "Error joining thread %d\n", i + 1);
            		exit(1);
    	    	}
    	}
    	
    	gettimeofday(&end_time, NULL);
    	fprintf(log, "Elapsed time is : %f\n", (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) * 1e-6);
    	fprintf(log, "Number of vampire numbers from 1 to %d : %d\n", n, count);
    	
    	fclose(log);
    	//pthread_mutex_destroy(&log_mutex);
	return 0;
}

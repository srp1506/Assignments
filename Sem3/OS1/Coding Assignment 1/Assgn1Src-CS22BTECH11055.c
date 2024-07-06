#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/time.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/mman.h>

int n;
int num_processes;
int count = 0;

int Tetrahedral(int num) {

	int n = 1;

	while (1) {

		int tetrahedralNumber = (n * (n + 1) * (n + 2)) / 6;
		if (tetrahedralNumber == num) return 1;
		else if (tetrahedralNumber > num) return 0;
		n++;
	}
}

int main(int argc, char *argv[]) {

	//char* path;
	char* path = "input.txt";
	FILE* file;
	//printf("Enter the path of the input file : \n");
	//scanf("%s", path);

	file = fopen(path, "r");

	if (file == NULL) {

		printf("File Not Found\n");
		exit(0);
	}

	pid_t pid;
	struct timeval start_time, end_time;

	fscanf(file, "%d %d", &n, &num_processes);
	// printf("%d %d\n", n, num_processes);
	for (int i = 0 ; i < num_processes ; i++) {

		char name[20];
		snprintf(name, sizeof(name), "child%d", i + 1);
		int main_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
		ftruncate(main_fd, ((n / num_processes) + (n % num_processes)) * sizeof(int));

		if (main_fd == -1) {

			printf("Shared Memory Allocation Failed\n");
			exit(1);
		}
	}

	gettimeofday(&start_time, NULL);

	for (int i = 0; i < num_processes; i++) {

		pid = fork();

		if (pid == 0) {

			int count = 0;
			char name[20];
			snprintf(name, sizeof(name), "child%d", i + 1);
			int child_fd = shm_open(name, O_RDWR, 0666);

			if (child_fd == -1) {

				printf("Shared Memory Allocation Failed\n");
				exit(1);
			}

			int* child_ptr = mmap(NULL, ((n / num_processes) + (n % num_processes)) * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, child_fd, 0);

			if (child_ptr == (int*)-1) {

				printf("Error Mapping\n");
				exit(1);
			}

			for (int i = 0 ; i < ((n / num_processes) + (n % num_processes)) ; i++) child_ptr[i] = 0;

			char logFile[20];
			snprintf(logFile, sizeof(logFile), "OutFile_%d.log", i + 1);
			FILE* log = fopen(logFile, "w");

			if (log == NULL) {

				perror("Error Opening Log File\n");
				exit(1);
			}

			for (int j = i + 1; j <= n; j += num_processes) {

				if (Tetrahedral(j)) {

					fprintf(log, "%d is a tetrahedral number\n", j);
					child_ptr[count++] = j;
				}
				else fprintf(log, "%d is not a tetrahedral number\n", j);
			}
			fclose(log);
			exit(0);
		}
	}

	for (int i = 0; i < num_processes; i++) wait(NULL);

	gettimeofday(&end_time, NULL);

	FILE* logMain = fopen("OutMain.log", "w");

	if (logMain == NULL) {

		perror("Error Opening Log File\n");
		exit(1);
	}

	fprintf(logMain, "Tetrahedral numbers within the range 1 to %d :\n", n);

	for (int i = 0; i < num_processes; i++) {
		
		char name[20];
		snprintf(name, sizeof(name), "child%d", i + 1);
		int child_fd = shm_open(name, O_RDWR, 0666);
		int* child_ptr = mmap(NULL, ((n / num_processes) + (n % num_processes)) * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, child_fd, 0);
		int j = 0;
		fprintf(logMain, "Process %d : ", i + 1);
		while (child_ptr[j] != 0) {
			
			fprintf(logMain, "%d ", child_ptr[j]);
			j++;
			count++;
		}
		fprintf(logMain, "\n");
	}
	fprintf(logMain, "Elapsed time is : %f\n", (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) * 1e-6);
	fprintf(logMain, "Count : %d\n", count);
	fclose(logMain);
	
	for (int i = 0 ; i < num_processes ; i++) {
		
		char name[20];
		snprintf(name, sizeof(name), "child%d", i + 1);	
		
		if (shm_unlink(name) == -1) {

			printf("Shared Memory Deletion Failed\n");
			exit(1);
		}
	}
	fclose(file);
	return 0;
}

#include "Header.h"

void grep(char* para1, char* para2, char* para3, char* para4) {

	if (para3 == NULL && para2 != NULL) {

		FILE* file = fopen(para2, "r");

		if (file == NULL) {

			printf("Error Opening File '%s'\n",para2);
			exit(1);
		}

		char buffer[1024];

		while (fgets(buffer, 1024, file) != NULL) {

			if (strstr(buffer, para1) != NULL) printf("%s\n",buffer);
		}

		fclose(file);
	}

	else {

		if (!strcmp(para1, "-m")) {

			int limit = atoi(para2);
			FILE* file = fopen(para4, "r");

			if (file == NULL) {

				printf("Error Opening File '%s'\n",para4);
				exit(1);
			}

			char buffer[1024];
			int count = 0;

			while (fgets(buffer, 1024, file) != NULL) {

				if (strstr(buffer, para3) != NULL) {

					count++;
					printf("%s\n",buffer);
				}

				if (count == limit) break;
			}

			fclose(file);
		}

		else if (!strcmp(para1, "-v")) {

			FILE* file = fopen(para3, "r");

			if (file == NULL) {

				printf("Error Opening File '%s'\n",para3);
				exit(1);
			}

			char buffer[1024];

			while (fgets(buffer, 1024, file) != NULL) {

				if (strstr(buffer, para2) == NULL) printf("%s\n",buffer);
			}

			fclose(file);
		}

		else if(!strcmp(para1, "-n")) {

			FILE* file = fopen(para3, "r");

			if (file == NULL) {

				printf("Error Opening File '%s'\n",para3);
				exit(1);
			}

			char buffer[1024];
			int lineNum = 1;

			while (fgets(buffer, 1024, file) != NULL) {

				if (strstr(buffer, para2) != NULL) {

					printf("%d : %s\n",lineNum, buffer);
				}

				lineNum++;
			}

			fclose(file);
		}

		else if(!strcmp(para1, "-o")) {

			FILE* file = fopen(para3, "r");

			if (file == NULL) {

				printf("Error Opening File '%s'\n",para3);
				exit(1);
			}

			char buffer[1024];
			int lineNum = 1;

			while (fgets(buffer, 1024, file) != NULL) {

				if (strstr(buffer, para2) != NULL) {

					printf("%s\n",para2);
				}

				lineNum++;
			}

			fclose(file);
		}
	}
}

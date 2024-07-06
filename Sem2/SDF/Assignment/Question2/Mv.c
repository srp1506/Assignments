#include "Header.h"

void mv(char* para1, char* para2, char* para3) {

	if (para3 == NULL && para2 != NULL) {

		int status = rename(para1, para2);

		if (status != 0) {
			printf("Error Moving File\n");
			exit(1);
		}
	}

	else {

		if (!strcmp(para1, "-i")) {

			struct stat statBuffer;

			if (stat(para3, &statBuffer) == 0) {

				char choice;
				printf("Do You Want To Overwrite '%s'? (y/n)\n",para3);
				scanf(" %c", &choice);

				if (choice != 'Y' && choice != 'y') {

					printf("Not Overwriting '%s'\n",para3);
					exit(0);
				}
			}

			int status = rename(para2, para3);

			if (status != 0) {

				printf("Error Moving File\n");
				exit(1);
			}
		}

		else if (!strcmp(para1, "-u")) {

			struct stat statSource;
			struct stat statDestination;

			if (stat(para2, &statSource) == 0 && stat(para3, &statDestination) == 0) if (statSource.st_mtime > statDestination.st_mtime) {

				int status = rename(para2, para3);

				if (status != 0) {

					printf("Error Moving File\n");
					exit(1);
				}
			}

		}

		else if (!strcmp(para1, "-v")) {

			int status = rename(para2, para3);

			if (status != 0) {

				printf("Error Moving File\n");
				exit(1);
			}

			printf("Renamed '%s' -> '%s'\n",para2, para3);
		}

		else if (!strcmp(para1, "-n")) {

			struct stat statDestination;

			if (stat(para3, &statDestination) != -1) {

				printf("cp: File '%s' Already Exists\n",para3);
				exit(1);
			}

			int status = rename(para2, para3);

			if (status != 0) {

				printf("Error Moving File\n");
				exit(1);
			}
		}

		else if (!strcmp(para1, "-f")) {

			int status = rename(para1, para2);

			if (status != 0) {
				printf("Error Moving File\n");
				exit(1);
			}
		}
	}
}


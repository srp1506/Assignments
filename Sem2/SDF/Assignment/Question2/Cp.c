#include "Header.h"

void CopyFile(const char*, const char*);

void cp(char* para1, char* para2, char* para3) {

	if (para3 == NULL && para2 != NULL) {

		CopyFile(para1, para2);
	}

	else {

		if (!strcmp(para1, "-i")) {

			struct stat statBuffer;

			if (stat(para3, &statBuffer) == 0) {

				char choice;
				printf("Do You Want To Overwrite '%s'? (y/n) ",para3);
				scanf(" %c", &choice);

				if (choice != 'Y' && choice != 'y') {

					printf("Not Overwriting '%s'\n",para3);
					exit(0);
				}
			}

			CopyFile(para2, para3);
		}	

		else if (!strcmp(para1, "-u")) {

			struct stat statSource;
			struct stat statDestination;

			if (stat(para2, &statSource) == 0 && stat(para3, &statDestination) == 0) if (statSource.st_mtime > statDestination.st_mtime) CopyFile(para2, para3);
		}

		else if (!strcmp(para1, "-v")) {

			CopyFile(para2, para3);

			printf("'%s' -> '%s'\n",para2, para3);
		}

		else if (!strcmp(para1, "-n")) {

			struct stat statDestination;

			if (stat(para3, &statDestination) != -1) {

				printf("cp: File '%s' Already Exists\n",para3);
				exit(1);
			}

			CopyFile(para2, para3);
		}

		else if (!strcmp(para1, "-l")) {

			int status = link(para2, para3);

			if (status != 0) {

				printf("Error Linking Files\n");
				exit(1);
			}
		}
	}
}

void CopyFile(const char* srcPath, const char* destPath) {

	int source = open(srcPath, O_RDONLY);

	if (source == -1) {

		printf("Error Opening Source File '%s'\n",srcPath);
		exit(1);
	}

	int destination = open(destPath, O_WRONLY | O_CREAT | O_TRUNC, 0666);

	if (destination == -1) {

		printf("Error Opening Destination File '%s'\n",destPath);
		close(source);
		exit(1);
	}

	char buffer[BUFSIZ];
	ssize_t charRead;

	while ((charRead = read(source, buffer, BUFSIZ)) > 0) {

		ssize_t charWritten = write(destination, buffer, charRead);

		if (charWritten != charRead || charWritten == -1) {

			printf("Error Writing To Destination File '%s'\n",destPath);
			close(source);
			close(destination);
			exit(1);
		}
	}

	if (charRead == -1) {

		printf("Error Reading Source File '%s'\n",srcPath);
		close(source);
		close(destination);
		exit(1);
	}

	if (close(source) == -1 || close(destination) == -1) {

		printf("Error Closing Files\n");
		exit(1);
	}

	struct stat srcData;
	if (stat(srcPath, &srcData) == 0) chmod(destPath, srcData.st_mode);
}


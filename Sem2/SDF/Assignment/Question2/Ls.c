#include "Header.h"

void PrintPermissions(mode_t);

void ls(char* option) {

	struct dirent* dirInfo;
	DIR* directory = opendir(".");
	struct stat entity;
	struct passwd* owner;
	struct group* group;
	char time[80];
	int totalBlocks = 0;

	if (option == NULL) {

		for (dirInfo = readdir(directory) ; dirInfo != NULL ; dirInfo = readdir(directory)) {

			stat(dirInfo->d_name, &entity);
			char* name = dirInfo->d_name;

			if (name[0] != '.' && S_ISDIR(entity.st_mode)) printf("\x1b[34m\e[1m%s\n\x1b[0m",dirInfo->d_name);

			else if (name[0] != '.' && (S_IXUSR & entity.st_mode)) printf("\x1b[32m\e[1m%s\n\x1b[0m",dirInfo->d_name);

			else if (name[0] != '.')printf("%s\n",dirInfo->d_name);
		}
	}

	else if (!strcmp(option, "-l")) {

		for (dirInfo = readdir(directory) ; dirInfo != NULL ; dirInfo = readdir(directory)) {

			stat(dirInfo->d_name, &entity);
			char* copy = dirInfo->d_name;

			if (copy[0] != '.') {

				long int fileSize = (unsigned long)entity.st_size;
				int blocks = fileSize % 4096 == 0 ? 4 * (fileSize / 4096) : 4 * (fileSize / 4096 + 1);
				totalBlocks += blocks; 
				PrintPermissions(entity.st_mode);

				printf(" %ld",(long)entity.st_nlink);

				owner = getpwuid(entity.st_uid);
				owner == NULL ? printf("%5ld ",(long)entity.st_uid) : printf("%5s ",owner->pw_name);

				group = getgrgid(entity.st_gid);
				group == NULL ? printf("%5ld ",(long)entity.st_gid) : printf("%5s ",group->gr_name);

				printf("%10ld ",(long)entity.st_size);

				strftime(time, sizeof(time), "%b %e %H:%M", localtime(&(entity.st_mtime)));
				printf("%s ",time);

				printf("%s\n",dirInfo->d_name);
			}
		}

		printf("total	%d\n",totalBlocks);
	}

	else if(!strcmp(option, "-a")) {

		for (dirInfo = readdir(directory) ; dirInfo != NULL ; dirInfo = readdir(directory)) {

			stat(dirInfo->d_name, &entity);

			if (S_ISDIR(entity.st_mode)) printf("\x1b[34m\e[1m%s\n\x1b[0m",dirInfo->d_name);

			else if(S_IXUSR & entity.st_mode) printf("\x1b[32m\e[1m%s\n\x1b[0m",dirInfo->d_name);

			else printf("%s\n",dirInfo->d_name);
		}
	}

	else if (!strcmp(option, "-i")) {

		for (dirInfo = readdir(directory) ; dirInfo != NULL ; dirInfo = readdir(directory)) {

			stat(dirInfo->d_name, &entity);
			char* name = dirInfo->d_name;
			ino_t index = entity.st_ino;

			if (name[0] != '.' && S_ISDIR(entity.st_mode)) printf("%lu \x1b[34m\e[1m%s\n\x1b[0m",(unsigned long)index, dirInfo->d_name);

			else if (name[0] != '.' && (S_IXUSR & entity.st_mode)) printf("%lu \x1b[32m\e[1m%s\n\x1b[0m",(unsigned long)index, dirInfo->d_name);

			else if (name[0] != '.')printf("%lu %s\n",(unsigned long)index, dirInfo->d_name);
		}
	}

	else if (!strcmp(option, "-s")) {

		for (dirInfo = readdir(directory) ; dirInfo != NULL ; dirInfo = readdir(directory)) {

			stat(dirInfo->d_name, &entity);
			char* name = dirInfo->d_name;

			if (name[0] != '.') {

				long int fileSize = (unsigned long)entity.st_size;
				int blocks = fileSize % 4096 == 0 ? 4 * (fileSize / 4096) : 4 * (fileSize / 4096 + 1);

				totalBlocks += blocks;

				if (name[0] != '.' && S_ISDIR(entity.st_mode)) printf("%d \x1b[34m\e[1m%s\n\x1b[0m",blocks, dirInfo->d_name);

				else if (name[0] != '.' && (S_IXUSR & entity.st_mode)) printf("%d \x1b[32m\e[1m%s\n\x1b[0m",blocks, dirInfo->d_name);

				else if (name[0] != '.')printf("%d %s\n",blocks, dirInfo->d_name);
			}
		}

		printf("total	%d\n",totalBlocks);
	}

	else if (!strcmp(option, "-o")) {

		for (dirInfo = readdir(directory) ; dirInfo != NULL ; dirInfo = readdir(directory)) {

			stat(dirInfo->d_name, &entity);
			char* copy = dirInfo->d_name;

			if (copy[0] != '.') {

				long int fileSize = (unsigned long)entity.st_size;
				int blocks = fileSize % 4096 == 0 ? 4 * (fileSize / 4096) : 4 * (fileSize / 4096 + 1);
				totalBlocks += blocks; 
				PrintPermissions(entity.st_mode);

				printf(" %ld",(long)entity.st_nlink);

				owner = getpwuid(entity.st_uid);
				owner == NULL ? printf("%5ld ",(long)entity.st_uid) : printf("%5s ",owner->pw_name);

				printf("%10ld ",(long)entity.st_size);

				strftime(time, sizeof(time), "%b %e %H:%M", localtime(&(entity.st_mtime)));
				printf("%s ",time);

				printf("%s\n",dirInfo->d_name);
			}
		}

		printf("total	%d\n",totalBlocks);
	}

	else if (!strcmp(option, "-g")) {

		for (dirInfo = readdir(directory) ; dirInfo != NULL ; dirInfo = readdir(directory)) {

			stat(dirInfo->d_name, &entity);
			char* copy = dirInfo->d_name;

			if (copy[0] != '.') {

				long int fileSize = (unsigned long)entity.st_size;
				int blocks = fileSize % 4096 == 0 ? 4 * (fileSize / 4096) : 4 * (fileSize / 4096 + 1);
				totalBlocks += blocks; 
				PrintPermissions(entity.st_mode);

				printf(" %ld",(long)entity.st_nlink);

				group = getgrgid(entity.st_gid);
				group == NULL ? printf("%5ld ",(long)entity.st_gid) : printf("%5s ",group->gr_name);

				printf("%10ld ",(long)entity.st_size);

				strftime(time, sizeof(time), "%b %e %H:%M", localtime(&(entity.st_mtime)));
				printf("%s ",time);

				printf("%s\n",dirInfo->d_name);
			}
		}

		printf("total	%d\n",totalBlocks);
	}

	closedir(directory);
}

void PrintPermissions(mode_t mode) {

	printf( (S_ISDIR(mode)) ? "d" : "-");
	printf( (mode & S_IRUSR) ? "r" : "-");
	printf( (mode & S_IWUSR) ? "w" : "-");
	printf( (mode & S_IXUSR) ? "x" : "-");
	printf( (mode & S_IRGRP) ? "r" : "-");
	printf( (mode & S_IWGRP) ? "w" : "-");
	printf( (mode & S_IXGRP) ? "x" : "-");
	printf( (mode & S_IROTH) ? "r" : "-");
	printf( (mode & S_IWOTH) ? "w" : "-");
	printf( (mode & S_IXOTH) ? "x" : "-");
}

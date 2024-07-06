#include "Header.h" 

void GetProcessInfo(char*, char*, char*, char*);

typedef struct ProcessInfo {

	char cmd[100];
	long int pid;
	char t[20];
	char sTime[10];
	unsigned int ppid;
	unsigned int psr;
	unsigned long sz, rss, c ,startime;
	char time[10];
}info;

void ps(char* option) {

	info process[1000];
	DIR* directory;
	struct dirent* entity;
	struct tm* timeData;
	directory = opendir("/proc/");
	int count = 0;
	unsigned int processID;
	unsigned int ppid;
	unsigned int psr;
	unsigned long rss;
	unsigned long sz;
	unsigned long c;
	unsigned long startTime;
	unsigned long int uTime;
	unsigned long int sTime;
	char tty[20];
	char state;
	char cmd[512];
	char ttyCurrent[512];

	if (option == NULL) {

		char path[1024];
		char* tty;
		int i;
		int selfFD = open("/proc/self/fd/0", O_RDONLY);
		int fd;
		unsigned long t;
		char flag;
		char ttySelf[256];
		char timeS[256];

		FILE* file;
		sprintf(ttySelf, "%s", ttyname(selfFD));

		printf("%5s %-10s %10s %s\n", "PID", "TTY", "TIME", "CMD");

		while ((entity = readdir(directory)) != NULL) {

			flag = 1;

			for (i = 0 ; entity->d_name[i] ; i++) if (!isdigit(entity->d_name[i])) {

				flag = 0;
				break;
			}

			if (flag) {

				sprintf(path, "/proc/%s/fd/0", entity->d_name);
				fd = open(path, O_RDONLY);
				tty = ttyname(fd);

				if (tty && strcmp(tty, ttySelf) == 0) {

					sprintf(path, "/proc/%s/stat", entity->d_name);
					file = fopen(path, "r");
					fscanf(file, "%d%s%c%c%c", &i, cmd, &flag, &flag, &flag);
					cmd[strlen(cmd) - 1] = '\0';

					for (i = 0 ; i < 11 ; i++) fscanf(file, "%lu", &t);

					fscanf(file, "%lu", &sTime);
					t = (int)((double)(t + sTime) / sysconf(_SC_CLK_TCK));
					sprintf(timeS, "%02lu:%02lu:%02lu",
							(t / 3600) % 3600, (t / 60) % 60, t % 60);

					printf("%5s %-10s %10s %s\n", entity->d_name, tty + 5, timeS, cmd + 1);
					fclose(file);
				}
				close(fd);
			}
		}
	}

	else if (!strcmp(option, "-r")) {

		char path[1024];
		char* ty;
		char state;
		int selfFD = open("/proc/self/fd/0", O_RDONLY);
		int fd;
		unsigned long t;
		char flag;
		char ttySelf[256];
		char timeS[256];

		FILE* file;
		sprintf(ttySelf, "%s", ttyname(selfFD));

		printf("%5s %-10s %-5s %10s %s\n", "PID", "TTY", "STATE", "TIME", "CMD");

		while((entity = readdir(directory)) != NULL) {

			flag = 1;

			for (int i = 0 ; entity->d_name[i] ; i++) if (!isdigit(entity->d_name[i])) {

				flag = 0;
				break;
			}

			if (flag) {

				sprintf(path, "/proc/%s/fd/0", entity->d_name);
				fd = open(path, O_RDONLY);
				ty = ttyname(fd);

				if (ty && strcmp(ty, ttySelf) == 0) {

					sprintf(path, "/proc/%s/stat", entity->d_name);
					file = fopen(path, "r");
					fscanf(file, "%*d %s %c %c %c", cmd, &state, &flag, &flag);
					cmd[strlen(cmd) - 1] = '\0';

					if (state != 'R') continue;

					for (int i = 0 ; i < 11 ; i++) fscanf(file, "%lu", &t);
					fscanf(file, "%lu", &sTime);

					t = (int)((double)(t + sTime) / sysconf(_SC_CLK_TCK));
					sprintf(timeS, "%02lu:%02lu:%02lu", (t / 3600) % 3600, (t / 60) % 60, t % 60);
					printf("%5s %-10s %-5c %10s %s\n",entity->d_name, ty + 5, state, timeS, cmd + 1);
					fclose(file);
				}
				close(fd);
			}
		}
	}

	else if (!strcmp(option, "-t")) {

		char path[1024];
		char* ty;
		char state;
		int selfFD = open("/proc/self/fd/0", O_RDONLY);
		int fd;
		unsigned long t;
		char flag;
		char ttySelf[256];
		char timeS[256];

		FILE* file;
		sprintf(ttySelf, "%s", ttyname(selfFD));

		printf("%5s %-10s %-5s %10s %s\n", "PID", "TTY", "STATE", "TIME", "CMD");

		while((entity = readdir(directory)) != NULL) {

			flag = 1;

			for (int i = 0 ; entity->d_name[i] ; i++) if (!isdigit(entity->d_name[i])) {

				flag = 0;
				break;
			}

			if (flag) {

				sprintf(path, "/proc/%s/fd/0", entity->d_name);
				fd = open(path, O_RDONLY);
				ty = ttyname(fd);

				if (ty && strcmp(ty, ttySelf) == 0) {

					sprintf(path, "/proc/%s/stat", entity->d_name);
					file = fopen(path, "r");
					fscanf(file, "%*d %s %c %c %c", cmd, &state, &flag, &flag);
					cmd[strlen(cmd) - 1] = '\0';

					for (int i = 0 ; i < 11 ; i++) fscanf(file, "%lu", &t);
					fscanf(file, "%lu", &sTime);

					t = (int)((double)(t + sTime) / sysconf(_SC_CLK_TCK));
					sprintf(timeS, "%02lu:%02lu:%02lu", (t / 3600) % 3600, (t / 60) % 60, t % 60);
					printf("%5s %-10s %-5c %10s %s\n",entity->d_name, ty + 5, state, timeS, cmd + 1);
					fclose(file);
				}
				close(fd);
			}
		}
	}

	else if (!strcmp(option, "-d")) {

		char path[1024];
		char* ty;
		int i;
		int selfFD = open("/proc/self/fd/0", O_RDONLY);
		int fd;
		unsigned long t;
		char flag;
		char ttySelf[256];
		char timeS[256];

		FILE* file;
		sprintf(ttySelf, "%s", ttyname(selfFD));

		printf("%5s %-10s %10s %s\n", "PID", "TTY", "TIME", "CMD");

		while((entity = readdir(directory)) != NULL) {

			flag = 1;

			for (int i = 0 ; entity->d_name[i] ; i++) if (!isdigit(entity->d_name[i])) {

				flag = 0;
				break;
			}

			if (flag) {

				int sid = 0;
				int pid = atoi(entity->d_name);
				sprintf(path, "/proc/%s/fd/0", entity->d_name);
				fd = open(path, O_RDONLY);
				ty = ttyname(fd);

				sprintf(path, "/proc/%s/stat", entity->d_name);
				file = fopen(path, "r");
				fscanf(file, "%d %s %*c %*d %*d %d", &i, cmd, &sid);
				cmd[strlen(cmd) - 1] = '\0';

				for (int i = 0 ; i < 8 ; i++) fscanf(file, "%lu", &t);
				fscanf(file, "%lu", &sTime);

				t = (int)((double)(t + sTime) / sysconf(_SC_CLK_TCK));
				sprintf(timeS, "%02lu:%02lu:%02lu", (t / 3600) % 3600, (t / 60) % 60, t % 60);

				if (pid != sid) {

					if (ty == NULL) printf("%5s %-10c %10s %s\n",entity->d_name, '?', timeS, cmd + 1);

					else printf("%5s %-10s %10s %s\n",entity->d_name, ty + 5, timeS, cmd + 1);

					fclose(file);
				}
				close(fd);
			}
		}
	}

	else if (!strcmp(option, "-e")) {

		char time[10];
		printf("%5s %-10s %10s %s\n", "PID", "TTY", "TIME", "CMD");

		while ((entity = readdir(directory)) != NULL) {

			if (entity->d_type == DT_DIR && isdigit(entity->d_name[0])) {
				GetProcessInfo(entity->d_name, tty, time, cmd);

				char pathDescriptor[256];
				sprintf(pathDescriptor, "/proc/%ld/fd/0", atol(entity->d_name));

				ssize_t nbytes = readlink(pathDescriptor, tty, 20);

				if (nbytes >= 0) tty[nbytes] = '\0';

				else {

					tty[0] = '?';

					for (int i = 1 ; i < 9 ; i++) tty[i] = ' ';

					tty[9] = '\0';
				}
				printf("%5s %-10s %10s %s\n", entity->d_name, tty, time, cmd);
			}
		}
	}

	else if (!strcmp(option, "-a") || !strcmp(option, "-aF")) {

		char ttySelf[256];
		int selfFD = open("/proc/self/fd/0", O_RDONLY);
		sprintf(ttySelf, "%s", ttyname(selfFD));

		while ((entity = readdir(directory)) != NULL) {

			if (entity->d_type == DT_DIR && isdigit(entity->d_name[0])) {

				struct stat statDirectory;
				char* pid = entity->d_name;
				char statDirectoryPath[256];				
				int fd;

				sprintf(statDirectoryPath, "/proc/%ld/stat", atol(pid));

				if (stat(statDirectoryPath, &statDirectory) != 0) continue;

				char pathDescriptor[256];

				sprintf(pathDescriptor, "/proc/%s/fd/0", pid);

				if (access(pathDescriptor, F_OK) != 0) continue;

				if (fd = open(pathDescriptor, O_RDWR) < 0) continue;				

				if (ttyname(fd) == NULL) {

					close(fd);
					continue;
				}

				char ty[32];
				readlink(pathDescriptor, ty, 20);

				FILE* statFile = fopen(statDirectoryPath, "r");

				if (statFile == NULL) continue;

				process[count].pid = atol(pid);

				fscanf(statFile, "%u %s %c %u %*u %*u %*u %*u %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %lu %*s %lu %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %u %lu ",&processID, cmd , &state, &ppid, &uTime , &sTime, &startTime, &rss , &psr, &c);

				FILE* statmFile = fopen("/proc/self/statm", "r");

				if (statmFile == NULL) continue;

				fscanf(statmFile, "%lu", &sz);
				statmFile = fopen("/proc/uptime", "r");
				double upTime;
				fscanf(statmFile, "%lf", &upTime);

				if (!strcmp(option, "-a") || !strcmp(option, "-aF")) {

					char path[1024];
					int sid = 0;
					FILE* file;
					sprintf(path, "/proc/%s/stat", entity->d_name);
					file = fopen(path, "r");
					fscanf(file, "%*d %*s %*c %*d %*d %d", &sid);

					if (sid == atoi(pid) || strstr(ty, "null")) continue;

					if (state == 'Z' || state == 'T') continue;
				}

				ssize_t nbytes = readlink(pathDescriptor, tty, 20);

				if (nbytes >= 0) tty[nbytes] = '\0';

				else {

					tty[0] = '?';

					for (int i = 1 ; i < 9 ; i++) tty[i] = ' ';

					tty[9] = '\0';
				}

				strcpy(process[count].cmd, cmd);

				int elapsedTime = (int)(float)(sTime + uTime) / sysconf(_SC_CLK_TCK);
				sprintf(process[count].time, "%02d:%02d:%02d",elapsedTime / 3600, (elapsedTime % 3600) / 60, elapsedTime % 60);

				time_t st = time(NULL) - ((double)upTime - ((double)startTime / sysconf(_SC_CLK_TCK)));
				timeData = localtime(&st);

				char timeT[10];
				strftime(timeT, 10, "%H:%M", timeData);
				strcpy(process[count].sTime, timeT);
				strcpy(process[count].t, tty);

				process[count].ppid = ppid;
				process[count].psr = psr;
				process[count].sz = sz;
				process[count].rss = rss;
				process[count].c = c;
				count++;
			}
		}

		if (!strcmp(option, "-a")) {

			printf("%5s %-10s %10s %s\n", "PID", "TTY", "TIME", "CMD");
			for (int i = 0 ; i < count ; i++) printf("%5ld %-10s %10s %s\n",process[i].pid, process[i].t, process[i].time, process[i].cmd);
		}

		else if (!strcmp(option, "-aF")) {

			char* userID = getlogin();
			printf("%5s %5s %5s %5s %10s %10s %5s %10s %-10s %10s %s\n","UID", "PID", "PPID", "C", "SZ", "RSS", "PSR", "STIME", "TTY", "TIME", "CMD");

			for (int i = 0 ; i < count ; i++) printf("%5s %5ld %5u %5lu %10lu %10lu %5u %10s %-10s %10s %s\n",userID, process[i].pid, process[i].ppid, process[i].c, process[i].sz, process[i].rss, process[i].psr, process[i].sTime, process[i].t, process[i].time, process[i].cmd);
		}
	}
	closedir(directory);
}

void GetProcessInfo(char* pid, char* tty, char* time, char* cmd) {

	char path[256];

	sprintf(path,"/proc/%s/fd/0", pid);
	readlink(path, tty, 256);

	sprintf(path, "/proc/%s/stat", pid);

	FILE* file = fopen(path, "r");
	if (file != NULL) {

		int uTime;
		int sTime;
		int cuTime;
		int csTime;
		int startTime;
		char state;

		fscanf(file, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*u %*u %*u %*u %u %u %u %u %*d %*d %*d %d",&state, &uTime, &sTime, &cuTime, &csTime, &startTime);
		fclose(file);

		int elapsedTime = startTime / sysconf(_SC_CLK_TCK);

		int hours = elapsedTime / 3600;
		int minutes = (elapsedTime % 3600) / 60;
		int seconds = elapsedTime % 60;
		sprintf(time, "%02d:%02d:%02d",hours, minutes, seconds);
	}

	else sprintf(time, "-");

	sprintf(path, "/proc/%s/cmdline", pid);

	FILE* cmdFile = fopen(path, "r");

	if (cmdFile != NULL) {

		fgets(cmd, 512, cmdFile);
		fclose(cmdFile);

		for (int i = 0 ; i < strlen(cmd) ; i++) if (cmd[i] == '\0') cmd[i] = ' ';
	}

	else sprintf(cmd, "-");
}




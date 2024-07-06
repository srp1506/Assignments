#include "Header.h"

int main() {

	printf("\n\n\x1b[32m\e[1m------------------------------------------------------------------------------------\n\t\t\t\tSoham Pawar's Bash\n------------------------------------------------------------------------------------\x1b[0m\n\n\n");
	while (1) {

		char* userName = getlogin();

		if (userName == NULL) {

			printf("Error: Username Not Found");
			exit (0);
		}

		char host[256];

		if (gethostname(host, sizeof(host)) != 0) {

			printf("Error: Hostname Not Found");
			exit (0);
		}

		char cwd[PATH_MAX + 1];

		if (getcwd(cwd, sizeof(cwd)) == NULL) {

			printf("Error: Current Working Directory Not Found");
			exit (0);
		}

		char* commandLine;
		commandLine = strcat(userName, "@");
		commandLine = strcat(commandLine, host);
		commandLine = strcat(commandLine, ":");
		commandLine = strcat(commandLine, cwd);
		commandLine = strcat(commandLine, "$ ");

		char* command = readline(commandLine);
		int hasNonSpace = 0;
		int index = 0;

		while (command[index] != '\0') {

			if (command[index] != ' ') {

				hasNonSpace = 1;
				break;
			}

			index++;
		}

		if (hasNonSpace == 1) {

			add_history(command);
			char commandBuffer[500];
			char *token;
			char reducedCommand[500];
			strcpy(commandBuffer, command);
			token = strtok(commandBuffer, " ");
			strcpy(reducedCommand, token);
			token = strtok(NULL, " ");

			while (token != NULL) {

				strcat(reducedCommand, " ");
				strcat(reducedCommand, token);
				token = strtok(NULL, " ");
			}

			char* arguments[6];
			arguments[0] = strtok(reducedCommand, " ");
			arguments[1] = strtok(NULL, " ");
			arguments[2] = strtok(NULL, " ");
			arguments[3] = strtok(NULL, " ");
			arguments[4] = strtok(NULL, " ");
			arguments[5] = strtok(NULL, " ");

			if (!strcmp(arguments[0], "cd") && arguments[1] != NULL) chdir(arguments[1]);

			else if (!strcmp(reducedCommand, "Exit") || !strcmp(reducedCommand, "exit") || !strcmp(reducedCommand, "Quit") || !strcmp(reducedCommand, "quit")) break;

			else if (!strcmp(reducedCommand, "help")) system("bash -c help");


			else system(command);
		}
	}

	printf("\n\n\x1b[34m\e[1m------------------------------------------------------------------------------------\n\t\t\t\t Bash Terminated\n------------------------------------------------------------------------------------\x1b[0m\n\n\n");
	return 0;
}

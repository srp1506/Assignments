#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

char* list[1024];
int nop[1024] = {0};
int count = 0;
int nop_count = 0;

int Reg_identify(char* reg_name) {
	
	int reg_num = -1;
	
	if (reg_name[0] == 'x') {
		
		if (strlen(reg_name) == 3) {
	
			char num_str[3];
    			num_str[0] = reg_name[1];
    			num_str[1] = reg_name[2];
    			num_str[2] = '\0';
    			reg_num = atoi(num_str);
		}
		else reg_num = atoi(&reg_name[1]);
	}
	else {
		
		if (reg_name[0] == 'z') reg_num = 0;
		else if (reg_name[0] == 'r') reg_num = 1;
		else if (reg_name[0] == 'f') reg_num = 8;
		else if (reg_name[0] == 'g') reg_num = 3;
		else if (reg_name[0] == 's') {
			
			if (strlen(reg_name) == 3) {
				
				if (reg_name[2] == '0') reg_num = 26;
				else if (reg_name[2] == '1') reg_num = 27;
			}
			else {
				
				switch(reg_name[1]) {
					
					case 'p':
						reg_num = 2;
						break;
					case '0':
						reg_num = 8;
						break;
					case '1':
						reg_num = 9;
						break;
					case '2':
						reg_num = 18;
						break;
					case '3':
						reg_num = 19;
						break;
					case '4':
						reg_num = 20;
						break;
					case '5':
						reg_num = 21;
						break;
					case '6':
						reg_num = 22;
						break;
					case '7':
						reg_num = 23;
						break;
					case '8':
						reg_num = 24;
						break;
					case '9':
						reg_num = 25;
						break;
				}
			}
		}
		else if (reg_name[0] == 't') {
			
			switch(reg_name[1]) {
				
				case 'p':
					reg_num = 4;
					break;
				case '0':
					reg_num = 5;
					break;
				case '1':
					reg_num = 6;
					break;
				case '2':
					reg_num = 7;
					break;
				case '3':
					reg_num = 28;
					break;
				case '4':
					reg_num = 29;
					break;
				case '5':
					reg_num = 30;
					break;
				case '6':
					reg_num = 31;
					break;
			}
		}
		else if (reg_name[0] == 'a') {
			
			switch(reg_name[1]) {
				
				case '0':
					reg_num = 10;
					break;
				case '1':
					reg_num = 11;
					break;
				case '2':
					reg_num = 12;
					break;
				case '3':
					reg_num = 13;
					break;
				case '4':
					reg_num = 14;
					break;
				case '5':
					reg_num = 15;
					break;
				case '6':
					reg_num = 16;
					break;
				case '7':
					reg_num = 17;
					break;
			}
		}
	}
	return reg_num;
}

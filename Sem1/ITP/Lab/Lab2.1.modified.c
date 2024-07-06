#include<stdio.h>
int main()
{
	int marks;
	printf("Enter The Marks Of The Student:\n");
	scanf("%d",&marks);
	switch (marks)
	{
		case 96 ... 100:
		{
			printf("Your Grade Is A+\n");
			break;
		}	
		case 91 ... 95:
		{
			printf("Your Grade Is A\n");
			break;
		}
		case 81 ... 90:
		{
			printf("Your Grade Is A-\n");
			break;
		}	
		case 71 ... 80:
		{
			printf("Your Grade Is B\n");
			break;
		}
		case 61 ... 70:
		{
			printf("Your Grade Is B-\n");
			break;
		}
		case 51 ... 60:
		{
			printf("Your Grade Is C\n");
			break;
		}
		case 41 ... 50:
		{
			printf("Your Grade Is C-\n");
			break;
		}
		case 31 ... 40:
		{
			printf("Your Grade Is D\n");
			break;
		}
		case 1 ... 30:
		{
			printf("Your Grade Is F\n");
			break;
		}
	}	
	return 0;
}

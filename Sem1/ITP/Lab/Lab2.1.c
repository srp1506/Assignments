#include<stdio.h>
int main()
{
	int marks;
	printf("Enter The Marks Of The Student:\n");
	scanf("%d",&marks);
	if (marks>100)
	{
		printf("Don't Act Oversmart\n");
	}
	else if (marks>95 && marks<=100)
	{
		printf("Your Grade Is A+\n");
	}
	else if (marks>90 && marks<=95)
	{
		printf("Your Grade Is A\n");
	}
	else if (marks>80 && marks<=90)
	{
		printf("Your Grade Is A-\n");
	}
	else if (marks>70 && marks<=80)
	{
		printf("Your Grade Is B\n");
	}
	else if (marks>60 && marks<=70)
	{
		printf("Your Grade Is B-\n");
	}
 	else if (marks>50 && marks<=60)
	{
		printf("Your Grade Is C\n");
	}
	else if (marks>40 && marks<=50)
	{
		printf("Your Grade Is C-\n");
	}
	else if (marks>30 && marks<=40)
	{
		printf("Your Grade Is D\n");
	}
	else
	{
		printf("Your Grade Is F\n");
	}		
	return 0;
}

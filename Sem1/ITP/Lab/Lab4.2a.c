#include<stdio.h>
int main()
{
	int n,a=1,b=1;
	printf("Enter The Position Upto Which Fibonacci Sequence Is To Be Printed:\n>");
	scanf("%d",&n);
	if (n==1)
		printf("1\n");
	else 
	{
		printf("1\n1\n");
		while(n-2)
		{
			int temp=a;
			a=a+b;
			b=temp;
			printf("%d\n",a);
			n--;
		}
	}
	return 0;
}

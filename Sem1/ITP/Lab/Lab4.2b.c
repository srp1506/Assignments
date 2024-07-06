#include<stdio.h>
int main()
{
	int m,n,a=1,b=1,present1=0,present2=0;
	printf("Enter The Supposed Terms Of The Fibonacci Sequence In Ascending Order:\n>");
	scanf("%d%d",&m,&n);
	printf("\n");
	m==1?present1=1:printf("");
	while(a<=n)
	{
		int temp=a;
		a=a+b;
		b=temp;
		a==m?present1=1:(a==n?present2=1:printf(""));
	}
	if (present1==1 && present2==1)
	{
		a=1;
		b=1;
		while (a<=n)
		{
			a>=m?printf("%d\n",a):printf("");
			int temp=a;
			a=a+b;
			b=temp;
		}

	}
	else 
		printf("Either One Of The Entered Numbers Or Both Are Not In The Sequence\n");
	return 0;
}

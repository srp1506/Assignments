#include<stdio.h>
#define ll long long
ll factorial(int n)
{	
	if (n==0)
		return 1;
	return n*factorial(n-1);
}
int main()
{
	int n;
	printf("Enter The Number Of Rows Required:\n>");
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<=n-i;j++)
		{
			printf(" ");
		}
		for (int j=0;j<=i;j++)
		{
			printf("%lld ",factorial(i)/(factorial(i-j)*factorial(j)));
		}
		printf("\n");
	}
	return 0;
}

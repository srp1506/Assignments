#include<stdio.h>
int reverse(int n)
{
	int sum=0;
	while(n)
	{
		int m=n%10;
		sum+=m;
		sum*=10;
		n/=10;
	}
	return sum/10;
}
int main()
{
	int n;
	printf("Enter The Number:\n>");
	scanf("%d",&n);
	n==reverse(n)?printf("The Given Number Is A Palindrome\n"):printf("The Given Number Is Not A Palindrome\n");
	return 0;
}

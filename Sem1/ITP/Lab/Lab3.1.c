#include<stdio.h>
int main()
{
	int n,prime=1;
	printf("Enter The Number To Be Checked:\n>");
	scanf("%d",&n);
	if (n==1)
		printf("Not Prime\n");
	else 
	{
		for (int i=2;i<n;i++)
		{
			if (n%i==0)
			{
				prime=0;
				break;
			}
		}
		prime==1?printf("Prime\n"):printf("Not Prime\n");
	}
	return 0;
}

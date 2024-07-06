#include<stdio.h>
int main()
{
	int n,nfactorial=1;
	printf("Enter The Value Of n:\n>");
	scanf("%d",&n);
	while(n)
	{
		nfactorial*=n;
		n--;
	}
	printf("%d\n",nfactorial);
	return 0;
}

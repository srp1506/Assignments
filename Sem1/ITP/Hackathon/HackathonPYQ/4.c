#include<stdio.h>
int sum(int a[],int n,int k)
{
	for (int i=0;i<n;i++)
	{
		int sum=0;
		int j=0;
		while (sum<=k)
		{
			sum+=a[i+j];
			j++;
			if (sum==k)
				return 1;
		}
	}
	return 0;
}
int main()
{
	int test;
	scanf("%d",&test);
	while (test--)
	{
		int n,k,sub;
		scanf("%d",&n);
		int a[n];
		for (int i=0;i<n;i++)
			scanf("%d",&a[i]);
		scanf("%d",&k);
		sub=sum(a,n,k);
		sub==1?printf("1\n"):printf("0\n");
	}
	return 0;
}

#include<stdio.h>
int main()
{
	int n,r,count=0;
	printf("Enter The Length Of The Array And The Index:\n>");
	scanf("%d%d",&n,&r);
	int a[n];
	printf("Enter The Values In The Array In Order:\n");
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int pos=0;
	int temp=a[0];
	a[0]=a[r];
	a[r]=temp;
	count+=3;
	for (int i=1;i<n;i++)
	{
		count++;
		if (a[i]<a[0])
		{
			pos++;
			int temp=a[pos];
			a[pos]=a[i];
			a[i]=temp;
			count+=3;
			
		}
	}
	int pin=a[pos];
	a[pos]=a[0];
	a[0]=pin;
	count+=3;
	for (int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\nCount =%d\n",count);
	return 0;
}

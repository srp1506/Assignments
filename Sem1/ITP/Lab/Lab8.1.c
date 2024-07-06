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
	for (int i=0;i<n;i++)
		a[i]<a[r]?count++,pos++:count++;
	if (pos!=r)
	{
		int temp=a[pos];
		a[pos]=a[r];
		a[r]=temp;
		count+=3;
	}
	for (int i=0;i<pos;i++)
	{
		for(int j=pos+1;j<n;j++)
		{
			count++;
			if (a[i]>a[pos])
			{
				count++;
				if (a[j]<a[pos])
				{
					count+=3;
					int temp=a[i];
					a[i]=a[j];
					a[j]=temp;
				}
			}
		}
	}
	for (int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n%d\n",count);
	return 0;
}

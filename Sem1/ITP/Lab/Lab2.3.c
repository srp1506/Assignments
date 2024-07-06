#include<stdio.h>
int main()
{
	int n,max=0,min,positive=0;
	float sum,average;
	printf("Enter The Size Of The Set:\n");
	scanf("%d",&n);
	int num[n];
	printf("Enter The Numbers In The Set:\n");
	for (int i=0;i<n;i++)
	{
	scanf("%d",&num[i]);
	}
	for (int i=0;i<n;i++)
	{
		max<num[i]?max=num[i]:printf("");
	}
	min=num[0];
	for (int i=0;i<n;i++)
	{
		min>num[i]?min=num[i]:printf("");
	}
	for (int i=0;i<n;i++)
	{
		num[i]>0?sum+=num[i],positive++:printf("");
	}
	average=sum/positive;
	printf("The Maximum Of The Numbers Is:%d\n",max);
	printf("The Minimum Of The Numbers Is:%d\n",min);
	printf("The Average Of The Positive Numbers Is:%f\n",average);
	return 0;
}

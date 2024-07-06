#include<stdio.h>
int main()
{
	int n,sum=0,min,max=0;
	printf("Enter The Size Of The List:\n>");
	scanf("%d",&n);
	min=2e9-1;
	for (int i=0;i<n;i++)
	{
		int a;
		scanf("%d",&a);
		a>max?max=a:printf("");
		a<min?min=a:printf("");
		sum+=a;
	}
	printf("The Average Is: %f\n",(float)sum/n);
	printf("The Max Is: %d\n",max);
	printf("The Min Is: %d\n",min);
	return 0;
}

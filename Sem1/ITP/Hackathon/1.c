#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int isprime(int n)
{
	if (n==1)return 0;
	for (int i=2;(i*i)<=n;i++)
	{
		if (n%i==0)return 0;
	}
	return 1;
}
void sort(int a[],int m,int n)
{
	for (int i=0;i<m;i++)
	{
		for (int j=i+1;j<m;j++)
		{
			if (a[i]>a[j])
			{
				int temp=a[j];
				a[j]=a[i];
				a[i]=temp;
			}
		}
	}
	for (int i=n-1;i>m-1;i--)
	{
		for (int j=i-1;j>m-1;j--)
		{
			if (a[i]>a[j])
			{
				int temp=a[j];
				a[j]=a[i];
				a[i]=temp;
			}
		}
	}
}
#define MAXSIZE 20

int main() {
    int size;
    int arr[MAXSIZE];
    int i;
    
    while(scanf("%d",&size)!=-1) {
        for (i=0;i<size;i++) {
            scanf("%d",&arr[i]);
        }
        if (size)
        {
        	int j=0;
		for (int i=0;i<size;i++)
		{
			if (isprime(arr[i])==1)
			{
				int temp=arr[j];
				arr[j]=arr[i];
				arr[i]=temp;
				j++;
			}
		}
		sort(arr,j,size);
		for (int i=0;i<size;i++)printf("%d ",arr[i]);
		printf("\n");
	}
	else printf("no numbers\n");
    	}
    return 0;
}

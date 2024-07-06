#include<stdio.h>
void input(int *ptr,int m,int n)
{
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			printf("Enter The Element At The %d row and %d column:\n ",i+1,j+1);
			scanf("%d",ptr);
			ptr++;
		}
	}
}
int sum(int *m,int *n,int c,int d)
{
	int sum=0;
	for (int i=0;i<c;i++)
	{
		sum+=(*m)*(*n);
		m++;
		n+=d;
	}
	return sum;
}
int main()
{
	int a,b,c,d;
	printf("Enter The Dimensions Of The Two Matrices(axb and cxd):\n");
	scanf("%d%d%d%d",&a,&b,&c,&d);
	int array1[a][b],array2[c][d];
	if (b==c)
	{
		input(&array1[0][0],a,b);
		input(&array2[0][0],c,d);
		int array3[a][d];
		for (int i=0;i<a;i++)
		{
			for (int j=0;j<d;j++)
			{
				array3[i][j]=sum(&array1[i][0],&array2[0][j],c,d);
			}
		}
	for (int i=0;i<a;i++)
	{
		for (int j=0;j<d;j++)
		{
			printf("%d ",array3[i][j]);
		}
		printf("\n");
	}
	}
	else 
		printf("Invalid Matrix Multiiplication\n");
	return 0;
}

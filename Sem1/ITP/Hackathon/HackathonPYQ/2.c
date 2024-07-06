#include<stdio.h>
void reduce(int *a,int *b)
{
	for (int i=2;i<*a;i++)
	{
		if ((*a)%i==0 && (*b)%i==0)
		{
			(*a)/=i;(*b)/=i;
			return reduce(a,b);
		}
	}
}
int main()
{
	int a,b;
	printf("Enter The Value Of a And b:\n>");
	scanf("%d%d",&a,&b);
	reduce(&a,&b);
	printf("%d/%d\n",a,b);
	return 0;
}

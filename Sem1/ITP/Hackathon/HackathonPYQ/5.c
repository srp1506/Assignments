#include<stdio.h>
int main()
{
	int test;
	scanf("%d",&test);
	while (test--)
	{
		int a,b,c,d,r,delta;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		r=(d-c)/(c-b);
		delta=b-a*r;
		printf("%d %d %d\n",a,r,delta);
	}
	return 0;
}

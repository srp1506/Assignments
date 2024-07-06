#include<stdio.h>
int main()
{
	int sum=0,n,a,b;
	printf("Enter The Value Of a, b and n Respectively :\n");
	scanf("%d%d%d",&a,&b,&n);
	for (int i=1;i<n;i++)
		if (i%a==0 || i%b==0)
			sum+=i;
	printf("%d\n",sum);
	return 0;
}

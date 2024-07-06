#include<stdio.h>
int main()
{
	char a;
	int array[100],count=0,wellformed=1,p=0,q=0;
	while (1)
	{
		scanf(" %c",&a);
		switch ((int)a)
		{
			case 40:
			{
				array[count]=1;
				p++;
				break;
			}
			case 41:
			{
				array[count]=4;
				p--;
				break;
			}
			case 91:
			{
				array[count]=2;
				q++;
				break;
			}
			case 93:
			{
				array[count]=3;
				q--;
				break;
			}
		}
		if ((int)a==97)
			break;
		count++;
	} 
	if (count%2!=0 || p!=0 || q!=0)
		wellformed=0;
	else
	{
		for (int i=0;i<count-1;i++)
		{
			for (int j=i;j<count;j++)
			{
				if (array[i]+array[j]==5 && (j-i)%2!=0 && array[j]>array[i])
				{
					array[i]=0;
					array[j]=0;
				}
			}
		}
	}
	while (count--)
	{
		if (array[count]!=0)
		{
			wellformed=0;
			break;
		}
	}
	wellformed==0?printf("0\n"):printf("1\n");
	return 0;
}

#include<stdio.h>
#include<string.h>
int main()
{
	char string[100];
	scanf("%s",string);
	int wellformed=1;
	int x=strlen(string);
	for (int i=1;i<x;i+=2)

	{
		for (int j=0;j<x;j++)
		{
			if ((string[j]=='(' && string[j+i]==')') || (string[j]=='[' && string[j+i]==']'))
				{
					if (i>1)
					{
						for (int k=1;k<i;k++)
						{
							if (string[j+k]!='0')
								wellformed=0;
						}
					}
					if (wellformed==1)
					{
						string[j]='0';
						string[i+j]='0';
					}
						
				}		
			wellformed=1;	
		}
	}
	for (int i=0;i<x;i++)
	{
		if (string[i]!='0')
		{
			wellformed=0;
			break;
		
		}
	}
	wellformed==1 ? printf("1\n") : printf("0\n");
	return 0;
}

#include<stdio.h>
int main()
{
	char string[100];
	int p=0,q=0,r=0,s=0,count=0,wellformed=1;
	scanf("%s",string);
	while (string[count]!='\0')
	{
		switch ((int)string[count])
		{ 
			case 40:
                        {
                                p++;
                                break;
                        }
                        case 41:
                        {
                                s++;
                                break;
                        }
                        case 91:
                        {
                                q++;
                                break;
                        }
                        case 93:
                        {
                                r++;
                                break;
                        }
		}
		p<s || q<r ?wellformed=0:printf("");
		count++;
	}	
	(p!=s || q!=r)?wellformed=0:printf("");
	for (int i=0;i<count-1;i++)
	{
		(string[i]=='(' && string[i+1]==']')||(string[i]=='[' && string[i+1]==')')?wellformed=0:printf("");
		for (int j=i+1;j<count;j++)
		{
			if (((string[i]=='(' && string[j]==')') || (string[i]=='[' && string[j]==']')) && (j-i)%2!=0)
			{
				string[i]='t';
				string[j]='t';
			}
		}
	}
	while (count--)
	{
		string[count]!='t'?wellformed=0:printf("");
	}
	wellformed==0?printf("0\n"):printf("1\n");	
	return 0;
}

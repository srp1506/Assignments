#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isfib(int n) {
int a=0,b=1,temp;
        while (a<=n)
        {
                temp=a;
                a+=b;
                b=temp;
                if (b==n)
                        return 1;
        }
        return 0;
}

bool ispalindrome(int n){
int sum=0,r=n;
        while(n)
        {
                int m=n%10;
                sum+=m;
                sum*=10;
                n/=10;
        }
        sum/=10;
        if (sum==r)
        return 1;
        else 
        return 0;
}

void printfibpalindrome(int num1, int num2)
{
	int d=0;
	if (num1>num2)
        {
                int temp;
                temp=num2;
                num2=num1;
                num1=temp;
        }

    int a=1,c=1,b;
    while(1)
    {
        b=a;
        a+=c;
        c=b;
     if (c<num2 && c>num1 && ispalindrome(c))
     {
        printf("%d ", c);
        d++;
     }
        if (c>num2)
                break;
    }
    d==0?printf("no numbers\n"):printf("");
}

int main()
{
    int num1, num2 ;

    while (scanf("%d %d",&num1, &num2) != -1) {
        if (isfib(num1) && isfib(num2)) {
            printfibpalindrome(num1, num2);
            printf("\n");
        } else {
            printf("no numbers");
            printf("\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
int mod(int a)
{
        if(a>=0)return a;
        else return a*-1;
}
int euclidGCD(int a, int b) {
        int coprime=1,gcd;
        a=mod(a);b=mod(b);
        if (a==0 & b!=0)
                 printf("%d\n",b);
        else if (b==0 & a!=0)
                 printf("%d\n",a);
        else
         {
                for(int i=2;i<=a;i++)
                {
                        if (a%i==0 && b%i==0)
                        {
                                coprime=0;
                                gcd=i;
                        }
                 }
        }
        if (coprime)return 1;
        else return gcd;
}

int main() {
  int a,b;
  while (scanf("%d %d",&a, &b) != -1) {
    printf("%d\n", euclidGCD(a,b));
  }

  return 0;
}


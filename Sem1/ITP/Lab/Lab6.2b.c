#include <stdio.h>
#include <stdlib.h>
int mod(int a)
{
	if(a>=0)return a;
	else return a*-1;
}
int euclidGCD(int a, int b) {
a=mod(a);b=mod(b);
if(b==0 && a!=0)return a;
else if(b!=0 && a==0)return b;
if (b%a!=0)
                return euclidGCD(b%a,a);
        else
                return a;    
}

int main() {
  int a,b;
  while (scanf("%d %d",&a, &b) != -1) {
    printf("%d\n", euclidGCD(a,b));
  }

  return 0;
}

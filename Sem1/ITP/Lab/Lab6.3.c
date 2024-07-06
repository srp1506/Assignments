#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXSIZE 20

bool is_prime(int num) {
	if (num<=1 )return 0;
    	for (int i=2;(i*i)<=num;i++)
        {
                if (num%i==0)
                        return 0;
        }
        return 1;
}


int main() {
    int size;
    int arr[MAXSIZE];
    int i;


    while(scanf("%d",&size)!=-1) {
        for (i=0;i<size;i++) {
            scanf("%d",&arr[i]);
        }
	int count=0;
        for (int i=0;i<size;i++)
        {
       		if (is_prime(arr[i]))
       		{
       			printf("%d ",arr[i]);
       			count++;
       		}
       }
       count==0?printf("no numbers\n"):printf("\n");
    }
        
    return 0;
}

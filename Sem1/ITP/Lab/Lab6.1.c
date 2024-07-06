#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXSIZE 20

int main()
{
    int a[MAXSIZE],size=MAXSIZE;
    int i;

    bzero(a,sizeof(a));
    while(scanf("%d",&size)!=-1){
        for(i=0;i<size;i++) {
            scanf("%d",&a[i]);
        }
        if (size==0)printf("no numbers\n");
        else {
                for (int i=0;i<size;i++)
                {
                        for (int j=i+1;j<size;j++)
                        {
                                if (a[i]>a[j])
                                {
                                        int temp=a[j];
                                        a[j]=a[i];
                                        a[i]=temp;
                                }
                        }
                }
                for (int i=0;i<size;i++) printf("%d ",a[i]);
                printf("\n");

        }
    }
    return 0;
}
   

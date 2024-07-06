#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 20

int main()
{
    int i,j,size,matrix[MAX_SIZE][MAX_SIZE];
   
    while(scanf("%d",&size)!=-1) {
        for (i=0;i<size;i++) {
            for (j=0;j<size;j++) {
                scanf("%d",&matrix[i][j]);
            }

        }
	int upper=1;
	for (int i=1;i<size;i++)
	{
		for (int j=0;j<i;j++)
		{
			if (matrix[i][j]!=0)
				upper=0;
		}
	}
	if (upper)
        printf("upper triangular\n");
        
        /* 
         * Use the following printf statement if matrix is NOT upper triangular
         */
	else
        printf("Not upper triangular\n");

    }
    
    return 0;
}


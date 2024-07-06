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
	if (size==1)
		printf("%d\n",matrix[0][0]);
	else if (size<=0)
		printf("Not upper triangular\n");
	else
	{
   	    	int upper=1;
		int zero[MAX_SIZE]={0};
       		for (int i=0;i<size;i++)
       		{
       			for (int j=0;j<size;j++)
       			{
       				if (matrix[i][j]==0)
       				{
					zero[i]++;
       				}
				else
					break;
       			}
		}
		for (int i=0;i<size;i++)
		{
			for (int j=0;j<=size;j++)
			{
				if (zero[i]<zero[j])
				{
					int temp=zero[i];
					zero[i]=zero[j];
					zero[j]=temp;
		
					for (int k=0;k<size;k++)
					{
						int temp=matrix[i][k];
						matrix[i][k]=matrix[j][k];
						matrix[j][k]=temp;
					}
				}
			}
		}
		if (zero[size-1]<size-1)
		{
			upper=0;
		}
  	     	if (upper==0)
		{
	       	 	printf("Not upper triangular\n");
		}
		else
		{
		        for(i=0;i<size;i++){
		            for(j=0;j<size;j++){
       		         	printf("%d ",matrix[i][j]);
       	 		    	}
        		    printf("\n"); 
        		}
    		}
    }
}
    return 0;
}

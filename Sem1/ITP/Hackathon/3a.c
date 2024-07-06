#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
typedef struct LinkedList
{
	int val;
	struct LinkedList* ptr;
}link;
/*
 * please don't use any array at all. 
 */
int prime(int n)
{
	if (n==1) return 0;
	for (int i=2;i<n;i++)
	{
		if (n%i==0)
			return 0;
	}
	return 1;
}
int smallestprime(int x,int y)
{
	for (int i=x+1;i<y;i++)
	{
		if (prime(i)==1)
			return i;
	}
	return 1;
}
int main()
{
    	int i;
	int var;
	int size;
	link end,*node,*first;
	end.ptr=0;
    	while(scanf("%d",&size)!=-1) {
		if (size>0)
		{
			first=&end;
    	   		scanf("%d",&var);
			end.val=var;
	        	for (i=0;i<size-1;i++) { 
				node=(link*)malloc(sizeof(link));
	       	     		scanf("%d",&var);
				node->val=var;
				node->ptr=first;
				first=node;
	       	 	}	
			link *ptr2=first;
			for (i=0;i<size;i++) {
				printf("%d ",ptr2->val);
				ptr2=ptr2->ptr;
			}
			printf("\n");
			if (size>1)
			{
				ptr2=first;
				while (ptr2->ptr!=0)
				{	
					link* ptr3;
					ptr3=ptr2->ptr;
					int b=ptr3->val,a=ptr2->val;
					if (a>b)
					{
						int temp=a;
						a=b;
						b=a;
					}
					node=(link*)malloc(sizeof(link));
					node->val=smallestprime(a,b);
					node->ptr=ptr3;
					ptr2->ptr=node;
					ptr2=ptr3;
				}
				ptr2=first;
				while(ptr2->ptr!=0) {
					printf("%d ",ptr2->val);
					ptr2=ptr2->ptr;
				}
				printf("%d\n",ptr2->val);
			}
			else printf("%d\n",first->val);
		}
		else
		printf("no elements in the linked list");	
	}
return 0;
}


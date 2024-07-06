#include<stdio.h>
void input(int *ptr)
{
	for (int i=0;i<3;i++)
	{
		scanf("%d",ptr);
		ptr++;
	}
}
void scalar(int *ptr1,int *ptr2)
{
	int sum=0;
	for (int i=0;i<3;i++)
	{
		sum+=(*ptr1)*(*ptr2);
		ptr1++;
		ptr2++;
	}
	printf("Scalar Product Of The Given Vectors Is: %d\n",sum);
}
void vector (int v1[3],int v2[3])
{
	int v3[3];
	v3[0]=v1[1]*v2[2]-v2[1]*v1[2];
	v3[1]=v2[0]*v1[2]-v1[0]*v2[2];
	v3[2]=v1[0]*v2[1]-v1[1]*v2[0];
	printf("Vector Product Of The Given Vectors Is: %di,%dj,%dk\n",v3[0],v3[1],v3[2]);
}
int main()
{
	int vect1[3],vect2[3];
	printf("Enter The Components Of Vector1:\n");
	input(vect1);
	printf("Enter The Components Of Vector2:\n");
	input(vect2);
	scalar(vect1,vect2);
	vector(vect1,vect2);
	return 0;
}

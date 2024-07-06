#include<stdio.h>
typedef struct student 
{
	char name[50];
	char gender;
	float cgpa;
	int yoj;
	int rollnum;
}stud;
void sort(stud a[],int n)
{
        for (int i=0;i<n;i++)
        {
                for (int j=i+1;j<n;j++)
                {
                        if (a[i].yoj>a[j].yoj)
                        {
                                stud temp=a[j];
                                a[j]=a[i];
                                a[i]=temp;
                        }
                }
        }
        for (int i=0;i<n;i++)
        {
                for (int j=i+1;j<n;j++)
                {
                	        if (a[i].rollnum>a[j].rollnum && a[i].yoj==a[j].yoj)
                       		{
                       	         	stud temp=a[j];
                       	         	a[j]=a[i];
                                	a[i]=temp;
                        	}
                }
        }
}
int main()
{
	int n;
	printf("Enter The Number Of Students:\n");
	scanf("%d",&n);
	printf("Enter The Details Of The Students In Order( Name, Gender(M/F), CGPA, Year Of Joining, Roll Number):\n");
	char temp;
	stud array[n];
	for (int i=0;i<n;i++)
	{
		printf("Student %d:\n",i+1);	
		scanf(" %[^\n]%*c %c%f%d%d",array[i].name,&array[i].gender,&array[i].cgpa,&array[i].yoj,&array[i].rollnum);
		scanf("%c",&temp);
	}
	printf("\n\n");
	sort(array,n);
	puts("Year	Rollnum		Gender		CGPA		Name");
	for (int i=0;i<n;i++)
		printf("%d	%d		%c		%.2lf		%s\n",array[i].yoj,array[i].rollnum,array[i].gender,array[i].cgpa,array[i].name);
	return 0;
}














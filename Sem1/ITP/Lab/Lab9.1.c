#include<stdio.h>
typedef struct imaginarynumber
{
	float real;
	float unreal;
}i;
double pow(double x,int n)
{
        double r=x;
        if (x!=0 && n==0)
                return 1;
        if (x!=0 && n<0)
        {
                x=1/x;
        }
        while (--n)
        {
                r*=x;
        }
        return r;
}
double nthroot(float x,int n,int i)
{
	 double guess=x/n;
        while (i--)
        {
                double correction=((pow(guess,n)-x)/(n*pow(guess,n-1)));
                guess-=correction;
        }
	return guess;
}
float magnitude(i i1)
{
	return nthroot((pow(i1.real,2)+pow(i1.unreal,2)),2,50);
}
void sum(i i1,i i2)
{
	printf("Addition :(%.2f,%.2fi)\n",(i1.real+i2.real),(i1.unreal+i2.unreal));
}
void difference(i i1,i i2)
{
	printf("Difference :(%.2f,%.2fi)\n",(i1.real-i2.real),(i1.unreal-i2.unreal));
}
void multiplication(i i1,i i2)
{
	i i3;
	i3.real=(i1.real*i2.real)-(i1.unreal*i2.unreal);
	i3.unreal=(i1.real*i2.unreal)+(i1.unreal*i2.real);
	printf("Multiplication: (%.2f,%.2fi)\n",i3.real,i3.unreal);
}
void division(i i1,i i2)
{
	i i3;
	i3.real=((i1.real*i2.real)+(i1.unreal*i2.unreal))/pow(magnitude(i2),2);
	i3.unreal=-((i1.real*i2.unreal)-(i1.unreal*i2.real))/pow(magnitude(i2),2);
	printf("Division :(%.2f,%.2fi)\n",i3.real,i3.unreal);
}
void polar(i i1)
{
	printf("Polar Form :(%.2f,tan^-1(%.2f))\n",magnitude(i1),i1.unreal/i1.real);
}
int main()
{
	i i1,i2;
	printf("Enter The Complex Numbers (a,bi) :\n>");
	scanf("%f%f%f%f",&i1.real,&i1.unreal,&i2.real,&i2.unreal);
	printf("Magnitude : %.5f ,%.5f\n",magnitude(i1),magnitude(i2));
	sum(i1,i2);
	difference(i1,i2);
	multiplication(i1,i2);
	division(i1,i2);
	polar(i1);
	polar(i2);
	return 0;
}

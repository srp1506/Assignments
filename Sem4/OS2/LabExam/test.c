#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/time.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/mman.h>

int a, b, c, d;

void matmul(int* A, int* B, int* C)
{
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            
        }
    }
}

int main(int argc, char *argv[]) 
{
    FILE* file1;
    FILE* file2;
    FILE* file3;
    file1 = fopen("matA.txt", "w");
    file2 = fopen("matB.txt", "w");
    file3 = fopen("matC.txt", "w");
    int a, b, c, d;
    printf("Enter the dimensions of A :");
    scanf("%d%d", &a, &b);
    printf("Enter the dimensions of B :");
    scanf("%d%d", &c, &d);

    if (b != c)
    {
        printf("Invalid instances for matrix multiplication\n");
        exit(1);
    }

    int* A = (int*)malloc(a * b * sizeof(int));
    int* B = (int*)malloc(c * d * sizeof(int));
    int* C = (int*)malloc(a * d * sizeof(int));

    printf("Values of A :\n");
    for (int i = 0; i < a * b; i++)
        scanf("%d", &A[i]);

    printf("Values of B :\n");
    for (int i = 0; i < c * d; i++)
        scanf("%d", &B[i]);

    matmul(A, B, C);

    for (int i = 0; i < a * b; i++)
    {
        if (i % b == 0 && i != 0)
            fprintf(file1, "\n");
        fprintf(file1, "%d ", A[i]);
    }

    for (int i = 0; i < c * d; i++)
    {
        if (i % d == 0 && i != 0)
            fprintf(file2, "\n");
        fprintf(file2, "%d ", B[i]);
    }

    for (int i = 0; i < a * d; i++)
    {
        if (i % d == 0 && i != 0)
            fprintf(file1, "\n");
        fprintf(file3, "%d ", C[i]);
    }
}
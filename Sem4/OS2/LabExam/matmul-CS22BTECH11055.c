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

void matmul(int** A, int** B, int** C)
{
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < d; j++)
        {
            int sum = 0;
            for (int k = 0; k < b; k++)
                sum += A[i][k] * B[k][j];
            
            C[i][j] = sum;
            // printf("%d\n", sum);
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
    printf("Enter the dimensions of A :");
    scanf("%d%d", &a, &b);
    printf("Enter the dimensions of B :");
    scanf("%d%d", &c, &d);

    if (b != c)
    {
        printf("Invalid instances for matrix multiplication\n");
        exit(1);
    }

    int** A = (int**)malloc(a * sizeof(int*));
    for (int i = 0; i < a; i++)
        A[i] = (int*)malloc(b * sizeof(int));

    int** B = (int**)malloc(c * sizeof(int*));
    for (int i = 0; i < c; i++)
        B[i] = (int*)malloc(d * sizeof(int));

    int** C = (int**)malloc(a * sizeof(int*));    
    for (int i = 0; i < a; i++)
        C[i] = (int*)malloc(d * sizeof(int));



    printf("Values of A :\n");
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++)
            scanf("%d", &A[i][j]);

    printf("Values of B :\n");
    for (int i = 0; i < c; i++)
        for (int j = 0; j < d; j++)
            scanf("%d", &B[i][j]);

    matmul(A, B, C);

    for (int i = 0; i < a; i++)
    {
        for (int j = 0 ; j < b ; j++)
            fprintf(file1, "%d ", A[i][j]);
        
        fprintf(file1, "\n");
        
    }

    for (int i = 0; i < c; i++)
    {
        for (int j = 0 ; j < d ; j++)
            fprintf(file2, "%d ", B[i][j]);
        
        fprintf(file2, "\n");
        
    }

    for (int i = 0; i < a; i++)
    {
        for (int j = 0 ; j < d ; j++)
            fprintf(file3, "%d ", C[i][j]);
        
        fprintf(file3, "\n");
        
    }
}
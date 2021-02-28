#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <stdint.h>
#include <time.h>

typedef struct 
{
    int64_t** m;
    int64_t size_a;
    int64_t size_b;

}matrix;

int64_t ** create_array2d(int64_t columns, int64_t rows)
{
    int64_t ** arr = malloc(sizeof(int64_t*) * rows );
    for(int i = 0; i < rows; i++)
    {
        arr[i] = malloc(columns * sizeof(int64_t));
    }


    return arr;
}

void free_array2d(int64_t** arr, int64_t columns, int64_t rows)
{
    if (arr == 0)
        return;
    
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
}

void print_matrix(matrix m)
{
    if (m.m == 0)
    {
        printf("print_matrix: Error: Data of matrix is corrupted\n");
        return;
    }
	for (int i = 0; i < m.size_b; i++)
	{
		for(int j = 0; j < m.size_a; j++)
		{
			printf("%ld ", m.m[i][j]);
		}
		printf("\n");
	}

    printf("\n");
}

matrix scan_matrix(FILE* file)
{
    matrix m;

    int t, check;
    char ch;
    int size_a = 0;
    int size_b = 0;
    
    while ((check = fscanf(file, "%d%c", &t, &ch)) != -1)
    {
        if (ch == ' ' && size_b == 0) 
            size_a++;
        if (ch == '\n')
        {
            size_a = (size_b == 0) ? (size_a + 1) : (size_a);
            size_b++;
        }
    }

    fseek(file, 0, SEEK_SET);
    m.m = create_array2d(size_a, size_b);
    m.size_a = size_a;
    m.size_b = size_b;

    for (int i = 0; i < size_b; i++)
    {
        for (int j = 0; j < size_a; j++) 
        {
            if ((check = fscanf(file, "%d%c", &t, &ch)) == -1) break;
            
            m.m[i][j] = t;
        }    
        
    }

    return m;
}

matrix multiply_matrix(matrix* A, matrix* B) // C[i,j] = Sum(A[i,k]*B[k,j]);
{
    matrix R;
    if (A->size_a != B->size_b)
    {
        printf("multiply_matrix: Error: matrices cannot be multiplied\n");
        R.m = 0;
        R.size_a = 0;
        R.size_b = 0;
        return R;
    }

    R.size_a = A->size_a;
    R.size_b = B->size_b;
    R.m = create_array2d(R.size_a, R.size_b);

    for (int i = 0; i < R.size_b; i++)
    {
        for (int j = 0; j < R.size_a; j++)
        {
            R.m[i][j] = 0;
            for (int k = 0; k < A->size_b; k++)
                R.m[i][j] += A->m[i][k] * B->m[k][j];  
        }
    }

    return R;

}

void init_matrix(matrix* A)
{
    A->m = NULL;
    A->size_a = 0;
    A->size_b = 0;
}

// * THREADING * //

typedef struct
{
    FILE* file;
    matrix* mat_A;
    matrix* mat_B;
    matrix* mat_R;
}thr_args;

void* thr_scan_matrix(void* param) // In: File, Matrix / Out: Matrix from file
{
    thr_args *arg = (thr_args*) param;
    FILE* file = arg->file;
    matrix* A = arg->mat_A;

    *A = scan_matrix(file);

    print_matrix(*A);
    return NULL;
}

void* thr_multiply_matrix(void* param) // In: MatrixA, MatrixB / Out: MatrixA x MatrixB = MatrixC
{
    thr_args *arg = (thr_args*) param;
    
    matrix* A = arg->mat_A;
    matrix* B = arg->mat_B;
    matrix* R = arg->mat_R;

    *R = multiply_matrix(A, B);


    return NULL;

}

int main(int argc, char* argv[])
{
    clock_t begin = clock();


    FILE* file1 = fopen(/*argv[1]*/ "./tests/2.txt", "r");
    FILE* file2 = fopen(/*argv[1]*/ "./tests/3.txt", "r");
    FILE* file3 = fopen(/*argv[1]*/ "./tests/4.txt", "r");
    FILE* file4 = fopen(/*argv[1]*/ "./tests/5.txt", "r");
    FILE* file5 = fopen(/*argv[1]*/ "./tests/6.txt", "r");
    matrix A, B, C, D, E, R1, R2, R3, R4, R5;
    init_matrix(&A);
    init_matrix(&B);
    init_matrix(&C);
    init_matrix(&D);
    init_matrix(&E);
    init_matrix(&R1);
    init_matrix(&R2);
    init_matrix(&R3);
    init_matrix(&R4);
    init_matrix(&R5);
    
    // pthread_t tr_0;
    // pthread_t tr_1;
    // pthread_t tr_2;
    // pthread_t tr_3;
    // pthread_t tr_4;

    // thr_args arg[5];
    
    // arg[0].file = file1;
    // arg[0].mat_A = &A; 
    
    // arg[1].file = file2;
    // arg[1].mat_A = &B;

    // arg[2].file = file3;
    // arg[2].mat_A = &C;

    // arg[3].file = file4;
    // arg[3].mat_A = &D;

    // arg[4].file = file5;
    // arg[4].mat_A = &E;

    // pthread_create(&tr_0, NULL, thr_scan_matrix, (void*) &arg[0]);
    // pthread_create(&tr_1, NULL, thr_scan_matrix, (void*) &arg[1]);
    // pthread_create(&tr_2, NULL, thr_scan_matrix, (void*) &arg[2]);
    // pthread_create(&tr_3, NULL, thr_scan_matrix, (void*) &arg[3]);
    // pthread_create(&tr_4, NULL, thr_scan_matrix, (void*) &arg[4]);
    

    // arg[0].mat_A = &A;
    // arg[0].mat_B = &A;
    // arg[0].mat_R = &R1;

    // arg[1].mat_A = &B;
    // arg[1].mat_B = &B;
    // arg[1].mat_R = &R2;

    // arg[2].mat_A = &C;
    // arg[2].mat_B = &C;
    // arg[2].mat_R = &R3;

    // arg[3].mat_A = &D;
    // arg[3].mat_B = &D;
    // arg[3].mat_R = &R4;

    // arg[4].mat_A = &E;
    // arg[4].mat_B = &E;
    // arg[4].mat_R = &R5;

    // pthread_create(&tr_0, NULL, thr_multiply_matrix, (void*) &arg[0]);
    // pthread_create(&tr_1, NULL, thr_multiply_matrix, (void*) &arg[1]);
    // pthread_create(&tr_2, NULL, thr_multiply_matrix, (void*) &arg[2]);
    // pthread_create(&tr_3, NULL, thr_multiply_matrix, (void*) &arg[3]);
    // pthread_create(&tr_4, NULL, thr_multiply_matrix, (void*) &arg[4]);
    

    // pthread_join(tr_4, NULL);

    A = scan_matrix(file1);
    print_matrix(A);

    B = scan_matrix(file2);
    print_matrix(B);

    C = scan_matrix(file3);
    print_matrix(C);

    D = scan_matrix(file4);
    print_matrix(D);

    E = scan_matrix(file5);
    print_matrix(E);

    R1 = multiply_matrix(&A, &A);
    R2 = multiply_matrix(&B, &B);
    R3 = multiply_matrix(&C, &C);
    R4 = multiply_matrix(&D, &D);
    R5 = multiply_matrix(&E, &E);





    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("time spent: %f sec \n", time_spent);
    return 0;
}
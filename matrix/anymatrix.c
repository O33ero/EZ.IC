#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <stdint.h>

// * Структура матрицы
typedef struct 
{
    int64_t** m; // Указатель на массив указателей на массивы строк матрицы
    int64_t size_a; // Число столбцов
    int64_t size_b; // Число строк

}matrix;

// * Создаю двумерный массив заданного размера
int64_t ** create_array2d(int64_t columns, int64_t rows)
{
    int64_t ** arr = malloc(sizeof(int64_t*) * rows );
    for(int i = 0; i < rows; i++)
    {
        arr[i] = malloc(columns * sizeof(int64_t));
    }


    return arr;
}

// * Освобождаю двумерный массив
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

// * Печатаю матрицу
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

// * Сканирую матрицу из файла
matrix scan_matrix(FILE* file)
{
    matrix m;

    int t, check;
    char ch;
    int size_a = 0;
    int size_b = 0;
    
    while ((check = fscanf(file, "%d%c", &t, &ch)) != -1) // Вычисляю размер матрицы
    {
        if (ch == ' ' && size_b == 0) 
            size_a++;
        if (ch == '\n')
        {
            size_a = (size_b == 0) ? (size_a + 1) : (size_a);
            size_b++;
        }
    }

    fseek(file, 0, SEEK_SET); // Возвращаюсь в начало файла
    m.m = create_array2d(size_a, size_b); // Создаю матрицу заданного размера
    m.size_a = size_a;
    m.size_b = size_b;

    for (int i = 0; i < size_b; i++)
    {
        for (int j = 0; j < size_a; j++) 
        {
            if ((check = fscanf(file, "%d%c", &t, &ch)) == -1) break; // Если не считало ничего, то ломай
            
            m.m[i][j] = t;
        }    
        
    }

    return m;
}

// * Умножаю матрицы
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
    R.m = create_array2d(R.size_a, R.size_b); // Создаю новую результирующую матрицу

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

int main(int argc, char* argv[])
{
    FILE* file1 = fopen(/*argv[1]*/ "./tests/1.txt", "r");
    FILE* file2 = fopen(/*argv[1]*/ "./tests/2.txt", "r");
    matrix A, B, R;
    A = scan_matrix(file1);
    print_matrix(A);
    
    B = scan_matrix(file2);
    print_matrix(B);

    R = multiply_matrix(&A, &B);
    print_matrix(R);

    free_array2d(A.m, A.size_a, A.size_b);
    free_array2d(B.m, B.size_a, B.size_b);
    free_array2d(R.m, R.size_a, R.size_b);

    return 0;
}
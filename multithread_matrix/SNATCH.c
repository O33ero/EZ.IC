#include <pthread.h>
#include <stdlib.h>
#include <mcheck.h>
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

//специальная структура для данных потока.
typedef struct /* Так это структура для потока (1/2) */
{
    //указатели на матрицы
    int **array;
    int line;   //номер обрабатываемой строки
    int column; //номер стобца

} matrix;

void check_matrix(FILE *fl)
{
    char ch;
    rewind(fl);
    while (fscanf(fl, "%c", &ch) != -1)
    {
        if ((!((ch >= 0x30 && ch <= 0x39) || ch == 0x20 || ch == 0xA || ch == 0x2D)) || (ch == 0x00))
        {
            printf("Mistake");
            exit(1);
        }
    }
    fseek(fl, 0, SEEK_SET); // Блять, а указатель в начало файла кто будет возвращать?
}

int **build_matrix(int column, int line)
{
    int **M = (int **)malloc(line * sizeof(int *));
    for (int i = 0; i < line; i++)
    {
        M[i] = (int *)malloc(column * sizeof(int));
    }
    return M;
}

matrix read_matrix(FILE *fl)
{
    matrix R;

    int num, scan;
    char ch;
    int line = 0;
    int column = 0;

    while ((scan = fscanf(fl, "%d%c", &num, &ch)) != -1) // Автор этой строки гений
    { 
        if (ch == ' ' && line == 0)
            column++;
        if (ch == '\n')
        {
            line++;
        }
    }

    if (column != 0)
    {
        column++;
    }

    rewind(fl);
    R.array = build_matrix(column, line); // Что? Как? Зачем? Почему тут num?
    R.column = column;
    R.line = line;

    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if ((scan = fscanf(fl, "%d%c", &num, &ch)) == -1) // Автор этой строки гений
                break; 

            R.array[i][j] = num;
        }
    }

    return R;
}

void print_matrix(matrix R)
{
    if (R.array == 0)
    {
        printf("NULL");
        return;
    }
    for (int i = 0; i < R.line; i++)
    {
        for (int j = 0; j < R.column; j++)
        {
            printf("%d ", R.array[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

matrix multiply_matrix(matrix *A, matrix *B)
{
    matrix C;
    if (A->column != B->line)
    {
        printf("Mistake");
        C.array = 0;
        C.column = 0;
        C.line = 0;
        return C;
    }

    C.column = B->column;
    C.line = A->line;
    C.array = build_matrix(C.column, C.line);
    for (int i = 0; i < C.line; i++)
    {
        for (int j = 0; j < C.column; j++)
        {
            C.array[i][j] = 0;
            for (int k = 0; k < A->column; k++)
            {
                C.array[i][j] += A->array[i][k] * B->array[k][j];
            }
        }
    }
    return C;
}

void clear_matrix(matrix A)
{
    for (int i = 0; i < A.line; i++)
    {
        free(A.array[i]);
    }
    free(A.array);
}

void initiate_matrix(matrix *A)
{
    A->array = NULL;
    A->column = 0;
    A->line = 0;
}

typedef struct /* Или это структура для потока (2/2) */
{
    FILE *fl;
    matrix *A;
    matrix *B;
    matrix *C;
} stream;

// * Сканирую матрицу отдельным потоком
void *stream_scan(void *crime) // In: File, Matrix / Out: Matrix from file
{
    stream *arg = (stream *)crime;
    FILE *fl = arg->fl;
    matrix *A = arg->A;

    *A = read_matrix(fl);

    print_matrix(*A);
    return NULL;
}

// * Умножаю матрицы отдельным потоком
void *stream_act(void *crime) // In: MatrixA, MatrixB / Out: MatrixA x MatrixB = MatrixC
{
    stream *arg = (stream *)crime;

    matrix *A = arg->A;
    matrix *B = arg->B;
    matrix *C = arg->C;

    *C = multiply_matrix(A, B);

    return NULL;
}

int main(int argc, char *argv[])
{
    FILE *fl1 = fopen("./tests/1.txt", "r");
    FILE *fl2 = fopen("./tests/2.txt", "r");
    matrix A, B, C;
    stream crime[2];

    initiate_matrix(&A);
    initiate_matrix(&B);
    initiate_matrix(&C);

    check_matrix(fl1);
    check_matrix(fl2);

    pthread_t stream1;
    pthread_t stream2;
    pthread_t stream3;

    crime[0].fl = fl1;
    crime[0].A = &A;
    crime[1].fl = fl2;
    crime[1].A = &B;

    pthread_create(&stream1, NULL, stream_scan, (void *)&crime[0]);
    pthread_create(&stream2, NULL, stream_scan, (void *)&crime[1]);

    crime[0].A = &A;
    crime[0].B = &B;
    crime[0].C = &C;

    pthread_create(&stream3, NULL, stream_act, (void *)&crime[0]);

    pthread_join(stream1, NULL);
    pthread_join(stream2, NULL);
    pthread_join(stream3, NULL);
    print_matrix(C); // Результат должен отправляться в файл

    clear_matrix(A);
    clear_matrix(B);
    clear_matrix(C);

    fclose(fl1);
    fclose(fl2);
    return 0;
}

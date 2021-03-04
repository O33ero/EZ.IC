#include <stdio.h>
#include <malloc.h>
#include <pthread.h>

//структура
typedef struct{
    int** A; // указатель на массив указателей на массив
    int column; // столбцы
    int row; // строчки
} matrix;

int** create_matrix(int column, int row){
    int **a = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++){
        a[i] = (int*)malloc(column * sizeof(int));
    }
    return a;
}

matrix check_file(FILE* fp){
    matrix A;
    int x = 0;
    int y = 0;
    char number_of_digits[100];
    char* str;

    while (1){
        str = fgets(number_of_digits, 100, fp);
        if(str == NULL){
            break;
        } else {
            for (int i = 0; i < (sizeof(str)); i++){
                if ((number_of_digits[i] == ' ') && (y == 0)){
                    x++;
                }
                if (number_of_digits[i] == '\n'){
                    if (y == 0){
                        x = x + 1;
                    }
                    y++;
                }
            }  
        }
    }

    A.A = create_matrix(x, y);
    A.column = x;
    A.row = y;     // !!! Не знаю почему, но матрицу /tests/2.txt он определяет как 3x4, что неверно
    
    int number;
    char ch;
    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i < y; i++){
        for (int j = 0; j < x; j++){
            fscanf(fp, "%d%c", &number, &ch);
            A.A[i][j] = number;
        }
    }
    
    return A;
}

void print_matrix(matrix A){
    for (int i = 0; i < A.row; i++){
        for (int j = 0; j < A.column; j++)
        {
            printf("%d ", A.A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

matrix multiply_matrix(matrix A, matrix B){
    matrix C;
    if (A.column != B.row){
        printf("Can not multiply matrices\n");
        C.A = 0;
        C.column = 0;
        C.row = 0;
        return C;
    }

    C.column = B.column;
    C.row = A.row;
    C.A = create_matrix(C.column, C.row);
    for (int i = 0; i < C.row; i++){
        for (int j = 0; j < C.column; j++){
            C.A[i][j] = 0;
            for (int k = 0; k < A.column; k++){
                C.A[i][j] += A.A[i][k] * B.A[k][j];
            }
        }
    }
    return C;
}

void free_matrix(matrix A){
    for (int i = 0; i < A.row; i++){
        free(A.A[i]);
    }
    free(A.A);
}

void init_matrix(matrix* A){
    A->A = NULL;
    A->column = 0;
    A->row = 0;
}

typedef struct{ // Автор этой структуры гений
    FILE* fp;
    matrix* A;
    matrix* B;
    matrix* C;
} flow_arguments;

void* pthread_check_file(void* args){
    flow_arguments *arg = (flow_arguments*) args; // Автор этого метода генией
    FILE* fp = arg->fp;
    matrix* A = arg->A;
    *A = check_file(fp);
    print_matrix(*A);
    return 0;
}

void* pthread_multiply_matrix(void* args){
    flow_arguments *arg = (flow_arguments*) args; // Автор этого метода гений
    matrix* A = arg->A;
    matrix* B = arg->B;
    matrix* C = arg->C;

    *C = multiply_matrix(*A, *B);
    return 0;
}

int main(int argc, char* argv[]){
    int status;
    FILE *fp1;
    FILE *fp2;
    matrix A, B, C;
    flow_arguments args[2];

    init_matrix(&A);
    init_matrix(&B);
    init_matrix(&C);
    
    if ((fp1 = fopen(argv[1] /*"./tests/1.txt"*/, "r")) == NULL)
    {
        printf("Не удалось открыть файл");
        return 0;
    }
    if ((fp2 = fopen(argv[2] /*"./tests/2.txt"*/, "r")) == NULL)
    {
        printf("Не удалось открыть файл");
        return 0;
    }

    pthread_t flow1;
    pthread_t flow2;
    pthread_t flow3;

    args[0].fp = fp1;
    args[0].A = &A; 
    
    args[1].fp = fp2;
    args[1].A = &B;

    pthread_create(&flow1, NULL, pthread_check_file, (void*) &args[0]);
    pthread_create(&flow2, NULL, pthread_check_file, (void*) &args[1]);

    args[0].A = &A;
    args[0].B = &B;
    args[0].C = &C;

    pthread_create(&flow3, NULL, pthread_multiply_matrix, (void*) &args[0]);

    pthread_join(flow1, NULL);
    pthread_join(flow2, NULL);
    pthread_join(flow3, NULL);
    print_matrix(C);

    // A = check_file(fp1);
    // print_matrix(A);

    // B = check_file(fp2);
    // print_matrix(B);

    // C = multiply_matrix(&A, &B);
    // print_matrix(C);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);

    fclose(fp1);
    fclose(fp2);
    return 0;
}
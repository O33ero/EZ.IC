#include <stdio.h>
#include <malloc.h>
#include <pthread.h>

//структура матрицы
typedef struct{
    int** A; // указатель на массив указателей на массив
    int column; // столбцы
    int row; // строчки
} matrix;

//создание матрицы
int** create_matrix(int column, int row){
    int **a = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++){
        a[i] = (int*)malloc(column * sizeof(int));
    }
    return a;
}

//узнаем размер матрицы
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

    //и тут же создаем и заполняем её
    A.A = create_matrix(x, y);
    A.column = x;
    A.row = y;    
    
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

//воводим содержимое матрицы
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

//перемножение матриц
matrix multiply_matrix(matrix A, matrix B){
    matrix C;
    if (A.column != B.row){
        printf("Can not multiply matrices");
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

//освобождение памяти
void free_matrix(matrix A){
    for (int i = 0; i < A.row; i++){
        free(A.A[i]);
    }
    free(A.A);
}

int main(int argc, char* argv[]){

    FILE *fp1;
    FILE *fp2;
    matrix A, B, C;
    
    if ((fp1 = fopen(argv[1], "r")) == NULL)
    {
        printf("Не удалось открыть файл");
        return 0;
    }
    if ((fp2 = fopen(argv[2], "r")) == NULL)
    {
        printf("Не удалось открыть файл");
        return 0;
    }

    A = check_file(fp1);
    print_matrix(A);

    B = check_file(fp2);
    print_matrix(B);

    C = multiply_matrix(A, B);
    print_matrix(C);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);

    fclose(fp1);
    fclose(fp2);
    return 0;
}
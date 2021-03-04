#include <stdio.h>
#include <malloc.h>

//функция создает массив указателей на массив указателей
int** create_matrix(int size_of_matrix){
    int **a = (int**)malloc(size_of_matrix * sizeof(int*));
    for (int i = 0; i < size_of_matrix; i++){
        a[i] = (int*)malloc(size_of_matrix * sizeof(int));
    }
    return a;
}

//функция узнает размер матрицы
int check_file(FILE* fp){
    int size_of_matrix = 0;
    char number_of_digits[100];
    char* str;
    str = fgets(number_of_digits, 100, fp);

    for (int i = 0; i < (sizeof(str)); i++){
        if ((number_of_digits[i] >= '0') && (number_of_digits[i] <= '9') 
        && (number_of_digits[i] != ' ') && number_of_digits[i] != '\n'){
            size_of_matrix++;
        }
    }
    
    return size_of_matrix;
}

//функция заполняет матрицу элементами из файла
int** fill_matrix(int** matrix, int size_of_matrix, FILE* fp){
    int number;
    char ch;
    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i < size_of_matrix; i++){
        for (int j = 0; j < size_of_matrix; j++){
            fscanf(fp, "%d%c", &number, &ch);
            matrix[i][j] = number;
        }
    }
    
    return matrix;
}

//вывод содержимого матрицы
void print_matrix(int** matrix, int size_of_matrix){
    for (int i = 0; i < size_of_matrix; i++){
        for (int j = 0; j < size_of_matrix; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

//перемножение матриц
int** muliply_matrix(int** matrix1,int** matrix2, int size_of_matrix){
    int** matrix;
    matrix = create_matrix(size_of_matrix);
    for (int i = 0; i < size_of_matrix; i++)
    {
        for (int j = 0; j < size_of_matrix; j++)
        {
            matrix[i][j] = 0;
            for (int k = 0; k < size_of_matrix; k++)
                matrix[i][j] += matrix1[i][k] * matrix2[k][j];  
        }
    }
    return matrix;
}

//освобождение памяти
void free_matrix(int** matrix, int size_of_matrix){
    for (int i = 0; i < size_of_matrix; i++){
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char* argv[]){

    FILE *fp;
    int size_of_matrix = 0;
    int** A;
    int** R;

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("Не удалось открыть файл");
        return 0;
    }


    size_of_matrix = check_file(fp);
    A = create_matrix(size_of_matrix);
    A = fill_matrix(A, size_of_matrix, fp);
    print_matrix(A, size_of_matrix);
    R = muliply_matrix(A, A, size_of_matrix);
    print_matrix(R, size_of_matrix);
    free_matrix(A, size_of_matrix);
    free_matrix(R, size_of_matrix);

    fclose(fp);
    return 0;
}
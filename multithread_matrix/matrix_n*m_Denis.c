#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>


typedef struct {
	int lines_1;
	int columns_1; 
	int lines_2;
	int columns_2;
	int** mass1;
	int** mass2; 
	int** mass_sum;
} pthrData;
int lines_of_matrix(FILE* ptrfile){
	rewind(ptrfile);
	int lines = 0, columns = 0;
	char ch;
	int s, n;
	while ((n = fscanf(ptrfile, "%d%c", &s, &ch)) != -1)
    {

        if (ch == '\n')
        {

            lines++;
        }
    }

	return lines;
}
int columns_of_matrix(FILE* ptrfile1){
	rewind(ptrfile1);
	int columns = 0;
	char ch;
	int s, n;
	while ((n = fscanf(ptrfile1, "%d%c",&s, &ch))!=-1)
	{    
    
	    columns++;
	}
	return columns;
}

void print_matrix(int** mass_sum ){
	for(int i = 0; 1; i++){
		for(int j = 0; 1; j++){
			if(mass_sum[i][j]){
				printf("mass_sum[%d][%d]=%d ", i, j, mass_sum[i][j]);
			}
			else{
				break;
			}
		}
		printf("\n");
	}
}

void* threadFunc(void* thread_data){
	int a=0, sum = 0;
	
	pthrData *data = (pthrData*) thread_data;

	for(int i = 0; i < data->lines_1; i++){
		for(int n = 0; n < data->columns_2; n++){
			for(int j = 0; j < data->columns_1; j++){
				a = data->mass1[i][j] * data->mass2[j][n];
				sum = sum + a;
			}
			data->mass_sum[i][n] = sum;
			sum = 0;
			printf("mass_sum[%d][%d]=%d ", i, n, data->mass_sum[i][n]);
		}
		printf("\n");
	}
 	
	print_matrix(data->mass_sum);

	return NULL;
}


 
int main()
{
    int columns_1 = 0, lines_1 = 0, i, j;
    int columns_2 = 0, lines_2 = 0;
	FILE *ptrfile;
	FILE *ptrfile1;
	char ch;
	int s;
	ptrfile=fopen("mass.txt","r+"); 
	lines_1 = lines_of_matrix(ptrfile);
	columns_1 = columns_of_matrix(ptrfile);
	columns_1 = columns_1 / lines_1;
	printf("lines_1 = %d \n", lines_1);
	printf("columns_1 = %d \n", columns_1);

	ptrfile1=fopen("mass1.txt","r+"); 
	lines_2 = lines_of_matrix(ptrfile1);
	columns_2 = columns_of_matrix(ptrfile1);
	columns_2 = columns_2 / lines_2;
	printf("lines_2 = %d \n", lines_2);
	printf("columns_2 = %d \n", columns_2);

	if (columns_1 == columns_1){
		int **mass = (int **)malloc(sizeof(int *) * lines_1);
		for(int i = 0; i < columns_1; i++) {
		    mass[i] = (int *)malloc(sizeof(int *) * columns_1);
		}
		int **mass1 = (int **)malloc(sizeof(int *) * lines_2);
		for(int i = 0; i < columns_2; i++) {
		    mass1[i] = (int *)malloc(sizeof(int *) * columns_2 );
		}
		int **mass_sum = (int **)malloc(sizeof(int *) * lines_1);
		for(int i = 0; i < columns_2; i++) {
		    mass_sum[i] = (int *)malloc(sizeof(int *) * columns_2);
		}

		rewind(ptrfile);    
		for(i=0;i<lines_1;i++)
		{	
			for (j = 0; j < columns_1; j++){
				fscanf(ptrfile, "%d",&mass[i][j]);
		    	printf("mass[%d][%d]=%d  ", i, j, mass[i][j]);
			}
		    printf("\n");
		}

		rewind(ptrfile1);    
		for(i=0;i<lines_2;i++)
		{	
			for (j = 0; j < columns_2; j++){
				fscanf(ptrfile1, "%d",&mass1[i][j]);
		    	printf("mass1[%d][%d]=%d  ", i, j, mass1[i][j]);
			}
		    printf("\n");
		}

		pthread_t* threads = (pthread_t*) malloc(lines_1 * sizeof(pthread_t));
		pthrData* threadData = (pthrData*) malloc(lines_1 * sizeof(pthrData));

		for(int i = 0; i < lines_1; i++){
			threadData[i].lines_1 = i;
			threadData[i].columns_1 = columns_1;
			threadData[i].columns_2 = columns_2;
			threadData[i].mass1 = mass;
			threadData[i].mass2 = mass1;
			threadData[i].mass_sum = mass_sum;
	 
			pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
		}
	 
		for(int i = 0; i < lines_1; i++)
			pthread_join(threads[i], NULL);
		
		
	}
	else{
		printf("Condition don't complete!\n");
	}

  
	return 0;
}
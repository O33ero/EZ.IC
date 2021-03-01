#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

typedef struct
{
	int string;
	int column;
	int **mass;
	int **mass_sum;
} pthrData;

void *threadFunc(void *thread_data)
{
	int a = 0, sum = 0;
	//получаем структуру с данными
	pthrData *data = (pthrData *)thread_data;

	//складываем элементы строк матриц и сохраняем результат
	for (int i = 0; i < data->string; i++)
	{
		for (int n = 0; n < data->column; n++)
		{
			for (int j = 0; j < data->column; j++)
			{
				a = data->mass[i][j] * data->mass[j][n];
				sum = sum + a;
			}
			data->mass_sum[i][n] = sum;
			sum = 0;
			printf("%d ", data->mass_sum[i][n]);
		}
		printf("\n");
	}

	return NULL;
}

/*
 * Хотелось бы освобождение памяти и переменные не односимвольные и
 * выносить все модули в отдельные функции. Поверь, это очень облегчит работу.
 * А в целом все нравится. :)
*/

int main()
{
	int n, k, i, j;
	FILE *ptrfile;
	k = 0;
	int s;
	ptrfile = fopen("mass.txt", "r+");

	while ((fscanf(ptrfile, "%d", &s) != EOF))
	{
		if (!ptrfile)
		{
			break;
		}
		k++;
	}
	printf("%d\n", k);
	n = k;
	k = sqrt(k);
	if (k * k == n)
	{
		int **mass = (int **)malloc(sizeof(int *) * k);
		for (int i = 0; i < k; i++)
		{
			mass[i] = (int *)malloc(sizeof(int *) * k);
		}
		int **mass_sum = (int **)malloc(sizeof(int *) * k);
		for (int i = 0; i < k; i++)
		{
			mass_sum[i] = (int *)malloc(sizeof(int *) * k);
		}

		rewind(ptrfile);
		for (i = 0; i < k; i++)
		{
			for (j = 0; j < k; j++)
			{
				fscanf(ptrfile, "%d", &mass[i][j]);
				printf("mass[%d][%d]=%d  ", i, j, mass[i][j]);
			}
			printf("\n");
		}

		//выделяем память под массив идентификаторов потоков
		pthread_t *threads = (pthread_t *)malloc(k * sizeof(pthread_t));
		//сколько потоков - столько и структур с потоковых данных
		pthrData *threadData = (pthrData *)malloc(k * sizeof(pthrData));

		//инициализируем структуры потоков
		for (int i = 0; i < k; i++)
		{
			threadData[i].string = i;
			threadData[i].column = k;
			threadData[i].mass = mass;
			threadData[i].mass_sum = mass_sum;

			//запускаем поток
			pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
		}

		//ожидаем выполнение всех потоков
		for (int i = 0; i < k; i++)
			pthread_join(threads[i], NULL);

		//multiplication_of_matrix(mass, k);
	}
	else
	{
		printf("Condition don't complete!\n");
	}

	fclose(ptrfile);

	return 0;
}
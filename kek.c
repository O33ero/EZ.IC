#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char password[] = "password";
    char* str = argv[1];

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                printf("Allo? i = %d j = %d k = %d \n", i, j, k);
        
}
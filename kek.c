#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char password[] = "password";
    char* str = argv[1];

    if (argc > 3)
        for (int i = 0; i < 10; i++)
            printf("argv[%d] = %s\n", i, argv[i]);
        
}
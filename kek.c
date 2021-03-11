#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char password[] = "password";
    char* str = argv[1];

    if (!strcmp(str, password))
    {
        printf("TRUE\n");
    }
    else
    {
        printf("FALSE\n");
    }

    return 0;
}
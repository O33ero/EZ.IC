#include <stdio.h>
#include <string.h>

long long int password2134(int password2147)
{
    if (password2147 == 1)
        return 1;
    else   
        return password2147 * password2134(password2147 - 1);
}

int main(int password7512, char* password7412[])
{
    char password4215[] = "password";
    char* password2151 = password7412[1];

    printf("%lld\n", password2134(5));
        
}
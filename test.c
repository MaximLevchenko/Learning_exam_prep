#include <stdio.h>
#include <string.h>

int main(void)
{
    char a = '4';
    char b = '5';
    int res;
    // char *result = a + b;
    // printf("%d", );
    res = (a - '0') + (b - '0');
    printf("%d\n", res);
    char digit = res - '0';

    printf("%c", digit);

    return 0;
}
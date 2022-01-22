#include <stdio.h>

/** 
 * Bitwise & operator, it takes two numbers and performs bitwise operations.
 * Result of & is 1 when both bits are 1, otherwise its 0.
 * 
 * Bitwise | operator, it takes two numbers and performs bitwise operations.
 * Result of & is 0 when both bits are 0, otherwise its 1.
 * 
 * Bitwise << operator, it takes two numbers and performs bitwise operations.
 * First operand << Second operand   
 * First operand is whose bits get left shifted and second operand decides by how many. 
*/
int main()
{
    int x;
    double y;
    int a = 10 % 16, b = 9 | 24, c = 3 << 1, p = 3 % 4; //3 = 0011  ->  6 = 0110
    printf("%d \n", a);
    return 0;
}
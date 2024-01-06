/*
 * Exercise 4-14
 *
 * Define a macro swap(t,x,y) that interchanges two arguments
 * of type t. (Block structure wil help.)
 *
 */

#include <stdio.h>

#define swap(t,x,y) if (sizeof((x)) == sizeof(t) && sizeof((y)) == sizeof(t)) \
{t temp = ((x)); ((x)) = ((y)), ((y)) = temp;}

int main(void)
{
        int a = 5;
        int b = 10;

        printf("Values before: a = %d, b = %d\n", a, b);

        swap(int, a , b);

        printf("Values after: a = %d, b = %d\n", a, b);

}


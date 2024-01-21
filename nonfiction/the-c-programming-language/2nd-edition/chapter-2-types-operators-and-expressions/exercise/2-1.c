#include <stdio.h>
#include <limits.h>

/* 
 * Exercise 2-1
 *
 * Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing
 * appropriate values from standard headers and by direct computation.
 * Harder if you compute them: determine the ranges of various floating-point
 * types
 */
int main(void) {
        printf("Signed Char Min Value: %d\nSigned Char Max Value: %d\n", SCHAR_MIN, SCHAR_MAX);
        printf("Unsigned Char Min Value: %d\nUnsigned Char Max Value: %u\n", 0, UCHAR_MAX);

        printf("Signed Short Min Value: %d\nSigned Short Max Value: %d\n", SHRT_MIN , SHRT_MAX);
        printf("Unsigned Short Min Value: %d\nUnsigned Short Max Value: %u\n", 0, USHRT_MAX);

        printf("Signed Int Min Value: %d\nSigned Int Max Value: %d\n", INT_MIN, INT_MAX);
        printf("Unsigned Int Min Value: %d\nUnsigned Int Max Value: %u\n", 0, UINT_MAX);

        printf("Signed Long Min Value: %ld\nSigned Long Max Value: %ld\n", LONG_MIN, LONG_MAX);
        printf("Unsigned Long Min Value %d\nUnsigned Long Max Value: %lu\n", 0, ULONG_MAX); 
}


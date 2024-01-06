/*
 * Exercise 4-12
 *
 * Adapt the ideas of printd to write a recursive version
 * of itoa; that is, convert an integer into a string
 * by calling a recursive function
 *
 */

#include <stdio.h>

#define MAX 100

int itoa(int n, char s[], int i)
{
        if (n < 0) {
                n = -n;     /* make n positive */
                s[i++] = '-';
        }

        if (n / 10)
               i = itoa((n / 10), s, i);
                
        s[i++] = (n % 10 + '0');
        s[i] = '\0';
        return i;
}

int main(void) {
        char s[MAX];
        int i = 0;

        itoa(123, s, 0);

        printf("Char value: %s\n", s);
}


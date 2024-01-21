/*
 * Exercise 7-2
 *
 * Write a program that will print arbitrary input in a sensible way.
 *
 * As a minimum, it should print non-graphic characters in octal or hexadecimal
 * according to local custom, and break long text lines.
 *
 */

#include <ctype.h>
#include <stdio.h>

#define MAXLINE 100
#define OCTLEN 6

int main(void) {
        int c, pos;
        int inc(int pos, int n);

        pos = 0;
        while ((c = getchar()) != EOF) {
                if (iscntrl(c) || c == ' ') {
                        pos = inc(pos, OCTLEN);
                        printf(" \\%03o ", c);

                        if (c == '\n') {
                                pos = 0;
                                putchar('\n');
                        }
                } else {
                        pos = inc(pos, 1);
                        putchar(c);
                }
        }

        return 0;
}

int inc(int pos, int n) {
        if (pos + n < MAXLINE) {
                return pos + n;
        } else {
                putchar('\n');
                return n;
        }
}

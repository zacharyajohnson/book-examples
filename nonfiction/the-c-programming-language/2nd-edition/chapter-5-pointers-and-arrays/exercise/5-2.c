/*
 * Exercise 5-2
 *
 * Write getfloat, the floating-point analog of getint
 *
 * What type does getfloat return as its function value?
 *
 */

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint: get next float from input into *pn */
int getfloat(float *pn)
{
        int c, sign;
        int sign_char;
        float fractional_part = 1.0;

        while (isspace(c = getch())) /* skip white space */
                ;
        if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
                ungetch(c); /* it's not a number */
                return 0;
        }
        sign = (c == '-') ? -1: 1;
        if (c == '+' || c == '-') {
                sign_char = c;
                if (!isdigit(c = getch())) {
                        if (c != EOF)
                                ungetch(c);
                        ungetch(sign_char);
                        return sign_char;
                }
        }
        for (*pn = 0.0; isdigit(c); c = getch())
                *pn = 10.0 * *pn + (c - '0');

        if (c == '.') {
                while (isdigit(c = getch())) {
                        *pn = 10.0 * *pn + (c - '0');
                        fractional_part *= 10.0;
                }
                ungetch(c);
        }
        *pn *= sign;
        *pn /= fractional_part;
        if (c != EOF)
                ungetch(c);
        return c;
}

int main(void) {
        float* number;
        getfloat(number);
        printf("Float number 1: %.6f\n", *number);
        getfloat(number);
        printf("Float number 2: %.6f\n", *number);
}

#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;          /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{         
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;

}

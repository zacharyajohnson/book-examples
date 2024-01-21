/*
 * Exercise 4-8
 *
 * Suppose that there will never be more than one character
 * of pushback.
 *
 * Modify getch and ungetch accordingly
 *
 */

#include <stdio.h>

int buf = 0;      /* buffer for ungetch */

int getch(void) /* get a (possibly pushed back) character */
{         
        int c;

        if (buf) {
                c = buf;
        } else {
                c = getchar();
        }
        
        buf = 0;
        
        return c;
}

void ungetch(int c) /* push character back on input */
{
        if (buf)
                printf("ungetch: too many characters\n");
        else {
               buf = c; 
        }
}


#include <stdio.h>

#define MAXLINE 1000

/* 
 * Exercise 2-2
 *
 * Write a loop equivalent to the for
 * loop above without using && or ||
 */
int main(void) {
        /* for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
                s[i] = 0;
         */

        int i, c; 
        char s[MAXLINE];

        int lim = MAXLINE;

        enum loop { FALSE, TRUE };

        enum loop ok_loop = TRUE;

        while (ok_loop == TRUE) {
                c = getchar();

                if (i >= lim - 1) {
                        ok_loop = FALSE;
                } else if (c == EOF) {
                      ok_loop = FALSE;  
                } else if (c == '\n') {
                        ok_loop = FALSE;
                } else {
                        s[i] = c;
                        ++i;
                }

        }
}

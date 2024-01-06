/*
 * Exercise 4-1
 *
 * Write the function strrindex(s,t), which returns
 * the position of the rightmost occurrence of t in s,
 * or -1 if there is none
 *
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int local_getline(char line[], int max);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main(void) {
        char line[MAXLINE];
        int found = 0;
        int index = -1;

        while (local_getline(line, MAXLINE) > 0)
                if ((index = strrindex(line, pattern)) >= 0) {
                        printf("Line: %s, Index: %d\n", line, index);
                        found++;
                }
        return found;
}

int local_getline(char s[], int lim) {
        int c, i;

        i = 0;
        while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
                s[i++] = c;
        if (c == '\n')
                s[i++] = c;
        s[i] = '\0';
        return i;
}

int strrindex(char s[], char t[]) {
        int i, j, k;

        for (i = (strlen(s) - 1); i >= 0; i--) {
                for (j=i, k=(strlen(t) - 1);  k >= 0 && s[j] == t[k]; j--, k--)
                        ;
                if (k == -1)
                        return j + 1;
        }
        return -1;
}


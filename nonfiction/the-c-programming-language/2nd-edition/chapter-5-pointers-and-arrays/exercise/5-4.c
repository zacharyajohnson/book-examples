/*
 * Exercise 5-4
 *
 * Write the function strend(s,t), which returns 1 if the string
 * t occurs at the end of the string s, and zero otherwise.
 *
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int local_getline(char line[], int max);
int strend(char* source, char* searchfor);

char* pattern = "ould";

int main(void) {
        char line[MAXLINE];
        int found = 0;
        int index = -1;

        while (local_getline(line, MAXLINE) > 0)
                if ((index = strend(line, pattern)) >= 0) {
                        printf("Line: %s, Match: %d\n", line, index);
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
                s[i] = '\0';
        return i;
}

int strend(char* s, char* t) {
        char* start_s = s;
        char* start_t = t;

        for( ; *s != '\0'; s++)
                ;

        for( ; *t != '\0'; t++)
                ;

        for( ; *s == *t; s--, t--) {
                if ( t == start_t || s == start_s) {
                        break;
                }
        }

        if (*s == *t && t == start_t && *s != '\0') {
                return 1;
        } else {
                return 0;
        }
}


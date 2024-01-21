/*
 * Exercise 5-6
 *
 * Rewrite appropriate programs from earlier chapters and exercises with pointers instead
 * of array indexing
 *
 * Good possibilities include getline (Chapters 1 and 4)
 * atoi, itoa, and their variants (Chapters 2, 3, and 4),
 * reverse (Chapter 3), and strindex and getop (Chapter 4)
 *
 */

#include <stdio.h>
#include <string.h>

void itoa(int, char*);
int atoi(char*);
void squeeze(char*, int);
void reverse(char*);

/* reverse: reverse string s in place */
void reverse(char* s)
{
        int c;
        char* start = s;
        char* end = s;

        for(; *end != '\0'; end++)
                ;
        end--;

        for (; start < end; start++, end--) {
                c = *start;
                *start = *end;
                *end = c;
        }
}

/* itoa: convert n to characters in s */
void itoa(int n, char* s) {
        char* start = s;
        int sign;

        if ((sign = n) < 0) /* record sign */
                n = -n;     /* make n positive */
        do {    /* generate digits in reverse order */
                *s++ = n % 10 + '0';
        } while ((n /= 10) > 0);

        if (sign < 0)
                *s++ = '-';

        *s = '\0';
        reverse(start);
}

int atoi(char* s) {
        int n;

        n = 0;

        for ( ; *s >= '0' && *s <= '9'; s++)
                n = 10 * n + (*s - '0');
        return n;
}

/* squeeze: delete all c from s */
void squeeze(char* s, int c)
{
        char* j = s;

        for ( ; *s != '\0'; s++)
                if (*s != c) {
                        *j = *s;
                        j++;
                }
        *j = '\0';
}


int main(void) {
        char reverse_char[100] = "Reverse test";
        reverse(reverse_char);
        printf("Reverse test: %s\n", reverse_char);

        char itoa_char[100];
        itoa(123, itoa_char);
        printf("Itoa test: %s\n", itoa_char);

        printf("atoi test: %d\n", atoi("123"));

        char squeeze_char[100] = "Squeexxxxxxxxxxxze";
        squeeze(squeeze_char, 'x');

        printf("squeeze test: %s\n", squeeze_char);
}

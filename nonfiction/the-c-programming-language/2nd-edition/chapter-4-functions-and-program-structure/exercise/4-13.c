/*
 * Exercise 4-13
 *
 * Write a recursive version of the function reverse(s),
 * which reverses the string s in place
 *
 */

#include <stdio.h>

#define MAX 100

void reverse(char []);
void reverse_r(char [], int, int);

void reverse(char s[])
{
        int i = 0;

        for (i = 0; s[i] != '\0'; i++)
                ;

        // back up one to get the true length of string
        i -= 1;

        reverse_r(s, 0, i);
}

void reverse_r(char s[], int start, int end) {
        if (start <= end) {
                char char_1 = s[start];
                char char_2 = s[end];

                s[start] = char_2;
                s[end] = char_1;

                start++;
                end--;

                reverse_r(s, start, end);
        }
}

int main(void) {
        char s[MAX] = "Hello World!";

        reverse(s);

        printf("Reversed String: %s\n", s);
}


/*
 * Exercise 3-2
 *
 * Write a function escape(s,t) that converts characters
 * like newline and tab into visible escape sequences like
 * \n and \t as it copies the string t to s. Use a switch
 *
 * Write a function for the other direction as well, converting
 * escape sequences into the real characters.
 *
 */

#include <stdio.h>

#define SIZE 1000

void escape (char s[], char t[]) {
        int j = 0;
        int i = 0;
        for (i = j = 0; t[i] != '\0'; ++i, ++j) {
                switch (t[i]) {
                        case '\n':
                                s[j] = '\\';
                                j++;
                                s[j] = 'n';
                                break;
                        case '\t':
                                s[j] = '\\';
                                j++;
                                s[j] = 't';
                                break;
                        default:
                                s[j] = t[i];
                                break;
                }
        }
        s[j] = '\0';
} 

void revert_escape (char s[], char t[]) {
        int j = 0;
        int i = 0;
        for (i = j = 0; t[i] != '\0'; i++, j++) {
                switch (t[i]) {
                        case '\\':
                                switch (t[++i]) {
                                        case 't':
                                                s[j] = '\t';
                                                break;
                                        case 'n':
                                                s[j] = '\n';
                                                break;
                                        default:
                                                s[j] = t[i];
                                                break;
                                }
                                break;
                        default:
                                s[j] = t[i];
                                break;
                }
        }
        s[j] = '\0';
}

int main(void) {
        char s[SIZE] = "";
        char t[SIZE] = "This \n is\t a\n test.";

        escape(s, t);
        printf("Escaped characters: %s\n", s);

        revert_escape(s,t);
        printf("Non escaped characters: %s\n", s);

        return 0;
}

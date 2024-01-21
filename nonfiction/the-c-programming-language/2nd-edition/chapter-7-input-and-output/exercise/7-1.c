/*
 * Exercise 7-1
 *
 * Write a program that converts upper case to lower or
 * lower case to upper, depending on the name it is invoked
 * with, as found in argv[0]
 *
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
        int c;
        int (*function)(int ch);

        if (strstr(argv[0], "upper") != NULL) {
                function = toupper;
        } else {
                function = tolower;
        }

        while ((c = getchar()) != EOF)
                putchar((*function)(c));
        return 0;
}

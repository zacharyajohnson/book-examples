/*
 * Exercise 2-10
 *
 * Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expression instead of if else
 *
 */

#include <stdio.h>

void lower(char string[]) {
        for (int i = 0; string[i] != '\0'; i++) {
                char c = string[i];
                string[i] = (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')): c;
        }
}

int main(void) {
        char string[] = "THIS is A TEST fOR LOwER FUNcTIOn";
        printf("Original String: %s\n", string);

        lower(string);

        printf("Lowered String: %s\n", string);

}

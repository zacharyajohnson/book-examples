/*
 * Exercise 2-5
 *
 * Write the function any(s2, s2), which returns the first location
 * in the string s1 where any character from the the string s2 occurs, or 
 * -1 if s1 contains no characters from s2
 *
 */

#include <stdio.h>

int any(char s1[], char s2[]) {
        for (int i = 0; s1[i] != '\0' ; i++) {
                for (int j = 0; s2[j] != '\0'; j++) {
                        if (s1[i] == s2[j]) {
                                return i;
                        }
                }
        }

        return -1;
}

int main(void) {

        // Should be the h in 'This'
        char s1[] = "This is a test";
        char s2[] = "ih";

        int location = any(s1, s2);

        printf("Location: %d\n", location);
}

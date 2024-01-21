/*
 * Exercise 2-4
 *
 * Write an alternate version of squeeze(s1, s2) that deletes each character in s1
 * that matches any character in the string s2
 *
 */

#include <stdio.h>

void squeeze(char s1[], char s2[]) {
        int j;
        int final_string_index = 0;

        for (int i = 0; s1[i] != '\0'; i++) {
                for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; j++) {
                        ;
                }

                if (s2[j] == '\0') {
                        s1[final_string_index++] = s1[i];
                }
        }

        s1[final_string_index] = '\0';
}

int main(void) {
        char s1[] = "Te))st string---***";
        char s2[] = "-)*";

        squeeze(s1, s2);

        printf("Sanitized value: s1=%s, s2=%s\n", s1, s2);
}

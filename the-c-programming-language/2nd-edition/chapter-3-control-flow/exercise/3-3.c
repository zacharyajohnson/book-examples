/*
 * Exercise 3-3
 *
 * Write a function expand(s1, s2) that expands shorthand notations
 * like a-z in the string s1 into the equivalent complete list abc...xyz
 * in s2.
 *
 * Allow for letters of either case and digits, and be prepared to handle
 * cases like a-b-c and a-z0-9 and -a-z.
 * Arrange that a leading or trailing - is taken literally
 *
 */

#include <ctype.h>
#include <stdio.h>

#define ARRAY_SIZE 1000

void expand(char s1[], char s2[]) {

        int s2_index = 0;
        for(int i = 0; s1[i] != '\0' ; i++) {
                if (s1[i] == '-' && i != 0 && s1[i+1] != '\0') {
                        char start_range = s1[i - 1];
                        char end_range = s1[i + 1];

                        for (int j = start_range; j <= end_range; j++, s2_index++) {
                                // Support fragmented ranges like a-b-c
                                // If the range (a-b)(b-c) has a common
                                // start and end range, don't add
                                // again or we are going to get duplicates
                                if (s2_index == 0 || (s2[s2_index-1] != j)) {
                                        s2[s2_index] = j;
                                } else {
                                        s2_index--;
                                }
                        }
                }

        }

        s2[s2_index] = '\0';
}

int main(void) {
        char s2[ARRAY_SIZE];

        expand("a-z", s2);
        printf("Entire lower alphabet expanded: %s\n", s2);

        expand("d-h", s2);
        printf("Partial lower alphabet expanded: %s\n", s2);

        expand("a-z0-9", s2);
        printf("Entire lower alphabet + digits expanded: %s\n", s2);

        expand("A-Z", s2);
        printf("Entire upper alphabet expanded: %s\n", s2);

        expand("D-G", s2);
        printf("Partial upper alphabet expanded: %s\n", s2);

        expand("A-Z0-9", s2);
        printf("Entire upper alphabet + digits expanded: %s\n", s2);

        expand("a-c-g", s2);
        printf("Fragmented lower alphabet expanded: %s\n", s2);

        expand("-c-g", s2);
        printf("Leading - lower alphabet expanded: %s\n", s2);

        expand("c-g-", s2);
        printf("Trailing - lower alphabet expanded: %s\n", s2);

}

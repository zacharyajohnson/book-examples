#include <stdio.h> 

#define NUM_DISTINCT_CHARS 300 

/*
 * Exercise 1-14
 *
 * Write a program to print a histogram of the frequencies of
 * different characters in its input.
 */
int main(void) {
        int c; 
        int char_count_hist[NUM_DISTINCT_CHARS];

	for (int i = 0; i < NUM_DISTINCT_CHARS; ++i)
		char_count_hist[i] = 0;

	while ( (c = getchar()) != EOF) {
                // Don't display invisible chars
                if (c >= '!' && c <= '~') {
                        char_count_hist[c]++;
                }
	}

        for (int i = 0; i < NUM_DISTINCT_CHARS; ++i) {
                if (char_count_hist[i] > 0) {
                        printf("Char count for %c: ", i);
                        for (int j = 0; j < char_count_hist[i]; ++j) {
                                printf("|");
                        }

                        printf("\n");
                }

        }

        return 0;
}

#include <stdio.h> 

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */
#define MAX_WORD_LENGTH 100

/*
 * Exercise 1-13
 *
 * Write a program to print a histogram of the lengths of
 * words in its input.
 *
 * It is easy to draw the histogram with the bars horizontal; a vertical
 * orientation is more challenging.
 */
int main(void) {
        int c, state; 
        state = OUT;
        int word_length = 0;
        int word_length_hist[MAX_WORD_LENGTH];

	for (int i = 0; i < MAX_WORD_LENGTH; ++i)
		word_length_hist[i] = 0;


	state = OUT;

	while ( (c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;

                        // Ignore stray blanks between words
                        // Otherwise it will be interpreted
                        // as another word
                        if (word_length != 0) {
                                word_length_hist[word_length]++;
                        }

                        word_length = 0;
                } else {
			state = IN;
		} 
                
                if (state == IN) {
                        word_length++;
                }
	}

        for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
                if (word_length_hist[i] > 0) {
                        printf("Word Length %d: ", i);

                        for (int j = 0; j < word_length_hist[i]; ++j) {
                                printf("|");
                        }

                        printf("\n");
                }
        }

        return 0;
}

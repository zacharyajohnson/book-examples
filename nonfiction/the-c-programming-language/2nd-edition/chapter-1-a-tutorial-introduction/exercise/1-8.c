#include <stdio.h>

/* 
 * Exercise 1-8
 *
 * Write a program to count blanks, tabs, and newlines.
 */
int main(void) {
	int c; 
	long newline_count = 0, tab_count = 0, blank_count = 0;

	while ( (c = getchar()) != EOF ) {
		if (c == '\n')
			++newline_count;
		if (c == '\t')
			++tab_count;
		if (c == ' ')
			++blank_count;
	}

	printf("Blank Count: %ld\n", blank_count);
	printf("Tab Count: %ld\n", tab_count);
	printf("Newline Count: %ld\n", newline_count);

}

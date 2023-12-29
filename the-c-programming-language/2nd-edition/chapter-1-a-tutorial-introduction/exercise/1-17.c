#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */
#define LONG_LINE_WIDTH 80

int get_line(char line[], int maxline);

/* 
 * Exercise 1-17
 *
 * Write a program to print all input lines that are longer than 80 characters
 */
int main(void) {
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	while ( ( len = get_line(line, MAXLINE) ) > 0 ) {

		if (len > LONG_LINE_WIDTH) {
			printf("%d, %s", len, line);
		}
	}

	return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim) {
	int c, i, j;

	j = 0;

	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
		if (i < lim - 2) {
			s[j] = c;
			++j;
		}
	}
	
	if (c == '\n') {
		s[j] = c;
		++j;
		++i;
	}

	s[j] = '\0';

	return i;
}

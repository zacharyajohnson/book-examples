#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);
int remove_blanks(char line[]);

/* 
 * Exercise 1-18
 *
 * Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines
 */
int main(void) {
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	while ( ( len = get_line(line, MAXLINE) ) > 0 ) {

		if ( remove_blanks(line) > 0)
			printf("%s", line);
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

int remove_blanks(char line[]) {
	int i = 0;

	while (line[i] != '\n')
		++i;
	--i;

	while (i >= 0 && (line[i] == ' ' || line[i] == '\t') )
		--i;

	if (i >= 0) {
		++i;
		line[i] = '\n';
		++i;
		line[i] = '\0';
	}

	return i;
}

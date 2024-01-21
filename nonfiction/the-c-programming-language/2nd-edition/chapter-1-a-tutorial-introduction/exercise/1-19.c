#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);
void reverse(char line[]);

/* 
 * Exercise 1-19
 *
 * Write a function reverse that reverses the character
 * string s. Use it to write a program that reverses its input a line at a time
 */
int main(void) {
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	while ( ( len = get_line(line, MAXLINE) ) > 0 ) {
		reverse(line);
		printf("%d, %s", len, line);
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

void reverse(char line[]) {
	int i = 0;
	int j = 0;

	char temp_char;

	while (line[i] != '\0')
		++i;

	--i;

	if (line[i] == '\n')
		--i;

	while(j < i) {
		temp_char = line[j];
		line[j] = line[i];
		line[i] = temp_char;
		
		--i;
		++j;
	}

}

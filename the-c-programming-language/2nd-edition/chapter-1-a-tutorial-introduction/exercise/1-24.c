#include <stdio.h>

int brace, brack, paren;

void in_quote(int c);
void in_comment(void);
void search(int c);

/* 
 * Exercise 1-24
 *
 * Write a program to check a C program for Rudimentary syntax
 * errors like unbalanced parentheses, brackets and braces. Don't forget
 * about quotes, both single and double, escape sequnces, and comments. (This
 * program is hard if you do it in full generality.)
 */
int main(void) {
	int c;
	extern int brace, brack, paren;

	while ( (c = getchar()) != EOF) {
		if (c == '/') {
			if ( ( c = getchar()) == '*') {
				in_comment();
			} else {
				search(c);
			}

		} else if (c == '\'' || c == '"') {
			in_quote(c);
		} else {
			search(c);
		}

		if (brace < 0) {
			printf("Unbalanced braces\n");
			brace = 0;
		}

		if (brack < 0) {
			printf("Unbalanced brackets\n");
			brack = 0;
		}

		if (paren < 0) {
			printf("Unbalanced parentheses\n");
			paren = 0;
		}
	}

	if (brace > 0 ) {
		printf("Unbalanced braces\n");
	}

	if (brack > 0) {
		printf("Unbalanced brackets\n");
	}

	if (paren > 0) {
		printf("Unbalanced parentheses\n");
	}

}

void in_quote(int c) {
	int d;

	while ( (d = getchar()) != c) {
		if (d == '\\') {
			getchar();
		}
	}
}

void in_comment(void) {
	int c, d;

	c = getchar();
	d = getchar();

	while (c != '*' || d != '/') {
		c = d;
		d = getchar();
	}
}

void search(int c) {
	extern int brace, brack, paren;

	if (c == '{') {
		++brace;
	} else if (c == '}') {
		--brace;
	} else if (c == '[') {
		++brack;
	} else if (c == ']') {
		--brack;
	} else if ( c == '(') {
		++paren;
	} else if (c == ')') {
		--paren;
	}
}

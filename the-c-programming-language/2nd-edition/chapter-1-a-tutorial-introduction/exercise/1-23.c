#include <stdio.h>

void read_comment(int character);
void skip_comment(void);
void echo_quote(int character_quote);

/* 
 * Exercise 1-23
 *
 * Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. 
 * C comments do not nest
 */
int main(void) {
	int current_char;

	while ( (current_char = getchar()) != EOF) {
		read_comment(current_char);
	}

	return 0;
}

void read_comment(int character) {
	int current_char = character;
	int next_char;

	if (current_char == '/') {
		if ( (next_char = getchar()) == '*') {
			skip_comment();
		} else if (next_char == '/') {
			putchar(current_char);
			read_comment(next_char);
		} else {
			putchar(current_char);
			putchar(next_char);
		}

	} else if (current_char == '\'' || current_char == '"') {
		echo_quote(current_char);
	} else {
		putchar(current_char);
	}

}

void skip_comment(void) {
	int current_char, next_char;

	current_char = getchar();
	next_char = getchar();

	while(current_char != '*' || next_char != '/') {
		current_char = next_char;
		next_char = getchar();
	}
}

void echo_quote(int character_quote) {
	int current_char;

	putchar(character_quote);

	while ((current_char = getchar()) != character_quote) {
		putchar(current_char);
		if (current_char == '\\') {
			putchar(getchar());
		}
	}

	putchar(current_char);

}

/*
 * Exercise 4-5
 *
 * Add access to library functions like sin, exp, and pow.
 *
 * See <math.h> in Appendix B, Section 4
 *
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>     /* for atof() */

#define MAXOP 100       /* max size of operand or operator */

enum OpCode {
        UNKNOWN = -999,
        NUMBER = '0',
        EULERS_NUMBER = 'e',
        POWER = '^',
        PEEK_STACK = 'p' + 'e' + 'e' + 'k' + '_' + 's' + 't' + 'a' + 'c' + 'k',
        DUPLICATE_TOP_STACK_ITEM = 'd' + 'u' + 'p' + '_' + 's' + 't' + 'a' + 'c' + 'k',
        SWAP_TOP_TWO_STACK_ITEMS = 's' + 'w' + 'a' + 'p' + '_' + 's' + 't' + 'a' + 'c' + 'k',
        CLEAR_STACK = 'c' + 'l' + 'e' + 'a' + 'r' + '_' + 's' + 't' + 'a' + 'c' + 'k',
        END_OF_LINE = '\n',
        MODULUS = '%',
        MULTIPLICATION = '*',
        ADDITION = '+',
        SUBTRACTION = '-',
        DIVISION = '/',
        SINE = 's' + 'i' + 'n' + 'e' 
};

int string_to_int(char []);
void clear(void);
void push(double);
double peek(void);
double pop(void);
enum OpCode getop(char []);
int getch(void);
void ungetch(int);

/* reverse Polish calculator */
main()
{
        enum OpCode type;
        double op2;
        char s[MAXOP];

        while ((type = getop(s)) != EOF) {
                switch (type) {
                        case NUMBER:
                                push(atof(s));
                                break;
                        case ADDITION:
                                push(pop() + pop());
                                break;
                        case MULTIPLICATION:
                                push(pop() * pop());
                                break;
                        case SUBTRACTION:
                                op2 = pop();
                                push(pop() - op2);
                                break;
                        case DIVISION:
                                op2 = pop();
                                if (op2 != 0.0)
                                        push(pop() / op2);
                                else
                                        printf("error: zero divisor\n");
                                break;
                        case MODULUS:
                                op2 = pop();
                                if (op2 != 0.0)
                                        push((long)pop() % (long)op2);
                                else
                                        printf("error: zero divisor\n");
                                break;
                        case EULERS_NUMBER:
                                double e = exp(pop());
                                push(e);
                                break;
                        case POWER:
                                op2 = pop();
                                double power = pow(pop(), op2);
                                push(power);
                                break;
                        case SINE:
                                double sine = sin(pop());
                                push(sine);
                                break;
                        case END_OF_LINE:
                                printf("\t%.8g\n", pop());
                                break;
                        case PEEK_STACK:
                                printf("Top of stack: \t%.8g\n", peek());
                                break;
                        case CLEAR_STACK:
                                printf("Clearing stack\n");
                                clear();
                                break;
                        case DUPLICATE_TOP_STACK_ITEM:
                                double dup_item = peek();
                                push(dup_item);
                                break;
                        case SWAP_TOP_TWO_STACK_ITEMS:
                                double top_item = pop();
                                double second_item = pop();

                                push(top_item);
                                push(second_item);
                                break;
                        case UNKNOWN:
                                // Eat rest of line and clear stack since we don't know what to do
                                while (getch() != '\n')
                                        ;
                                clear();
                                printf("error: unknown command %s\n", s);
                                break;
                }

        }
        return 0;
}

int string_to_int(char s[]) {
        int i = 0;
        int c;
        int value = 0;

        while ( (c = s[i++]) != '\0' )
                value += c;
        return value;
}

#define MAXVAL 100      /* maximum depth of val stack */
int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

void clear(void) {
        sp = 0;
}

/* push: push f onto value stack */
void push (double f)
{
        if (sp < MAXVAL)
                val[sp++] = f;
        else
                printf("error: stack full, can't push %g\n", f);
}

/* return value at top of stack without popping */
double peek (void)
{
        if (sp > 0) {
                int i = sp - 1;
                return val[i];
        }
        else {
                printf("error: stack empty\n");
                return 0.0;
        }
}

/* pop: pop and return top value from stack */
double pop(void)
{
        if (sp > 0)
                return val[--sp];
        else {
                printf("error: stack empty\n");
                return 0.0;
        }
}

/* getop: get next operator or numeric operand */
enum OpCode getop(char s[]) 
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';


	i = 0;
	if (c == '-') {                      /* check sign */
		if (!isdigit(s[++i] = c = getch())) {
			ungetch(c);
			c = s[0];                  /* not a sign */
		}
        }

        if (isalpha(c)) {
                for (c = getch(); isalpha(c) || c == '_'; c = getch())
                        s[++i] = c;

                s[i + 1] = '\0';
                int string_int_value = string_to_int(s);

                switch (string_int_value) {
                        case SINE:
                                ungetch(c);
                                return string_int_value;
                        case CLEAR_STACK:
                        case PEEK_STACK:
                        case SWAP_TOP_TWO_STACK_ITEMS:
                        case DUPLICATE_TOP_STACK_ITEM:
                                return string_int_value;
                        default:
                                return UNKNOWN;
                }
        }

                                

	if (!isdigit(c) && c != '.')
		return c;                      /* not a number */

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if( c == '.')                      /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;          /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{         
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;

}


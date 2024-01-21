/*
 * Exercise 4-4
 *
 * Add commands to print the top element of the stack
 * without poping, to duplicate it, and to swap the top
 * two elements.
 *
 * Add a command to clear the stack. 
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>     /* for atof() */

#define MAXOP 100       /* max size of operand or operator */

enum OpCode {
        NUMBER = '0',
        PEEK_STACK = 'p',
        DUPLICATE_TOP_STACK_ITEM = 'd',
        SWAP_TOP_TWO_STACK_ITEMS = 's',
        CLEAR_STACK = 'c',
        END_OF_LINE = '\n',
        MODULUS = '%',
        MULTIPLICATION = '*',
        ADDITION = '+',
        SUBTRACTION = '-',
        DIVISION = '/'
};

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
                        default:
                                printf("error: unknown command %s\n", s);
                                break;
                }

        }
        return 0;
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


        // Need to handle (c)lear stack and (p)rint
        // stack commands. We have to intentionally
        // eat the /n so the case statement above
        // doesn't think its the end of the line
        // of a operation like addition
        if (c == CLEAR_STACK || c == PEEK_STACK || c == SWAP_TOP_TWO_STACK_ITEMS || c == DUPLICATE_TOP_STACK_ITEM) {
                int possible_newline = getch();

                if (possible_newline == '\n') {
                        return c;
                } else {
                        ungetch(possible_newline);
                }

        }

	i = 0;
	if (c == '-') {                      /* check sign */
		if (!isdigit(s[++i] = c = getch())) {
			ungetch(c);
			c = s[0];                  /* not a sign */
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


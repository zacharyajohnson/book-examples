/*
 * Exercise 4-11
 *
 * Modify getop so that it doesn't need to use ungetch.
 *
 * Hint: use an internal static variable
 *
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>     /* for atof() */

#define MAXOP 100       /* max size of operand or operator */

enum OpCode {
        VAR = -1000,
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
        VARIABLE_ASSIGNMENT = '=',
        PRINT_VARIABLE_VALUE = 'p' + 'r' + 'i' + 'n' + 't' + '_' + 'v' + 'a' + 'r',
        LAST_PRINTED_VALUE = 'l' + 'a' + 's' + 't' + '_' + 'p' + 'r' + 'i' + 'n' + 't' + 'e' + 'd' + '_' + 'v' + 'a' + 'l' + 'u' + 'e',
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
void ungets(char []);
void ungetch(int);
double get_var_value(int);
void assign_var_value(double, int);

double vars[26];
double last_printed_value;

double get_var_value(int var_name) {
        return vars[var_name - 'a'];
}

void assign_var_value(double var_value, int var_name) {
        vars[var_name - 'a'] = var_value;
}

/* reverse Polish calculator */
main()
{
        enum OpCode type;
        double op2;
        char s[MAXOP];

        while ((type = getop(s)) != EOF) {
                switch (type) {
                        case VAR:
                                push(s[0]);
                                break;
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
                                last_printed_value = pop();
                                printf("\t%.8g\n", last_printed_value);
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
                        case VARIABLE_ASSIGNMENT:
                                double var_value = pop();
                                double var_name = pop();
                                assign_var_value(var_value, var_name);
                                push(get_var_value(var_name));
                                break;
                        case PRINT_VARIABLE_VALUE:
                                printf("\t%.8g\n", get_var_value(pop()));
                                break;
                        case LAST_PRINTED_VALUE:
                                printf("\t%.8g\n", last_printed_value);
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

                if (string_int_value >= 'a' && string_int_value <= 'z') {
                        ungetch(c);
                        return VAR;
                }

                switch (string_int_value) {
                        case SINE:
                                ungetch(c);
                                return string_int_value;
                        case CLEAR_STACK:
                        case PRINT_VARIABLE_VALUE:
                        case LAST_PRINTED_VALUE:
                        case PEEK_STACK:
                        case SWAP_TOP_TWO_STACK_ITEMS:
                        case DUPLICATE_TOP_STACK_ITEM:
                                return string_int_value;
                        default:
                                ungetch(c);
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

/* This is int to handle EOF on some machines */
int buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;          /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{         
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungets(char s[]) {
        int i = 0;

        for (i = 0; s[i] != '\0'; i++)
                ;

        while (--i >= 0)
                ungetch(s[i]);
}

void ungetch(int c) /* push character back on input */
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;

}


/*
 * Exercise 5-10 
 *
 * Write the program expr, which evaluates a reverse Polish expression
 * from the command line, where each operator or operand is a seperate
 * argument. For example,
 *
 *      expr 2 3 4 + *
 *
 * evaluates 2 x (3+4) 
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
        MODULUS = '%',
        MULTIPLICATION = '*',
        ADDITION = '+',
        SUBTRACTION = '-',
        DIVISION = '/',
        SINE = 's' + 'i' + 'n' + 'e' 
};

int string_to_int(char*);
void clear(void);
void push(double);
double peek(void);
double pop(void);
enum OpCode getop(char []);
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
int main(int argc, char* argv[])
{
        int i = 0;
        enum OpCode type;
        double op2;
        char s[MAXOP];

        while (++i < argc) {
                type = getop(argv[i]);
                switch (type) {
                        case NUMBER:
                                push(atof(argv[i]));
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
                        case UNKNOWN:
                                printf("error: unknown command %s\n", s);
                                return -1;
                }
        }
        printf("\t%.8g\n", pop());
        return 0;
}

int string_to_int(char* s) {
        int c;
        int value = 0;

        while ( (c = *s++) != '\0')
                value += c;
        return value;
}

#define MAXVAL 100      /* maximum depth of val stack */
int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

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
enum OpCode getop(char* s) 
{
	int c;
	while ((c = *s++) == ' ' || c == '\t')
		;
        s--;

        /* Start of string minus trailing blanks */
        char* start = s;
	if (c == '-') {                      /* check sign */
		if (!isdigit(c = *++s)) {
			c = *--s;                  /* not a sign */
		}
        }

        if (isalpha(c)) {
                int string_int_value = string_to_int(start);

                switch (string_int_value) {
                        case SINE:
                                return string_int_value;
                        default:
                                return UNKNOWN;
                }
        }

                                

	if (!isdigit(c) && c != '.')
		return c;                      /* not a number */

	return NUMBER;
}


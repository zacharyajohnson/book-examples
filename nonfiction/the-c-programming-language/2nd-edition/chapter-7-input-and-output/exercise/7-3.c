/*
 * Exercise 7-3
 *
 * Revise minprintf to handle more of the other facilities of printf
 *
 */

#include <stdarg.h>
#include <stdio.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
        va_list ap; /* points to each unnamed arg in turn */
        char *p, *sval;
        int ival;
        double dval;
        char charval;

        va_start(ap, fmt); /* make ap point to 1st unnamed arg */

        for (p = fmt; *p; p++) {
                if (*p != '%') {
                        putchar(*p);
                        continue;
                }

                switch (*++p) {
                        case 'e':
                        case 'E':
                                dval = va_arg(ap, double);
                                printf("%e", dval);
                                break;
                        case 'c':
                                charval = va_arg(ap, char);
                                printf("%c", charval);
                                break;
                        case 'd':
                        case 'i':
                                ival = va_arg(ap, int);
                                printf("%d", ival);
                                break;
                        case 'f':
                        case 'F':
                                dval = va_arg(ap, double);
                                printf("%d", dval);
                                break;
                        case 's':
                                for (sval = va_arg(ap, char*); *sval; sval++) {
                                        putchar(*sval);
                                }
                                break;
                        default:
                                putchar(*p);
                                break;
                }
        }
        va_end(ap); /* clean up when done */
}

int main(void) {

}


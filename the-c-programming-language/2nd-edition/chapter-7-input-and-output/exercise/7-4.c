/*
 * Exercise 7-4
 *
 * Write a private version of scanf analogous to minprintf from
 * the previous section
 *
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

void minscanf(char *fmt, ...)
{
        va_list ap; /* points to each unnamed arg in turn */
        char *p, *sval;
        int* ival;
        double* dval;

        va_start(ap, fmt); /* make ap point to 1st unnamed arg */

        char local_format[1000];
        int i = 0;

        for (p = fmt; *p; p++) {
                if (*p != '%') {
                        local_format[i++] = *p;
                        continue;
                }

                local_format[i++] = '%';
                while (*(p + 1) && !isalpha(*(p+1)))
                        local_format[i++] = *++p;
                local_format[i++] = *++p;
                local_format[i] = '\0';

                switch (*++p) {
                        case 'd':
                                ival = va_arg(ap, int*);
                                scanf(local_format, ival);
                                break;
                        case 'f':
                                dval = va_arg(ap, double*);
                                scanf(local_format, dval);
                                break;
                        case 's':
                                sval = va_arg(ap, char*);
                                scanf(local_format, sval);
                                break;
                        default:
                                scanf(local_format);
                                break;
                }

                i = 0;
        }
        va_end(ap); /* clean up when done */
}

int main(void) {
        int* int_value;
        float* float_value;
        char char_value[100];

        minscanf("%d %f %s", int_value, float_value, char_value);

        printf("Variable values: int = %d, float = %f, char* = %s", int_value, float_value, char_value);

        return 0;
}


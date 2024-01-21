/*
 * Exercise 4-2
 *
 * Extend atof to handle scientific notation of the form
 *      123.45e-6
 *
 * where a floating-point number may be followed by
 * e or E and an optionally signed exponent
 *
 */

#include <ctype.h>
#include <stdio.h>

/* atof: convert string s to double */
double atof(char s[])
{
        double val, power, exponent;
        int i, sign, exponent_sign;

        for (i = 0; isspace(s[i]); i++) /* skip white space */
                ;
        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
                i++;
        for (val = 0.0; isdigit(s[i]); i++)
                val = 10.0 * val + (s[i] - '0');
        if (s[i] == '.')
                i++;
        for (power = 1.0; isdigit(s[i]); i++) {
                val = 10.0 * val + (s[i] - '0');
                power *= 10.0;
        }

        if (s[i] == 'e' || s[i] == 'E') {
                i++;

                exponent_sign = (s[i] == '-') ? -1 : 1;
                if (s[i] == '+' || s[i] == '-')
                        i++;

                for (exponent = 0.0; isdigit(s[i]); i++)
                        exponent = 10.0 * exponent + (s[i] - '0');

                while (exponent-- != 0)
                        power = (exponent_sign > 0) ? power / 10: power * 10;

                
        } 

        return sign * val / power;
}

int main(void) {
        printf("%.10f\n", atof("123.45e-6"));
}


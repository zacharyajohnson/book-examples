/*
 * Exercise 2-3
 *
 * Write the function htoi(s), which converts a string
 * of hexadecimal digits (including an optional 0x or 0X) into its
 * equivalent integer value.
 *
 * The allowable digits are 0 through 9, a through f, and A through F
 *
 */

#include <ctype.h>
#include <stdio.h>

#define MAX_STRING_LENGTH 1000

int htoi(const char string[]) {
        int int_value = 0;
        int index = 0;
        
        // If optional prefix is there
        if (string[0] == '0' && tolower(string[1] == 'x') && string[2] != '\0' ) {
                index = 2;
        }

        for ( ; string[index] != '\0' ; ++index ) {
                char c = string[index];
                int hex_digit = 0;

                if ( !isdigit(c) && (tolower(c) < 'a' || tolower(c) > 'f') ) {
                        return -1;
                } else if (isdigit(c)) {
                        hex_digit = string[index] - '0';
                } else {
                        hex_digit = tolower(string[index]) - 'a' + 10;
                }

                int_value = (16 * int_value) + hex_digit;
        } 

        return int_value;
}

int main(void) {
        char string[MAX_STRING_LENGTH];

        printf("Enter a hex string: ");
        scanf("%s", string);

        int hex_int_value = htoi(string);

        if (hex_int_value < 0) {
                printf("Invalid hex value: %s\n", string);
        } else {
                printf("Hex int value: %d\n", hex_int_value);
        }
}

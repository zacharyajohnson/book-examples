/*
 * Exercise 2-6
 *
 * Write a function setbits(x,p,n,y) that returns
 * x with the n bits that begin at position p set
 * to the rightmost n bits of y, leaving the other
 * bits unchanged
 */

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
        unsigned nbits;

	nbits = ~(~0 << n); /* mask to extract rightmost n bits */

	return (x & ~(nbits << p)) | ((y & nbits) << p);
}

int main(void) {
        unsigned result = setbits(246, 2, 3, 81);

        printf("Result: %u\n", result);
}

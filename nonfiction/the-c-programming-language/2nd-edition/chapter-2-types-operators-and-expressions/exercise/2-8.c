/*
 * Exercise 2-8
 *
 * Write a function rightrot(x,n) that returns the
 * value of the integer x rotated to the right by
 * n bit positions
 *
 */

#include <stdio.h>

size_t int_size() {
	int x = ~0;
	size_t i = 0;

	while (x != 0) {
		x <<= 1;
		++i;
	}

	return i;
}

unsigned rightrot(unsigned x, int n) {
	unsigned size, bits;

	size = int_size();     /* never assume size of an int */
	n = n % size;          /* scale down the shift count to a defined range */
	bits = x & ~(~0 << n); /* extract the n bits to be rotated */

	return (x >> n) | bits << (size - n);
}

int main(void) {
	unsigned x = 0XAF14E5CB;
	int n = 8;

	printf("%x\n", rightrot(x, n));

	return 0;
}

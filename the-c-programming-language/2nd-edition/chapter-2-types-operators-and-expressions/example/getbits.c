#include <stdio.h>

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n) 
{
        /* This shit is hard to understand
         * So I will break it down
         * Given x = 246(11110110 in binary)(32 bits so leading zeros)
         * p = 2, and n = 3
         *
         * We will end up with 6 as being returned(110)
         *
         * p(position) starts from the leftmost bit to rightmost
         * So p of 2 of the above example will result in
         * the cursor being set here 11110110
         *                                ^
         *                                |
         *                                |
         * 
         * n is the number of bits we want to return.
         * Since n = 3, we will return 110 since there
         * are 3 bits starting at p position from left
         * to right
         *
         *
         * x >> (p+1-n) will shift the bits
         * right based on the position and how
         * many bits we actually want to return
         * In this example 246 >> (2+1-3) will shift
         * the bits 0 positions so the binary will
         * remain unchanged(11110110)
         *
         * To get the part we actually want,
         * we have to do some more bit manipulation.
         *
         * ~(~0 << n) will do the following
         * ~0 is ones complement so 11111111 << n
         * will shift left n positions so when
         * n = 3 
         * 11111111 << 3 = 248 (11111000, with a bunch of leading ones since this is 32 bit)
         *
         * Right now we have ~(11111000) which will equal  00000111(Leading ones are now zeros, value is 7)
         *
         * Then we do a bitwise AND with 11110110 and 0111(both 32 bits)
         *
         * 00000000000000000000000011110110
         * 00000000000000000000000000000111
         * --------------------------------
         * 00000000000000000000000000000110
         *
         * And get 6 as the result(110)
         *
         * Fuck that was a lot of notes. Hope you learned something lol.
         */ 
        return (x >> (p+1-n)) & ~(~0 << n);
}

int main(void) {
        printf("Bits: %u\n", getbits(246, 2, 3));
}

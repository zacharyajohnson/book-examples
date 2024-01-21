/*
 * Exercise 7-9
 *
 * Functions like isupper can be implemented to save space
 * or to save time.
 *
 * Explore both possibilities.
 *
 */

/* Saves time since it isn't a function call */
/* Will have more space since its a macro(text substitution) */
#define isupper(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0

/* Saves space since it is a function call and only called once */
/* Will take more time since its a function call */
int isupper(char c) {
        if (c >= 'A' && c <= 'Z') {
                return 1;
        } else {
                return 0;
        }
}


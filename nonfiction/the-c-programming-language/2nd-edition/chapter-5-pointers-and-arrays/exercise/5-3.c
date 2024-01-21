/*
 * Exercise 5-3
 *
 * Write a pointer version of the function strcat that we showed in
 * Chapter 2: strcat(s,t) copies the string t to the end of s.
 *
 */

void strcat(char* s, char* t)
{
        while (*s != '\0')    /* find end of s */
                s++;
        while ((*s++ = *t++) != '\0')       /* copy t */
                ;
}

/*
 * Exercise 5-5
 *
 * Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings.
 *
 * For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 *
 */

void strncpy(char* dest, char* source, int n) {
        while (*t != '\0' && n-- > 0) {
                *s++ = *t++;
        }

        while (n-- > 0) {
                *s++ = '\0';
        }
}

void strncat(char* dest, char* source, int n) {
        for (; *dest != '\0'; dest++)
                ;

        for (; (*dest = *source) != '\0'; source++, dest++) {
               if (--n <= 0) {
                      break;
               }
        }

        dest++;
        *dest = '\0';
}

int strcmpn(char* s, char* t, int n) {
        for ( ; *s==*t; s++, t++) {
               if (*s == '\0' || --n <= 0) {
                      return 0; 
               }
        }

        return *s - *t;
}

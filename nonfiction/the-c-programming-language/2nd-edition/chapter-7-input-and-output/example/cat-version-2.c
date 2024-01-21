#include <stdio.h>
#include <stdlib.h>

void filecopy(FILE* ifp, FILE* ofp);

/* cat: concatenate files, version 2 */
int main (int argc, char *argv[]) {
        FILE *fp;
        void filecopy(FILE*, FILE*);
        char *prog = argv[0]; /* program name for errors */

        if (argc == 1) {
                filecopy(stdin, stdout); /* no args; copy standard input */
        } else {
                while (--argc > 0) {
                        if ((fp = fopen(*++argv, "r")) == NULL) {
                                fprintf(stderr, "cat: can't open %s\n", *argv);
                                exit(1);
                        } else {
                                filecopy(fp, stdout);
                                fclose(fp);
                        }
                }
        }

        if (ferror(stdout)) {
                fprintf(stderr, "%s: error writing stdout\n", prog);
                exit(2);
        }

        exit(0);
}

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE* ifp, FILE* ofp) {
        int c;

        while ((c = getc(ifp)) != EOF) {
                putc(c, ofp);
        }
}


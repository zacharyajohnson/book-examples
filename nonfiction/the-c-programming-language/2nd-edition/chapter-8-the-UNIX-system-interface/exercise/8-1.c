/*
 * Exercise 8-1
 *
 * Rewrite the program cat from Chapter 7 using read, write
 * open, and close, instead of their standard library equivalents.
 *
 * Peform experiments to determine the relative speeds of the two
 * versions
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void filecopy(int ifd, int ofd);

/* cat: concatenate files, version 2 */
int main (int argc, char *argv[]) {
        int fd;
        void filecopy(int, int);
        char *prog = argv[0]; /* program name for errors */

        if (argc == 1) {
                filecopy(0, 1); /* no args; copy standard input */
        } else {
                while (--argc > 0) {
                        if ((fd = open(*++argv, O_RDONLY)) == -1) {
                                fprintf(stderr, "cat: can't open %s\n", *argv);
                                exit(1);
                        } else {
                                filecopy(fd, 1);
                                close(fd);
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
void filecopy(int ifd, int ofd) {
        int n;
        char buf[BUFSIZ];

        while((n = read(ifd, buf, BUFSIZ)) > 0) {
                if (write(ofd, buf, n) != n) {
                        fprintf(stderr, "Error writing on file %d", ofd);
                        exit(1);
                }
        }
}


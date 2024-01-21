/*
 * Exercise 8-2
 *
 * Rewrite fopen and _fillbuf with fields instead of explicit bit
 * operations
 *
 * Compare code size and execution speed
 *
 */

/*
 * Conclusion
 *
 * Bitfields require more code and are slower since they
 * are machine dependent.
 *
 * Bit operations on a single int are more concise and
 * have a constant performance profile
 *
 */
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max files open at once */

typedef struct _flags {
        unsigned is_read: 1;
        unsigned is_write: 1;
        unsigned is_unbuf: 1;
        unsigned is_buf: 1;
        unsigned is_eof: 1;
        unsigned is_err : 1;
} Flag;

typedef struct _iobuf {
        int cnt;        /* characters left */
        char* ptr;      /* next character position */
        char* base;     /* location of buffer */
        Flag flag;       /* mode of file access */
        int fd;         /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE*);
int _flushbuf(int, FILE*);

#define feof(p) ((p)->flag.is_eof != 0 )
#define ferror(p) ((p)->flag.is_err != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x, p) (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x) : _flushbuff((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define PERMS 0666 /* RW for owner, group, others */

/* fopen: open file, return file ptr */
FILE* fopen(char* name, char* mode) {
        int fd;
        FILE *fp;

        if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
                return NULL;
        }

        for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
                if (fp->flag.is_read == 0 && fp->flag.is_write  == 0) {
                        break;  /* found free slot */
                }
        }

        if (fp >= _iob + OPEN_MAX) { /* no free slots */
                return NULL;
        }

        if (*mode == 'w') {
                fd = creat(name, PERMS);
        } else if (*mode == 'a') {
                if ((fd = open(name, O_WRONLY, 0)) == -1) {
                        fd = creat(name, PERMS);
                }

                lseek(fd, 0L, 2);
        } else {
                fd = open(name, O_RDONLY, 0);
        }

        if (fd == -1) { /* couldn't access name */
                return NULL;
        }

        fp->fd = fd;
        fp->cnt = 0;
        fp->base = NULL;

        fp->flag.is_unbuf = 0;
        fp->flag.is_buf = 1;
        fp->flag.is_eof = 0;
        fp->flag.is_err = 0;

        if (*mode == 'r') {
                fp->flag.is_read = 1;
                fp->flag.is_write = 0;
        } else {
                fp->flag.is_read = 0;
                fp->flag.is_write = 1;
        }


        return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE* fp) {
        int bufsize;

        if (fp->flag.is_read == 0 || fp->flag.is_eof == 1 || fp->flag.is_err == 1) {
                return EOF;
        }

        bufsize = (fp->flag.is_unbuf == 1) ? 1: BUFSIZ;

        if (fp->base == NULL) { /* no buffer yet */
                if ((fp->base = (char *) malloc(bufsize)) == NULL) {
                        return EOF;     /* can't get buffer */
                }
        }

        fp->ptr = fp->base;
        fp->cnt = read(fp->fd, fp->ptr, bufsize);

        if (--fp->cnt < 0) {
                if (fp->cnt == -1) {
                        fp->flag.is_eof = 1;
                } else {
                        fp->flag.is_err = 1;
                }
                fp->cnt = 0;
                return EOF;
        }

        return (unsigned char) *fp->ptr++;
}

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr: */
        { 0, (char *) 0, (char *) 0, {01,00,00,01,00,00}, 0 },
        { 0, (char *) 0, (char *) 0, {00,01,00,01,00,00}, 1 },
        { 0, (char *) 0, (char *) 0, {00,01,01,00,00,00}, 2 }
};

int main(void) {
        FILE* file = fopen("8-2.c", "r");

        char c;
        while ((c = getc(file)) != EOF) {
                write(stdin->fd, &c, 1);
        }

}


/*
 * Exercise 8-3
 *
 * Design and write _flushbuf, fflush, and fclose
 *
 */

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max files open at once */

typedef struct _iobuf {
        int cnt;        /* characters left */
        char* ptr;      /* next character position */
        char* base;     /* location of buffer */
        int flag;       /* mode of file access */
        int fd;         /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
        _READ = 01,     /* file open for reading */
        _WRITE = 02,    /* file open for writing */
        _UNBUF = 04,    /* file is unbuffered */
        _EOF = 010,     /* EOF has occurred on this file */
        _ERR = 020      /* error occurred on this file */
};

int fflush(FILE*);
int _fillbuf(FILE*);
int _flushbuf(int, FILE*);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x, p) (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x) : _flushbuf((x), p))

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
                if ((fp->flag & (_READ | _WRITE)) == 0) {
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
        fp->flag = (*mode == 'r') ? _READ : _WRITE;
        return fp;
}

int fclose(FILE* fp) {
        int rc;

        if ((rc = fflush(fp)) != EOF) {
                free(fp->base);
                fp->ptr = NULL;
                fp->cnt = 0;
                fp->base = NULL;
                fp->flag &= ~(_READ | _WRITE);
        }

        return rc;
}


int fflush(FILE* fp) {
        int rc = 0;

        if ((fp->flag & (_WRITE)) == 0) {
                return EOF;
        }

        if (fp < _iob || fp >= _iob + OPEN_MAX) {
                return EOF;
        }

        rc = _flushbuf(0,fp);
        fp->ptr = fp->base;
        fp->cnt = (fp->flag & _UNBUF) ? 1: BUFSIZ;

        return rc;
}


/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE* fp) {
        int bufsize;

        if ((fp->flag&(_READ|_EOF|_ERR)) != _READ) {
                return EOF;
        }

        bufsize = (fp->flag & _UNBUF) ? 1: BUFSIZ;

        if (fp->base == NULL) { /* no buffer yet */
                if ((fp->base = (char *) malloc(bufsize)) == NULL) {
                        return EOF;     /* can't get buffer */
                }
        }

        fp->ptr = fp->base;
        fp->cnt = read(fp->fd, fp->ptr, bufsize);

        if (--fp->cnt < 0) {
                if (fp->cnt == -1) {
                        fp->flag |= _EOF;
                } else {
                        fp->flag |= _ERR;
                }
                fp->cnt = 0;
                return EOF;
        }

        return (unsigned char) *fp->ptr++;
}

/* _flushbuf: allocate and flush input buffer */
int _flushbuf(int c, FILE* fp) {
        unsigned int nc;
        int bufsize;

        if (fp < _iob || fp >= _iob + OPEN_MAX) {
                return EOF;
        }

        if ((fp->flag&(_WRITE|_ERR)) != _WRITE) {
                return EOF;
        }

        bufsize = (fp->flag & _UNBUF) ? 1: BUFSIZ;

        if (fp->base == NULL) { /* no buffer yet */
                if ((fp->base = (char *) malloc(bufsize)) == NULL) {
                        fp->flag |= _ERR;
                        return EOF;     /* can't get buffer */
                }
        } else {
                nc = fp->ptr - fp->base;
                if (write(fp->fd, fp->base, nc) != nc) {
                        fp->flag |= _ERR;
                        return EOF;
                }
        }

        fp->ptr = fp->base;
        *fp->ptr++ = (char) c;
        fp->cnt = bufsize - 1;
        return c;
}

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr: */
        { 0, (char *) 0, (char *) 0, _READ, 0 },
        { 0, (char *) 0, (char *) 0, _WRITE, 1 },
        { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

int main(void) {
        FILE* file = fopen("8-3.c", "r");

        char c;
        while ((c = getc(file)) != EOF) {
                write(stdin->fd, &c, 1);
        }

}


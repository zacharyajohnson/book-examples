/*
 * Exercise 5-7
 *
 * Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage.
 *
 * How much faster is the program?
 *
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[],  int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
main()
{
        int nlines; /* number of input lines read */

        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
                qsort(lineptr, 0, nlines-1);
                writelines(lineptr, nlines);
                return 0;
        } else {
                printf("error: input too big to sort\n");
                return 1;
        }
}

#define MAXLEN 1000 /* max length of any input line */
#define MAXSTORAGE 5000

int local_getline(char*, int);
char *alloc(int);

char line_storage[MAXSTORAGE];

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
        int len, nlines;
        char *p = line_storage;
        char *line_storage_end = line_storage + MAXSTORAGE;

        char line[MAXLEN];

        nlines = 0;
        while ((len = local_getline(line, MAXLEN)) > 0) {
                if (nlines >= maxlines || p + len > line_storage_end) {
                        return -1;
                } else {
                        line[len-1] = '\0'; /* delete newline */
                        strcpy(p, line);
                        lineptr[nlines++] = p;
                        p += len;
                }
        }
        return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
        int i;

        for (i = 0; i < nlines; i++) {
                printf("%s\n", lineptr[i]);
        }
}

int local_getline(char* s, int lim)
{
        int c;
        char *t = s;

        while (--lim > 0 && (c=getchar()) != EOF && c!= '\n') {
                *s++ = c;
        }

        if (c == '\n') {
                *s++ = c;
        }

        *s = '\0';
        return s - t;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
        int i, last;
        void swap(char *v[], int i, int j);

        if (left >= right) {
                return;
        }

        swap(v, left, (left + right)/2);
        last = left;

        for(i = left+1; i <= right; i++) {
                if (strcmp(v[i], v[left]) < 0) {
                        swap(v, ++last, i);
                }
        }

        swap(v, left, last);
        qsort(v, left, last-1);
        qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
        char *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

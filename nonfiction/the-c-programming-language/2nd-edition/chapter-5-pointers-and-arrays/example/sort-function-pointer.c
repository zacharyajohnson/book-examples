#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[],  int nlines);
void writelines(char *lineptr[], int nlines);

void local_qsort(void *lineptr[], int left, int right,
                int (*comp)(void *, void *));

int numcmp(char*, char*);

/* sort input lines */
int main(int argc, char* argv[])
{
        int nlines; /* number of input lines read */
        int numeric = 0; /* 1 if numeric sort */

        if (argc > 1 && strcmp(argv[1], "-n") == 0) {
                numeric = 1;
        }

        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
                local_qsort((void **) lineptr, 0, nlines-1,
                                (int (*)(void*, void*))(numeric ? numcmp : strcmp));
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
void local_qsort(void *v[], int left, int right,
                int (*comp)(void*, void*))
{
        int i, last;
        void swap(void *v[], int i, int j);

        if (left >= right) {
                return;
        }

        swap(v, left, (left + right)/2);
        last = left;

        for(i = left+1; i <= right; i++) {
                if ((*comp)(v[i], v[left]) < 0) {
                        swap(v, ++last, i);
                }
        }

        swap(v, left, last);
        local_qsort(v, left, last-1, comp);
        local_qsort(v, last+1, right, comp);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
        void *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

/* numpcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
        double v1, v2;

        v1 = atof(s1);
        v2 = atof(s2);

        if (v1 < v2) {
                return -1;
        } else if (v1 > v2) {
                return 1;
        } else {
                return 0;
        }
}


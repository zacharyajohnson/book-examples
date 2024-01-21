/*
 * Exercise 8-5
 *
 * Modify the fsize program to print the other information
 * contained in the inode entry
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void fsize(char*);
void dirwalk(char*, void (*fcn) (char*));

/* print file sizes */
int main(int argc, char* argv[]) {
        if (argc == 1) { /* default: current directory */
                fsize(".");
        } else {
                while (--argc > 0) {
                        fsize(*++argv);
                }
        }

        return 0;
}

/* fsize: print size of file "name" */
void fsize(char* name) {
        struct stat stbuf;

        if (stat(name, &stbuf) == -1) {
                fprintf(stderr, "fsize: can't access %s\n", name);
                return;
        }

        if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
                dirwalk(name, fsize);
        }

        printf("Size: %8ld ", stbuf.st_size);
        printf("Device: %8ld ", stbuf.st_dev);
        printf("Inode Number: %8ld ", stbuf.st_ino);
        printf("Mode: %6o ", stbuf.st_mode);
        printf("UID: %8ld ", stbuf.st_uid);
        printf("GID: %8ld ", stbuf.st_gid);
        printf("Name: %s\n", name);
}

#define MAX_PATH 1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char* dir, void (*fcn)(char*)) {
        char name[MAX_PATH];

        struct dirent *dp;
        DIR *dfd;

        if ((dfd == opendir(dir)) == NULL) {
                fprintf(stderr, "dirwalk: can't open %s\n", dir);
                return;
        }

        while ((dp = readdir(dfd)) != NULL) {
                if (strcmp(dp->d_name, ".") == 0 ||
                                strcmp(dp->d_name, "..") == 0) {
                        continue; /* skip self and parent */
                }

                if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
                        fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
                } else {
                        sprintf(name, "%s/%s", dir, dp->d_name);
                        (*fcn)(name);
                }
        }

        closedir(dfd);
}


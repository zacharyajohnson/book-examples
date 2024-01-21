/*
 * Exercise 7-6
 *
 * Write a program to compare two files, printing the first line
 * where they differ.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int local_getline(FILE* file, char* line, int max) {
        if (fgets(line, max, file) == NULL) {
                return 0;
        } else {
                return strlen(line);
        }
}

int main(int argc, char* argv[]) {
        int file_1_line_index = 0;
        char file_1_line[MAXLINE];

        int file_2_line_index = 0;
        char file_2_line[MAXLINE];

        if (argc < 3) {
                fprintf(stderr, "Not enough args. Please provide paths for two files for comparison\n");
                exit(1);
        }

        FILE* file1 = fopen(argv[1], "r");
        FILE* file2 = fopen(argv[2], "r");

        if (file1 == NULL) {
                fprintf(stderr, "File 1 does not exist: %s\n", argv[1]);
                exit(1);
        } else if (file2 == NULL) {
                fprintf(stderr, "File 2 does not exist: %s\n", argv[2]);
                exit(1);
        }

        while (!feof(file1) && !feof(file2)) {
                file_2_line_index++;
                file_1_line_index++;
                int error_code_file_1 = local_getline(file1, file_1_line, MAXLINE);
                int error_code_file_2 = local_getline(file2, file_2_line, MAXLINE);

                if (error_code_file_1 == 0 || error_code_file_2 == 0) {
                        break;
                } else if (strcmp(file_1_line, file_2_line) != 0) {
                        break;
                }
        }

        if (feof(file1) && feof(file2)) {
                printf("File %s and File %s match\n", argv[1], argv[2]);
        } else {
                printf("Difference on files %s and %s\n", argv[1], argv[2]);
                printf("File 1: %s. Line %d: %s\n", argv[1], file_1_line_index, file_1_line);
                printf("File 2: %s. Line %d: %s\n", argv[2], file_2_line_index, file_2_line);

        }
}


#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILENAME_LENGTH 50
#define MAX_NUM_FILES 40

typedef struct options {
  int e;
  int n;
  int i;
  int l;
  int c;
  int v;
  int h;
  int s;
} opt;

typedef struct argum {
  int flag;
  char *template;
  char *file_name[MAX_NUM_FILES];
  int count_files;
  int many_files;
} args;

void grep_parser(int argc, char *argv[], opt *options, args *arguments);
void parsing_arguments(int argc, char **argv, args *arguments);
int find_pattern(char *line, char *pattern, int flags);
void grep(args *arguments, opt *options);
void arg_failure();

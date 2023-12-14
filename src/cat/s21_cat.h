#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int E;
  int T;
} opt;

opt options = {0};

struct option long_options[] = {
    {"number-nonblank", 0, NULL, 'b'},
    {"number", 0, NULL, 'n'},
    {"squeeze-blank", 0, NULL, 's'},
    {0, 0, 0,
     0}};  // указывает на конец списка опций, после этого прекращает работу

#endif

#include "s21_cat.h"

void cat_parser(int argc, char *argv[], opt *options) {
  int opt;
  int option_index;
  while ((opt = getopt_long(argc, argv, "+benstvTE", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      default:
        fprintf(stderr, "usage 'benstv'");
        exit(1);
    }
  }
}

void cat_reader(char *argv[], opt *options) {
  FILE *f = fopen(argv[optind], "r");
  if (!f) {  // проверяем, что fopen успешно открыл файл
    perror("s21_cat");
    exit(1);
  }
  char current_char;
  int all_line_number = 0;
  int not_null_line = 0;
  int count_empty_line = 0;
  char previos_char = '\n';

  while ((current_char = fgetc(f)) != EOF) {
    if (options->n && previos_char == '\n') printf("%6d\t", ++all_line_number);
    if (options->e && current_char == '\n') printf("$");
    if (options->t && current_char == 9) {
      printf("^I");
      previos_char = current_char;
      continue;
    }
    if (options->b && current_char != '\n' && previos_char == '\n')
      printf("%6d\t", ++not_null_line);
    if (options->s) {
      if (current_char == '\n' && previos_char == '\n') {
        count_empty_line++;
        if (count_empty_line > 1) {
          continue;
        }
      } else {
        count_empty_line = 0;
      }
    }
    if (options->v) {
      if (current_char > 0 && current_char < 32 && current_char != 10 &&
          current_char != 9 && current_char != 127) {
        printf("^%c", current_char + 64);
      } else if (current_char == 0x7F) {
        printf("^?");
      } else {
        putchar(current_char);
      }
    } else {
      putchar(current_char);
    }
    previos_char = current_char;
  }
  fclose(f);
}

int main(int argc, char *argv[]) {
  cat_parser(argc, argv, &options);
  if (options.b) options.n = 0;
  cat_reader(argv, &options);
  return 0;
}
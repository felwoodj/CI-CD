#include "s21_grep.h"

int main(int argc, char *argv[]) {
  opt options = {
      0, 0, 0, 0, 0, 0, 0, 0,
  };
  args arguments = {0, NULL, {NULL}, 0, 0};
  if (argc < 2) arg_failure();
  grep_parser(argc, argv, &options, &arguments);
  parsing_arguments(argc, argv, &arguments);
  grep(&arguments, &options);
  return 0;
}

void grep_parser(int argc, char *argv[], opt *options, args *arguments) {
  char option;
  const struct option long_options[] = {{NULL, 0, NULL, 0}};
  while ((option = getopt_long(argc, argv, "eivclnhs", long_options, NULL)) !=
         -1) {
    switch (option) {
      case 'e':
        options->e = 1;
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case '?':
        arg_failure();
    }
  }
  if (options->i || options->e || options->v || options->c || options->l ||
      options->n || options->h || options->s)
    arguments->flag = 1;
}

void arg_failure() {
  fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]...\n");
  fprintf(stderr, "Try 'grep --help' for more information.\n");
  exit(1);
}

void parsing_arguments(int argc, char **argv, args *arguments) {
  int number_of_files = argc - optind - 1;
  if (number_of_files > 1) arguments->many_files = 1;
  arguments->count_files = number_of_files;
  for (int i = optind, file_index = 0; i < argc; i++) {
    char *value = argv[i];
    if (argv[i][0] == '-') continue;
    if (arguments->template == NULL) {
      arguments->template = value;
    } else {
      arguments->file_name[file_index++] = value;  // ?
    }
  }
}

int find_pattern(char *line, char *patter, int flags) {
  regex_t regex;
  int result = regcomp(&regex, patter, flags), exit = 0;
  if (result) {
    exit = -1;
  } else {
    result = regexec(&regex, line, 0, NULL, 0);
    if (!result) {
      exit = 1;
    } else if (result == REG_NOMATCH) {
      exit = 0;
    }
  }
  regfree(&regex);
  return exit;
}

void grep(args *arguments, opt *options) {
  for (int i = 0; i < arguments->count_files; i++) {
    FILE *file = fopen(arguments->file_name[i], "rb");
    if (file == NULL) {
      if (!options->s) {
        fprintf(stderr, "grep:%s: No such file or directory\n",
                arguments->file_name[i]);
      }
      continue;
    } else {
      int count_matched_lines = 0;
      int matched_files = 0;
      int count_lines = 1;
      size_t length = 0;
      char *line = NULL;
      bool flag_s = false;

      for (; (getline(&line, &length, file)) != -1; count_lines++) {
        int comp_flag = 0;
        if (options->i) comp_flag = REG_ICASE;
        int match = find_pattern(line, arguments->template, comp_flag);
        if (options->e && match) {
          if (arguments->count_files > 1) {
            printf("%s:%s", arguments->file_name[i], line);
          } else {
            printf("%s", line);
          }

        } else if (options->i && match) {
          if (arguments->count_files > 1) {
            printf("%s:%s", arguments->file_name[i], line);
          } else {
            printf("%s", line);
          }

        } else if (options->v && !match && line != NULL) {
          if (arguments->count_files > 1) {
            printf("%s:%s", arguments->file_name[i], line);
          } else {
            printf("%s", line);
          }
          if (line[strlen(line) - 1] != 10) printf("\n");
        } else if (options->n && match) {
          if (arguments->count_files > 1) {
            printf("%s:%d:%s", arguments->file_name[i], count_lines, line);
          } else {
            printf("%d:%s", count_lines, line);
          }
          if (line[strlen(line) - 1] != 10) printf("\n");

        } else if (options->l && match) {
          printf("%s\n", arguments->file_name[i]);
          matched_files++;
          flag_s = true;
          break;
        } else if (options->c && match) {
          count_matched_lines++;
        } else if (options->h && match) {
          printf("%s", line);
        } else if (((!flag_s && match) || (!arguments->flag && match)) &&
                   !options->v) {
          printf("%s:%s", arguments->file_name[i], line);
        }
      }
      if (options->c) {
        if (arguments->count_files > 1) {
          printf("%s:%d\n", arguments->file_name[i], count_matched_lines);
        } else {
          printf("%d\n", count_matched_lines);
        }
      } else if (options->s && matched_files > 0) {
        break;
      }
      if (line) free(line);
    }
    if (file != NULL) fclose(file);
  }
}
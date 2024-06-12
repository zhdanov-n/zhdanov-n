#include "cat_func.h"

int GNU_string_flags_parser(const char* option, int* number_lines,
                            int* squeeze_blank) {
  int exit_status = 0;
  if (strcmp(option, "--number-nonblank") == 0)
    *number_lines = 2;
  else if (strcmp(option, "--number") == 0)
    *number_lines = 1;
  else if (strcmp(option, "--squeeze-blank") == 0)
    *squeeze_blank = 1;
  else {
    fprintf(stderr, ERROR_02, option);
    fprintf(stderr, ERROR_03);
    exit_status = 1;
  }
  return exit_status;
}

int char_flags_parser(char option, int* number_lines, int* show_ends,
                      int* show_nonprintable, int* squeeze_blank,
                      int* show_tabs) {
  int exit_status = 0;
  if (option == 'b') {
    *number_lines = 2;
  } else if (option == 'e') {
    *show_ends = 1;
    *show_nonprintable = 1;
  } else if (option == 'E') {
    *show_ends = 1;
  } else if (option == 'n') {
    if (!(*number_lines)) {
      *number_lines = 1;
    }
  } else if (option == 's') {
    *squeeze_blank = 1;
  } else if (option == 't') {
    *show_tabs = 1;
    *show_nonprintable = 1;
  } else if (option == 'T') {
    *show_tabs = 1;
  } else if (option == 'v') {
    *show_nonprintable = 1;
  } else {
    fprintf(stderr, ERROR_02_CHAR, option);
    fprintf(stderr, ERROR_03);
    exit_status = 1;
  }
  return exit_status;
}

void cat(FILE* file, int number_lines, int show_ends, int show_tabs,
         int squeeze_blank, int show_nonprintable) {
  int c;
  int line_num = 1;
  int non_empty_line_num = 1;
  int empty_line = 1;
  int previous_char = '\n';
  int pre_previous_char = 0;

  while ((c = getc(file)) != EOF) {
    if (!(squeeze_blank && c == '\n' &&
          (previous_char == '\n' && pre_previous_char == '\n'))) {
      if (squeeze_blank && c == '\n') {
        if (number_lines == 1 && previous_char == '\n') {
          printf("%6d\t", line_num);
        }
        if (show_ends && c == '\n') {
          putchar('$');
        }
        putchar(c);
      } else {
        if (empty_line && number_lines > 0) {
          if (number_lines == 2 && c != '\n') {
            printf("%6d\t", non_empty_line_num);
            non_empty_line_num++;
          } else if (number_lines == 1) {
            printf("%6d\t", line_num);
          }
          empty_line = 0;
        }
        if (show_tabs && c == '\t') {
          putchar('^');
          putchar('I');
        } else if (show_ends && c == '\n') {
          putchar('$');
          putchar('\n');
        } else if (show_nonprintable && (c < 32 || c == 127 || c >= 128)) {
          show_nonprintable_func(c);
        } else {
          putchar(c);
        }
      }
      if (c == '\n') {
        line_num++;
        empty_line = 1;
      }
    }
    pre_previous_char = previous_char;
    previous_char = c;
  }
}

void show_nonprintable_func(int ch) {
  if (ch != 9 && ch != 10 && ch < 32) {
    printf("^%c", ch + 64);
  } else if (ch == 127) {
    printf("^?");
  } else if (ch > 127 && ch < 160) {
    printf("M-^%c", ch - 64);
  } else if (ch >= 160 && ch != 255) {
    printf("M-%c", ch - 128);
  } else {
    putchar(ch);
  }
}

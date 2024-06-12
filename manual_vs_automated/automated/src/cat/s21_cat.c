#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int number_lines = 0;
  int show_ends = 0;
  int show_tabs = 0;
  int squeeze_blank = 0;
  int show_nonprintable = 0;
  int arg_flag = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && !arg_flag && argc > 2) {
      if (argv[i][1] == '-') {
        if (GNU_string_flags_parser(argv[i], &number_lines, &squeeze_blank) !=
            0)
          return 1;
      } else {
        for (int j = 1; argv[i][j] != '\0'; j++) {
          if (char_flags_parser(argv[i][j], &number_lines, &show_ends,
                                &show_nonprintable, &squeeze_blank,
                                &show_tabs) != 0)
            return 1;
        }
      }
    } else {
      arg_flag = 1;
      FILE *file = fopen(argv[i], "rb");
      if (file == NULL) {
        fprintf(stderr, ERROR_01, argv[i]);
      } else {
        cat(file, number_lines, show_ends, show_tabs, squeeze_blank,
            show_nonprintable);
        fclose(file);
      }
    }
  }
  if (argc == 1) {
    fprintf(stderr, ERROR_03);
  }
  return 0;
}

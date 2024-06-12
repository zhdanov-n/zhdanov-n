#include "s21_grep.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, ERROR_03);
    return 1;
  }
  grepFlags options = {0};
  int pattern_count = 0;
  const char *patterns[MAX_PATTERNS] = {0};
  const char *filenames[MAX_FILENAMES] = {0};
  int filename_count = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (int j = 1; argv[i][j] != '\0'; j++) {
        if (grepFlags_parser(argv[i][j], &options)) return 1;
      }
    }
    if (strcmp(argv[i], "-e") == 0) {
      if (i + 1 < argc) {
        patterns[pattern_count] = s21_strdup(argv[i + 1]);
        pattern_count++;
        i++;
      } else {
        fprintf(stderr, ERROR_04, argv[i][1]);
        fprintf(stderr, ERROR_03);
        return 1;
      }
    } else if (strcmp(argv[i], "-f") == 0 || options.enablepatternFile) {
      if (i + 1 < argc) {
        int count =
            read_patterns_from_file(argv[i + 1], patterns + pattern_count);
        if (count == -1) {
          fprintf(stderr, ERROR_01, argv[i + 1]);
          return 1;
        }
        pattern_count += count;
        i++;
        options.enablepatternFile = 0;
      } else {
        fprintf(stderr, ERROR_04, argv[i][1]);
        fprintf(stderr, ERROR_03);
        return 1;
      }
    } else {
      if (!pattern_count && (argv[i][0] != '-')) {
        patterns[pattern_count] = s21_strdup(argv[i]);
        pattern_count++;
        i++;
      }
      if (pattern_count && (argv[i] != NULL) && (argv[i][0] != '-')) {
        filenames[filename_count] = argv[i];
        filename_count++;
      }
    }
  }
  int multiple_files = filename_count > 1;
  for (int i = 0; i < filename_count; i++) {
    grep(patterns, pattern_count, filenames[i], options, multiple_files);
  }
  for (int i = 0; i < pattern_count; i++) {
    free((char *)patterns[i]);
  }
  return 0;
}

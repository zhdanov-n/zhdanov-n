#include "grep_func.h"

int grepFlags_parser(char option, grepFlags *options) {
  int exit_status = 0;
  if (option == 'i') {
    options->ignoreCase = 1;
  } else if (option == 'v') {
    options->invertMatch = 1;
  } else if (option == 'c') {
    options->printMatchCount = 1;
  } else if (option == 'l') {
    options->printOnlyFilename = 1;
  } else if (option == 'n') {
    options->printLineNumber = 1;
  } else if (option == 'h') {
    options->suppressFilenames = 1;
  } else if (option == 's') {
    options->silentMode = 1;
  } else if (option == 'o') {
    options->showOnlyMatchingPart = 1;
  } else if (option == 'e') {
    options->enablePattern = 1;
  } else if (option == 'f') {
    options->enablepatternFile = 1;
  } else {
    fprintf(stderr, ERROR_02_CHAR, option);
    fprintf(stderr, ERROR_03);
    exit_status = 1;
  }
  return exit_status;
}

char *s21_strdup(const char *str) {
  size_t len = strlen(str);
  char *dup = (char *)malloc((len + 1) * sizeof(char));
  if (dup != NULL) {
    strcpy(dup, str);
  }
  return dup;
}

int read_patterns_from_file(const char *filename,
                            const char *patterns[MAX_PATTERNS]) {
  int exit_status = 0;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    exit_status = -1;
  } else {
    int pattern_count = 0;
    char line[MAX_LINE_LENGTH] = {0};
    while (fgets(line, sizeof(line), file)) {
      if (strlen(line) == 1 && line[0] == '\n') {
        strcpy(line, ".");
      } else {
        if (line[strlen(line) - 1] == '\n') {
          line[strlen(line) - 1] = '\0';
        }
      }
      patterns[pattern_count] = s21_strdup(line);
      pattern_count++;
    }
    exit_status = pattern_count;
    fclose(file);
  }
  return exit_status;
}

void grep(const char **patterns, int pattern_count, const char *filename,
          grepFlags options, int multiple_files) {
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    regex_t regex[pattern_count];
    int regex_flags = REG_EXTENDED;
    if (options.ignoreCase) {
      regex_flags |= REG_ICASE;
    }
    for (int i = 0; i < pattern_count; i++) {
      regcomp(&regex[i], patterns[i], regex_flags);
    }
    int lineCount = 1;
    char ch = ' ';
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        lineCount++;
      }
    }
    rewind(file);
    char line[MAX_LINE_LENGTH] = {0};
    int line_number = 1;
    int matched_lines[lineCount + 1];
    memset(matched_lines, 0, sizeof(matched_lines));
    int match_count = 0;
    int flag_L = 0;
    while (fgets(line, sizeof(line), file)) {
      int line_matched = 0;
      for (int i = 0; i < pattern_count; i++) {
        if (regexec(&regex[i], line, 0, NULL, 0) == 0) {
          line_matched = 1;
          break;
        }
      }
      if (!options.invertMatch) {
        if (line_matched && !matched_lines[line_number]) {
          flag_L = 1;
          if (!options.printMatchCount && !options.printOnlyFilename) {
            if (multiple_files && !options.suppressFilenames) {
              printf("%s:", filename);
            }
            if (options.printLineNumber) {
              printf("%d:", line_number);
            }
            if (options.showOnlyMatchingPart) {
              for (int i = 0; i < pattern_count; i++) {
                regmatch_t match;
                int offset = 0;
                while (regexec(&regex[i], line + offset, 1, &match, 0) == 0) {
                  for (int j = match.rm_so; j < match.rm_eo; j++) {
                    printf("%c", line[offset + j]);
                  }
                  printf("\n");
                  offset += match.rm_eo;
                }
              }
            } else {
              printf("%s", line);
              if (line[strlen(line) - 1] != '\n') {
                printf("\n");
              }
            }
          }
          matched_lines[line_number] = 1;
          match_count++;
        }
      } else {
        if ((!line_matched && !matched_lines[line_number]) ||
            (strcmp(patterns[0], ".") == 0 && line[0] == '\n')) {
          flag_L = 1;
          if (!options.printMatchCount && !options.printOnlyFilename) {
            if (multiple_files && !options.suppressFilenames) {
              printf("%s:", filename);
            }
            if (options.printLineNumber) {
              printf("%d:", line_number);
            }
            printf("%s", line);
            if (line[strlen(line) - 1] != '\n') {
              printf("\n");
            }
          }
          matched_lines[line_number] = 1;
          match_count++;
        }
      }
      line_number++;
    }
    if (options.printMatchCount) {
      if (multiple_files) {
        printf("%s:", filename);
      }
      if (options.printOnlyFilename) {
        if (match_count > 1) match_count = 1;
      }
      printf("%d\n", match_count);
    }
    if (options.printOnlyFilename && flag_L) {
      printf("%s\n", filename);
    }
    for (int i = 0; i < pattern_count; i++) {
      regfree(&regex[i]);
    }
    fclose(file);
  } else {
    if (!options.silentMode) {
      fprintf(stderr, ERROR_01, filename);
    }
  }
}

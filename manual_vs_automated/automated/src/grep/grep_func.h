#ifndef SRC_GREP_GREP_FUNC_H_
#define SRC_GREP_GREP_FUNC_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERNS 1024
#define MAX_LINE_LENGTH 8192
#define MAX_FILENAMES 100
#define ERROR_01 "s21_grep: %s: No such file or directory\n"
#define ERROR_02_CHAR "s21_grep: invalid option -- %c\n"
#define ERROR_03 \
  "usage: s21_grep [-chilnosv] [-e pattern] [-f file] [pattern] [file ...]\n"
#define ERROR_04 "s21_grep: option requires an argument -- %c\n"

typedef struct {
  int enablePattern;
  int ignoreCase;
  int invertMatch;
  int printMatchCount;
  int printOnlyFilename;
  int printLineNumber;
  int suppressFilenames;
  int silentMode;
  int enablepatternFile;
  int showOnlyMatchingPart;
} grepFlags;

int grepFlags_parser(char option, grepFlags *options);
char *s21_strdup(const char *str);
int read_patterns_from_file(const char *filename,
                            const char *patterns[MAX_PATTERNS]);
void grep(const char **patterns, int pattern_count, const char *filename,
          grepFlags options, int multiple_files);

#endif  // SRC_GREP_GREP_FUNC_H_

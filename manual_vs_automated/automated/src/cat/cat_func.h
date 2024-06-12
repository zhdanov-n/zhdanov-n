#ifndef SRC_CAT_CAT_FUNC_H_
#define SRC_CAT_CAT_FUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_01 "s21_cat: %s: No such file or directory\n"
#define ERROR_02 "s21_cat: illegal option -- %s\n"
#define ERROR_02_CHAR "s21_cat: illegal option -- %c\n"
#define ERROR_03                                               \
  "Usage: s21_cat [-beEnstTv] [--number-nonblank] [--number] " \
  "[--squeeze-blank] [file ...]\n"

int GNU_string_flags_parser(const char* option, int* number_lines,
                            int* squeeze_blank);
int char_flags_parser(char option, int* number_lines, int* show_ends,
                      int* show_nonprintable, int* squeeze_blank,
                      int* show_tabs);
void cat(FILE* file, int number_lines, int show_ends, int show_tabs,
         int squeeze_blank, int show_nonprintable);
void show_nonprintable_func(int ch);
#endif  // SRC_CAT_CAT_FUNC_H_

#!/bin/bash

S21_GREP_CMD="./s21_grep"

compare_output() {
local s21_output="$1"
local grep_output="$2"

diff -u "$s21_output" "$grep_output"
local exit_code=$?

if [[ $exit_code -eq 0 ]]; then
echo "Test passed!"
else
echo "Test failed!"
fi

return $exit_code
}

cleanup() {
rm -f file.txt file1.txt file2.txt patterns.txt patterns2.txt s21_output.txt grep_output.txt
}
trap cleanup EXIT

echo "pattern matching text pattern2" > file.txt
echo "some other text" > file1.txt
echo "pattern matching another text" > file2.txt
echo "pattern" > patterns.txt
echo "pattern2" >> patterns2.txt

# Test 1: Single file search with '-c' flag
echo "Test 1: Single file search with '-c' flag"
$S21_GREP_CMD -c "pattern" file.txt > s21_output.txt
grep -c "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 2: Multiple files search with '-h' flag
echo "Test 2: Multiple files search with '-h' flag"
$S21_GREP_CMD -h "pattern" file1.txt file2.txt > s21_output.txt
grep -h "pattern" file1.txt file2.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 3: Case-insensitive search with '-i' flag
echo "Test 3: Case-insensitive search with '-i' flag"
$S21_GREP_CMD -i "Pattern" file.txt > s21_output.txt
grep -i "Pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 4: List files with '-l' flag
echo "Test 4: List files with '-l' flag"
$S21_GREP_CMD -l "pattern" file1.txt file2.txt > s21_output.txt
grep -l "pattern" file1.txt file2.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 5: Show line numbers with '-n' flag
echo "Test 5: Show line numbers with '-n' flag"
$S21_GREP_CMD -n "pattern" file.txt > s21_output.txt
grep -n "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 6: Show only matching part with '-o' flag
echo "Test 6: Show only matching part with '-o' flag"
$S21_GREP_CMD -o "pattern" file.txt > s21_output.txt
grep -o "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 7: Silent mode with '-s' flag
echo "Test 7: Silent mode with '-s' flag"
$S21_GREP_CMD -s "pattern" file.txt > s21_output.txt
grep -s "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 8: Invert match with '-v' flag
echo "Test 8: Invert match with '-v' flag"
$S21_GREP_CMD -v "pattern" file.txt > s21_output.txt
grep -v "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 9: Multiple patterns search with '-e' pattern option
echo "Test 9: Multiple patterns search with '-e' pattern option"
$S21_GREP_CMD -e "pattern1" -e "pattern2" file.txt > s21_output.txt
grep -e "pattern1" -e "pattern2" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 10: Combination of '-i' and '-v' flags
echo "Test 10: Combination of '-i' and '-v' flags"
$S21_GREP_CMD -i -v "pattern" file.txt > s21_output.txt
grep -iv "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 11: Case-insensitive search with line numbers
echo "Test 11: Case-insensitive search with line numbers"
$S21_GREP_CMD -i -n "pattern" file.txt > s21_output.txt
grep -in "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 12: Invert match with silent mode
echo "Test 12: Invert match with silent mode"
$S21_GREP_CMD -v -s "pattern" file.txt > s21_output.txt
grep -vs "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 13: Show only matching part with case-insensitive search
echo "Test 13: Show only matching part with case-insensitive search"
$S21_GREP_CMD -i -o "pattern" file.txt > s21_output.txt
grep -io "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 14: Multiple patterns search with '-e' pattern option
echo "Test 14: Multiple patterns search with '-e' pattern option"
$S21_GREP_CMD -e "pattern1" -e "pattern2" file.txt > s21_output.txt
grep -e "pattern1" -e "pattern2" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 15: Invert match with multiple patterns search
echo "Test 15: Invert match with multiple patterns search"
$S21_GREP_CMD -v -e "pattern1" -e "pattern2" file.txt > s21_output.txt
grep -v -e "pattern1" -e "pattern2" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 16: Case-insensitive search with invert match
echo "Test 16: Case-insensitive search with invert match"
$S21_GREP_CMD -i -v "pattern" file.txt > s21_output.txt
grep -iv "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 17: List files with line numbers
echo "Test 17: List files with line numbers"
$S21_GREP_CMD -l -n "pattern" file1.txt file2.txt > s21_output.txt
grep -l -n "pattern" file1.txt file2.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 18: Show only matching part with invert match
echo "Test 18: Show only matching part with invert match"
$S21_GREP_CMD -o -v "pattern" file.txt > s21_output.txt
grep -o -v "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 19: Silent mode with multiple patterns search
echo "Test 19: Silent mode with multiple patterns search"
$S21_GREP_CMD -s -e "pattern1" -e "pattern2" file.txt > s21_output.txt
grep -s -e "pattern1" -e "pattern2" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 20: Case-insensitive search with line numbers and invert match
echo "Test 20: Case-insensitive search with line numbers and invert match"
$S21_GREP_CMD -i -n -v "pattern" file.txt > s21_output.txt
grep -in -v "pattern" file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 21: Multiple patterns search with '-e' pattern option and single '-f' flag
echo "Test 21: Multiple patterns search with '-e' pattern option and single '-f' flag"
$S21_GREP_CMD -e "pattern1" -e "pattern2" -f patterns.txt file.txt > s21_output.txt
grep -e "pattern1" -e "pattern2" -f patterns.txt file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 22: Multiple patterns search with '-e' pattern option and multiple '-f' flags
echo "Test 22: Multiple patterns search with '-e' pattern option and multiple '-f' flags"
$S21_GREP_CMD -e "pattern1" -e "pattern2" -f patterns.txt -f patterns.txt file.txt > s21_output.txt
grep -e "pattern1" -e "pattern2" -f patterns.txt -f patterns.txt file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 23: Combination of '-i' and '-f' flags
echo "Test 23: Combination of '-i' and '-f' flags"
$S21_GREP_CMD -i -f patterns.txt file.txt > s21_output.txt
grep -i -f patterns.txt file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 24: Combination of '-v' and '-f' flags
echo "Test 24: Combination of '-v' and '-f' flags"
$S21_GREP_CMD -v -f patterns.txt file.txt > s21_output.txt
grep -v -f patterns.txt file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

# Test 25: Combination of '-i', '-v', and '-f' flags
echo "Test 25: Combination of '-i', '-v', and '-f' flags"
$S21_GREP_CMD -i -v -f patterns.txt file.txt > s21_output.txt
grep -iv -f patterns.txt file.txt > grep_output.txt
compare_output "s21_output.txt" "grep_output.txt"

echo "All tests completed!"

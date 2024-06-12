#!/bin/bash

REMOTE_HOST="172.24.116.8"
USERNAME="root"

CAT_BINARY_PATH="src/cat/s21_cat"
GREP_BINARY_PATH="src/grep/s21_grep"

REMOTE_DESTINATION="/usr/local/bin/"

scp $CAT_BINARY_PATH $USERNAME@$REMOTE_HOST:/usr/local/bin
scp $GREP_BINARY_PATH $USERNAME@$REMOTE_HOST:/usr/local/bin

if [ $? -eq 0 ]; then
  echo "Deploy success."
else
  echo "Deploy failure."
  exit 1
fi
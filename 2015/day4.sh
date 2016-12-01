#!/bin/bash

SK=iwrupvqb
PREFIX=000000

START=$1
INC=$2

i=$START
while [[ $(md5 -qs $SK$i) != $PREFIX* ]]; do
  if [[ $(((i - START) % (INC * 100))) == 0 ]]; then
    echo "Tested $i"
  fi
  ((i += INC))
done

echo "MD5($SK$i) = $(md5 -qs $SK$i)"

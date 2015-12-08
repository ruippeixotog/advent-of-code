#!/bin/bash
TMP=$(mktemp)
trap "rm $TMP" EXIT

ENCODED=$(tee $TMP | sed 's/\\/\\\\/g' | sed 's/"/\\"/g' | \
  sed 's/\(.*\)/"\1"/g' | wc -m)
RAW=$(wc -m < $TMP)

echo $((ENCODED-RAW))

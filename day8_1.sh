#!/bin/bash
TMP=$(mktemp)
trap "rm $TMP" EXIT

RAW=$(tee $TMP | sed 's/\\\\/_/g' | sed 's/\\"/_/g' | \
  sed 's/\\x[0-9a-f][0-9a-f]/_/g' | sed 's/"//g' | wc -m)
ENCODED=$(wc -m < $TMP)

echo $((ENCODED-RAW))

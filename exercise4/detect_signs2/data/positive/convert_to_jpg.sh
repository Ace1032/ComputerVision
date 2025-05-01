#!/bin/bash
mkdir -p numbered

i=1
for file in Screenshot*; do
    extension="${file##*.}"
    convert "$file" "numbered/${i}.jpg"
    ((i++))
done

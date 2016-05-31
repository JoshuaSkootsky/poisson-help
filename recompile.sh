#!/bin/bash

file="random_tester"
# You need the space around the brackets
if [ -f "$file" ]
then
    rm "$file" && make "$file"
else
    make "$file"
fi

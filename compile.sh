#!/bin/sh

set -e

gcc -Wall -Wextra -Wpedantic -pedantic -g -o main main.c
echo "Compilation complete!"

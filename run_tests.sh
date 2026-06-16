#!/usr/bin/env bash
set -euo pipefail

echo "Compiling test_light.c..."
gcc -I. -std=c99 -O2 -Wall test_light.c -o test_light

echo "Running tests..."
./test_light

echo "Done."

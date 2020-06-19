#!/bin/bash

make
#find error_test -type f -exec echo -e "\ntest {}" \; -exec ./cub3D {} \;
find error_test -type f -exec echo -e "\ntest {}" \; -exec valgrind --undef-value-errors=no ./cub3D {} \; -exec echo "" \;


#!/bin/bash

make
find error_test -type f -exec echo -e "\ntest {}" \; -exec ./Cub3D {} \;


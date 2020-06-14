#!/bin/bash

find error_test -type f -exec echo -e "\ntest {}" \; -exec ./Cub3D {} --save \;


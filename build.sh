#!/bin/bash

if [ ! -d "$PWD/build" ]; then
	mkdir build
fi

cd build/ &&
gcc -Wall -Wextra -ggdb -I../raylib-5.0_linux_amd64/include ../main.c -o main -L../raylib-5.0_linux_amd64/lib -l:libraylib.a -lm &&
./main

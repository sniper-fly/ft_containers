#!/bin/bash
sed -i -e "s@^SRC_FILES =.*@SRC_FILES = $(find ./src -type f -name '*.cpp' | xargs basename -a | tr '\n' ' ')@g" ./Makefile

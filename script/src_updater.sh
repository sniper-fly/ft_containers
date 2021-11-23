#!/bin/bash
sed -i -e "s@^SRC_FILES =.*@SRC_FILES = $(find ./src -type f -name '*.cpp' | tr '\n' ' ')@g" ./Makefile

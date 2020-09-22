#!/bin/bash

rm -rf GameDemo
find . -name "Makefile"        | xargs rm -rf
find . -name "build"           | xargs rm -rf
find . -name "CMakeFiles"      | xargs rm -rf
find . -name "CMakeCache.txt"  | xargs rm -rf
find . -name "*.cmake"         | xargs rm -rf
find . -name "*.dylib"         | xargs rm -rf
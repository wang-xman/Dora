#!/bin/sh

# must explilcitly add to the library path the path to the shared lib.
export LD_LIBRARY_PATH=$DORA_PROJECT_ROOT/build:$LD_LIBRARY_PATH

# Dora lib-wide directories
INCDIR="$DORA_PROJECT_ROOT/include"
SRCDIR="$DORA_PROJECT_ROOT/src"
BLDDIR="$DORA_PROJECT_ROOT/build"

echo "*****************"
echo "* UNIT : assert *"
echo "*****************"
# Compiling into a shared library has been delegated
# to the Makefile in the upper directory
echo "-- WARNING: Must manually run Makefile to create or update shared library"

echo "-- Compile local source file(s) with Dora header"
g++ -std=c++11 -g -Wall -c ./test_assert.cpp -o ./test_assert.o -I $INCDIR

echo "-- Link object files with Dora shared lib"
g++ -std=c++11 -g -Wall -L$BLDDIR ./test_assert.o -o ./unit_test_assert.out -ldora

echo "-- Run executable"
./unit_test_assert.out
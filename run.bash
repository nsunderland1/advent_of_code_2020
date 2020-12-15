#!/bin/bash

DAY=$(date +%-d)
DAY_PADDED=$(printf "%02d" $DAY)

cd day${DAY_PADDED}
g++-10 -std=c++20 -O3 puzzle.cpp
./a.out

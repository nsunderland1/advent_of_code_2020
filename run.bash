#!/bin/bash

DAY=$(date +%-d)
DAY_PADDED=$(printf "%02d" $DAY)

cd day${DAY_PADDED}
g++ puzzle${1}.cpp
./a.out

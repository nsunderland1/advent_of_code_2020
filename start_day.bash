#!/bin/bash

DAY=$(date +%-d)
DAY_PADDED=$(printf "%02d" $DAY)

firefox https://adventofcode.com/2020/day/${DAY}

mkdir day${DAY_PADDED}
cp template.cpp day${DAY_PADDED}/puzzle1.cpp
cp template.cpp day${DAY_PADDED}/puzzle2.cpp

code -n . day${DAY_PADDED}/puzzle1.cpp day${DAY_PADDED}/puzzle2.cpp

curl "https://adventofcode.com/2020/day/${DAY}/input" -H "Cookie: session=${ADVENT_SESSION}" > "day${DAY_PADDED}/input"

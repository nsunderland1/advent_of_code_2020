#!/bin/bash

DAY=$(date +%-d)
DAY_PADDED=$(printf "%02d" $DAY)

firefox https://adventofcode.com/2020/day/${DAY}

mkdir day${DAY_PADDED}
cp template.cpp day${DAY_PADDED}/puzzle.cpp
cp template.js day${DAY_PADDED}/puzzle.js

code -n . day${DAY_PADDED}/puzzle.cpp day${DAY_PADDED}/puzzle.js

curl "https://adventofcode.com/2020/day/${DAY}/input" -H "Cookie: session=${ADVENT_SESSION}" > "day${DAY_PADDED}/input"

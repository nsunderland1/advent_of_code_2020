#!/bin/bash

DAY=$(date +%-d)
DAY_PADDED=$(printf "%02d" $DAY)

firefox https://adventofcode.com/2020/day/${DAY}

mkdir day${DAY_PADDED}
cp template.cpp day${DAY_PADDED}/puzzle.cpp
cp template.js day${DAY_PADDED}/puzzle.js
cp template-dune day${DAY_PADDED}/dune
cp template.ml day${DAY_PADDED}/puzzle.ml

# generate .merlin files to make ocaml-lsp happy
dune build day${DAY_PADDED}

code -n . day${DAY_PADDED}/puzzle.cpp day${DAY_PADDED}/puzzle.js day${DAY_PADDED}/puzzle.ml

curl "https://adventofcode.com/2020/day/${DAY}/input" -H "Cookie: session=${ADVENT_SESSION}" > "day${DAY_PADDED}/input"

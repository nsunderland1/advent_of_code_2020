#!/bin/bash

DAY=$(date +%-d)
DAY_PADDED=$(printf "%02d" $DAY)

dune build day${DAY_PADDED}

cp _build/default/day${DAY_PADDED}/puzzle.exe day${DAY_PADDED}/puzzle
cd day${DAY_PADDED}
./puzzle

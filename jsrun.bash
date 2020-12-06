#!/bin/bash

DAY=$(date +%-d)
DAY_PADDED=$(printf "%02d" $DAY)

cd day${DAY_PADDED}
node puzzle.js

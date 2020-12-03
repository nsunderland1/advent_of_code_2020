const fs = require('fs');

const IGNORE_EMPTY_LINES = true;

const data = fs.readFileSync('input', 'UTF-8');
let lines = data.split(/\r?\n/);

if (IGNORE_EMPTY_LINES) {
  lines = lines.filter(line => line !== "");
}

const valid =
  lines
    .map(line => {
      console.log(line);
      const [range, letterColon, pass] = line.split(' ');
      const [lo, hi] = range.split('-').map(n => parseInt(n, 10));
      const letter = letterColon[0];
      return {hi, lo, letter, pass};
    })
    .reduce((acc, {lo, hi, letter, pass}) => {
      const count = pass.split(letter).length-1;
      return acc + Number(lo <= count && count <= hi);
    }, 0);

console.log(valid);

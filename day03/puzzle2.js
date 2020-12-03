const fs = require('fs');

const IGNORE_EMPTY_LINES = true;

const data = fs.readFileSync('input', 'UTF-8');
let lines = data.split(/\r?\n/);

if (IGNORE_EMPTY_LINES) {
  lines = lines.filter(line => line !== "");
}

const trees =
  [[1, 1], [3, 1], [5, 1], [7, 1], [1, 2]].map(
    ([xstep, ystep]) =>
      lines
        .reduce(([tot, y, x], line, i) =>
          i < y ? [tot, y, x] : [tot + Number(line[x] === '#'), y + ystep, (x + xstep) % line.length]
        , [0, 0, 0])[0]
  ).reduce((a, b) => a * b);

console.log(trees);


const fs = require('fs');

const IGNORE_EMPTY_LINES = true;

const data = fs.readFileSync('input', 'UTF-8');
let lines = data.split(/\r?\n/);

if (IGNORE_EMPTY_LINES) {
  lines = lines.filter(line => line !== "");
}

const [trees,] =
  lines
    .reduce(([tot, x], line) =>
      [tot + Number(line[x] === '#'), (x + 3) % line.length]
    , [0, 0]);

console.log(trees);


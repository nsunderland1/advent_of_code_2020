const fs = require('fs');

const IGNORE_EMPTY_LINES = true;

const data = fs.readFileSync('input', 'UTF-8');
let lines = data.split(/\r?\n/);

if (IGNORE_EMPTY_LINES) {
  lines = lines.filter(line => line !== "");
}
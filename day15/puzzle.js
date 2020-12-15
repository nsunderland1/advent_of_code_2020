const fs = require('fs');

const IGNORE_EMPTY_LINES = true;
const GOAL = 30000000;

const data = fs.readFileSync('input', 'UTF-8');
let lines = data.split(/\r?\n/);

if (IGNORE_EMPTY_LINES) {
  lines = lines.filter(line => line !== "");
}

const nums = lines[0].split(',');
const said = Array(GOAL).fill(-1);
nums.forEach((num, i) => {
  said[num] = i;
});

let last = 0;
for (let i = nums.length; i < GOAL-1; i++) {
  if (said[last] < 0) {
    said[last] = i;
    last = 0;
  } else {
    const tmp = i - said[last];
    said[last] = i;
    last = tmp;
  }
}
console.log(last);


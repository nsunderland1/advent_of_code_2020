const fs = require('fs');
const { exit } = require('process');
const v8 = require('v8');

const structuredClone = obj => {
  return v8.deserialize(v8.serialize(obj));
};

const IGNORE_EMPTY_LINES = true;

const data = fs.readFileSync('input', 'UTF-8');
let lines = data.split(/\r?\n/);

if (IGNORE_EMPTY_LINES) {
  lines = lines.filter(line => line !== "");
}

const dirs = [-1, 0, 1];
const dirs4d = dirs.map(x => {
  return dirs.map(y => {
    return dirs.map(z => {
      return dirs.map(w => {
        return [x,y,z,w];
      });
    }).flat();
  }).flat();
}).flat().filter(([x,y,z,w]) => x !== 0 || y !== 0 || z != 0 || w != 0);

const neighbours = pos => {
  const [x,y,z,w] = pos;
  return dirs4d.map(([dx,dy,dz,dw]) => [x+dx,y+dy,z+dz,w+dw]);
};

let grid = {};

lines.forEach((line, y) => {
  [...line].forEach((state, x) => {
    const pos = [x,y,0,0];
    grid[JSON.stringify(pos)] = state;
  });
});
gexpand(grid);

const CYCLE_COUNT = 6;
let updated = structuredClone(grid);
for (let cycle = 0; cycle < CYCLE_COUNT; cycle++) {
  Object.keys(grid).forEach(pos => {
    const state = grid[pos];
    const nbcount = neighbours(JSON.parse(pos)).filter(nb => grid[JSON.stringify(nb)] === '#').length;
    if (state === '#' && nbcount !== 2 && nbcount !== 3) {
      updated[pos] = '.';
    } else if (state === '.' && nbcount === 3) {
      updated[pos] = '#';
    }
  });
  gexpand(updated);
  grid = structuredClone(updated);
}

console.log(Object.keys(grid).reduce((acc, pos) => {
  return grid[pos] === '#' ? acc+1 : acc;
}, 0));

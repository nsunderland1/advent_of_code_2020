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

const gset = (gr, [x,y,z,w], v) => {
  if (gr[x] === undefined) {
    gr[x] = {};
  }
  if (gr[x][y] === undefined) {
    gr[x][y] = {};
  }
  if (gr[x][y][z] === undefined) {
    gr[x][y][z] = {};
  }
  gr[x][y][z][w] = v;
};
const gget = (gr, [x,y,z,w]) => {
  if (gr[x] === undefined) {
    return undefined;
  }
  if (gr[x][y] === undefined) {
    return undefined;
  }
  if (gr[x][y][z] === undefined) {
    return undefined;
  }
  return gr[x][y][z][w];
};
const gkeys = gr => {
  return Array.from(Object.keys(gr)).map(x => {
    x = parseInt(x, 10);
    return Array.from(Object.keys(gr[x])).map(y => {
      y = parseInt(y, 10);
      return Array.from(Object.keys(gr[x][y])).map(z => {
        z = parseInt(z, 10);
        return Array.from(Object.keys(gr[x][y][z])).map(w => {
          w = parseInt(w, 10);
          return [x,y,z,w];
        });
      }).flat();
    }).flat();
  }).flat();
};

const gexpand = gr => {
  gkeys(gr).forEach(key => {
    neighbours(key).forEach(nb => {
      if (gget(gr, nb) === undefined) {
        gset(gr, nb, '.');
      }
    });
  });
}
let grid = {};

lines.forEach((line, y) => {
  [...line].forEach((state, x) => {
    const pos = [x,y,0,0];
    gset(grid, pos, state);
  });
});
gexpand(grid);

const CYCLE_COUNT = 6;
let updated = structuredClone(grid);
for (let cycle = 0; cycle < CYCLE_COUNT; cycle++) {
  gkeys(grid).forEach(pos => {
    const state = gget(grid, pos);
    const nbcount = neighbours(pos).filter(nb => gget(grid, nb) === '#').length;
    if (state === '#' && nbcount !== 2 && nbcount !== 3) {
      gset(updated, pos, '.');
    } else if (state === '.' && nbcount === 3) {
      gset(updated, pos, '#');
    }
  });
  gexpand(updated);
  grid = structuredClone(updated);
}

console.log(gkeys(grid).reduce((acc, pos) => {
  return gget(grid, pos) === '#' ? acc+1 : acc;
}, 0));

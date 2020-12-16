const { info } = require('console');
const fs = require('fs');
const { exit } = require('process');

const IGNORE_EMPTY_LINES = true;

const data = fs.readFileSync('input', 'UTF-8');
const sections = data.split(/\n\n/);
const fieldData =
  sections[0].split('\n')
             .map(line => {
               const [name, info] = line.split(':').map(str => str.trim());
               const ranges =
                info.split('or').map(str => str.trim())
                    .map(range => {
                      const [lo, hi] = range.split('-').map(num => parseInt(num, 10));
                      return {lo, hi};
                    });
               return {name, ranges};
             });
const myticket = sections[1].split('\n').slice(1).join(',').split(',').map(str => parseInt(str.trim(), 10));
const nearby = sections[2].trim().split('\n').slice(1).map(ticket => ticket.split(',').map(str => parseInt(str.trim(), 10)));
const valid = nearby.filter(ticket => {
  try {
    ticket.forEach(field => {
      let safe = false;
      fieldData.forEach(data => {
        data.ranges.forEach(range => {
          if (range.lo <= field && field <= range.hi) {
            safe = true;
          }
        });
      });
      if (!safe) {
        throw -1;
      }
    });
  } catch (bla) {
    return false;
  }
  return true;
});

const targets = [
  "departure location",
  "departure station",
  "departure platform",
  "departure track",
  "departure date",
  "departure time"
];

// let positions = {};
// let positionsRev = {};

let unsolved = {};
let unsolvedRev = {};
fieldData.forEach(field => {
  unsolved[field.name] = new Set();
});
for (let i = 0; i < myticket.length; i++) {
  unsolvedRev[i] = new Set();
  fieldData.forEach(field => {
    unsolved[field.name].add(i);
    unsolvedRev[i].add(field.name);
  });
}

let solved = {};
let solvedRev = {};
while (targets.some(target => solved[target] === undefined)) {
  valid.forEach(ticket => {
    Object.keys(unsolved).forEach(name => {
      Object.keys(unsolvedRev).forEach(pos => {
        pos = parseInt(pos, 10);
        let field = ticket[pos];
        let info = fieldData.find(data => data.name == name);
        if (!info.ranges.some(range => range.lo <= field && field <= range.hi)) {
          unsolved[name].delete(pos);
          unsolvedRev[pos].delete(name);
        }
      });
    });
  });
  Object.keys(unsolved).forEach(name => {
    if (unsolved[name].size === 1) {
      let pos = Array.from(unsolved[name].values())[0];
      solved[name] = pos;
      solvedRev[pos] = name;
      delete unsolved[name];
      delete unsolvedRev[pos];
    }
  });
  Object.keys(unsolvedRev).forEach(i => {
    i = parseInt(i, 10);
    if (unsolvedRev[i].size === 1) {
      let name = Array.from(unsolvedRev[i].values())[0];
      solved[name] = i;
      solvedRev[i] = name;
      delete unsolved[name];
      delete unsolvedRev[name];
    }
  });
  Object.entries(unsolved).forEach(([name, poses]) => {
    const posArr = Array.from(poses.values());
    posArr.forEach(pos => {
      if (solvedRev[pos]) {
        poses.delete(pos);
      }
    })
  });
  Object.entries(unsolvedRev).forEach(([pos, names]) => {
    pos = parseInt(pos, 10);
    const nameArr = Array.from(names.values());
    nameArr.forEach(name => {
      if (solved[name]) {
        names.delete(name);
      }
    });
  }); 
}
console.log(targets.reduce((acc, target) => {
  return acc * myticket[solved[target]];
}, 1));
